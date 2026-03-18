#include "RESTManager.h"

#include <QtHttpServer/QHttpServerRequest>
#include <QtHttpServer/QHttpServerResponse>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QUrlQuery>
#include <QtDebug>
#include <QDateTime>
#include <QTimeZone>
#include <QUrl>
#include <QMap>
#include <QRegularExpression>

RESTManager::RESTManager(SqlManager* sql, QObject* parent)
    : QObject(parent)
    , m_tcpServer(std::make_unique<QTcpServer>(this))
    , m_sql(sql)
{
}

QHttpServerResponse RESTManager::jsonResp(QJsonValue v, QHttpServerResponse::StatusCode code)
{
    if (v.isArray())
    {
        QHttpServerResponse resp(v.toArray(), code);
        applyCors(resp);
        return resp;
    }
    if (v.isObject())
    {
        QHttpServerResponse resp(v.toObject(), code);
        applyCors(resp);
        return resp;
    }
    QJsonObject wrapper;
    wrapper.insert("value", v);
    QHttpServerResponse resp(wrapper, code);
    applyCors(resp);
    return resp;
}

QHttpServerResponse RESTManager::errResp(int httpCode, const QString& message)
{
    QJsonObject obj;
    obj.insert("ok", false);
    obj.insert("error", message);
    auto code = static_cast<QHttpServerResponse::StatusCode>(httpCode);
    return jsonResp(obj, code);
}

void RESTManager::applyCors(QHttpServerResponse& resp) const
{
    QHttpHeaders headers = resp.headers();
    headers.append("Access-Control-Allow-Origin", "*");
    headers.append("Access-Control-Allow-Methods", "GET, POST, PUT, OPTIONS");
    headers.append("Access-Control-Allow-Headers", "Content-Type");
    headers.append("Access-Control-Allow-Credentials", "false");
    resp.setHeaders(std::move(headers));
}

void RESTManager::setupRoutes()
{
    auto optionsHandler = [this](const QHttpServerRequest&) {
        QHttpServerResponse resp(QHttpServerResponse::StatusCode::Ok);
        applyCors(resp);
        return resp;
    };

    // Health / status (GET)
    m_httpServer.route("/", QHttpServerRequest::Method::Get, [this](const QHttpServerRequest&) {
        QMutexLocker locker(&device_state_mutex);
        QString state = device_state.isEmpty() ? QStringLiteral("ok") : device_state;
        return jsonResp(QJsonObject{{"status", state}});
    });

    // GET settings
    m_httpServer.route("/api/settings/sensors", QHttpServerRequest::Method::Get, [this](const QHttpServerRequest&) {
        QJsonArray arr = m_sql->getSensorMapJson();
        return jsonResp(arr);
    });

    // PUT settings
    m_httpServer.route("/api/settings/sensors", QHttpServerRequest::Method::Put, [this](const QHttpServerRequest& req) {
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(req.body(), &err);
        if (err.error != QJsonParseError::NoError || !doc.isArray())
        {
            return errResp(400, "invalid json array");
        }

        // merge with existing keys: keep old ones not provided
        QJsonArray current = m_sql->getSensorMapJson();
        QMap<QString, QString> map;
        for (const QJsonValue& v : current)
        {
            if (!v.isObject()) continue;
            QJsonObject o = v.toObject();
            map[o.value("key").toString()] = o.value("name").toString();
        }
        for (const QJsonValue& v : doc.array())
        {
            if (!v.isObject()) continue;
            QJsonObject o = v.toObject();
            QString k = o.value("key").toString();
            QString n = o.value("name").toString();
            if (!k.isEmpty())
            {
                map[k] = n;
            }
        }

        QJsonArray merged;
        for (auto it = map.cbegin(); it != map.cend(); ++it)
        {
            QJsonObject o;
            o.insert("key", it.key());
            o.insert("name", it.value());
            merged.append(o);
        }

        QString errMsg;
        if (!m_sql->updateSensorMapJson(merged, &errMsg))
        {
            return errResp(500, errMsg);
        }
        QJsonObject ok; ok.insert("ok", true);
        return jsonResp(ok);
    });

    m_httpServer.route("/api/settings/sensors", QHttpServerRequest::Method::Options, optionsHandler);

    // GET read frequency
    m_httpServer.route("/api/settings/frequency", QHttpServerRequest::Method::Get, [this](const QHttpServerRequest&) {
        QString errMsg;
        int freq = m_sql->readFrequency(&errMsg);
        if (freq < 0)
        {
            return errResp(500, errMsg.isEmpty() ? QStringLiteral("read frequency error") : errMsg);
        }
        QJsonObject obj; obj.insert("read_frequency", freq);
        return jsonResp(obj);
    });

    m_httpServer.route("/api/settings/frequency", QHttpServerRequest::Method::Options, optionsHandler);

    // PUT read frequency
    m_httpServer.route("/api/settings/frequency", QHttpServerRequest::Method::Put, [this](const QHttpServerRequest& req) {
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(req.body(), &err);
        if (err.error != QJsonParseError::NoError || !doc.isObject())
        {
            return errResp(400, "invalid json object");
        }
        QJsonObject obj = doc.object();
        if (!obj.contains("read_frequency") || !obj.value("read_frequency").isDouble())
        {
            return errResp(400, "read_frequency missing or invalid");
        }
        int val = static_cast<int>(obj.value("read_frequency").toDouble());
        QString errMsg;
        if (!m_sql->setReadFrequency(val, &errMsg))
        {
            return errResp(500, errMsg);
        }
        QJsonObject ok; ok.insert("ok", true); ok.insert("read_frequency", val);
        return jsonResp(ok);
    });

    m_httpServer.route("/api/settings/frequency", QHttpServerRequest::Method::Options, optionsHandler);

    // GET range
    m_httpServer.route("/api/sensor/range", QHttpServerRequest::Method::Get, [this](const QHttpServerRequest& req) {
        QUrlQuery q(req.query());
        qint64 from = 0, to = 0;
        if (!parseIntExpr(q.queryItemValue("from"), from) || !parseIntExpr(q.queryItemValue("to"), to) || to < from)
        {
            return errResp(400, "invalid from/to");
        }
        QJsonArray out;
        QString errMsg;
        if (!m_sql->queryRangeJson(from, to, &out, &errMsg))
        {
            return errResp(500, errMsg);
        }
        return jsonResp(out);
    });

    m_httpServer.route("/api/sensor/range", QHttpServerRequest::Method::Options, optionsHandler);

    // GET range by datetime (ISO string)
    m_httpServer.route("/api/sensor/rangeDateTime", QHttpServerRequest::Method::Get, [this](const QHttpServerRequest& req) {
        QUrlQuery q(req.query());
        qint64 from = 0, to = 0;
        if (!parseDateTimeIso(q.queryItemValue("from"), from) || !parseDateTimeIso(q.queryItemValue("to"), to))
        {
            return errResp(400, "invalid datetime");
        }
        if (to < from)
        {
            return errResp(400, "to < from");
        }
        QJsonArray out;
        QString errMsg;
        if (!m_sql->queryRangeJson(from, to, &out, &errMsg))
        {
            return errResp(500, errMsg);
        }
        return jsonResp(out);
    });

    m_httpServer.route("/api/sensor/rangeDateTime", QHttpServerRequest::Method::Options, optionsHandler);
}

bool RESTManager::parseIntExpr(const QString& text, qint64& outVal)
{
    QRegularExpression re(R"(^\s*(\d+)\s*([+-])?\s*(\d+)?\s*$)");
    QRegularExpressionMatch m = re.match(text);
    if (!m.hasMatch())
        return false;
    bool ok = false;
    qint64 base = m.captured(1).toLongLong(&ok);
    if (!ok) return false;
    if (m.captured(2).isEmpty())
    {
        outVal = base;
        return true;
    }
    qint64 offset = m.captured(3).toLongLong(&ok);
    if (!ok) return false;
    if (m.captured(2) == "-")
        offset = -offset;
    outVal = base + offset;
    return true;
}

bool RESTManager::parseDateTimeIso(const QString& text, qint64& outSecs)
{
    QString s = QUrl::fromPercentEncoding(text.toUtf8()).trimmed();

    auto tryParse = [](const QString& v) -> QDateTime {
        QDateTime dt = QDateTime::fromString(v, Qt::ISODateWithMs);
        if (!dt.isValid())
            dt = QDateTime::fromString(v, Qt::ISODate);
        if (!dt.isValid())
            dt = QDateTime::fromString(v, "yyyy-MM-dd'T'hh:mm:ss'Z'");
        if (dt.isValid() && v.endsWith('Z', Qt::CaseInsensitive))
            dt.setTimeZone(QTimeZone::utc());
        return dt;
    };

    QDateTime dt = tryParse(s);
    if (dt.isValid())
    {
        outSecs = dt.toSecsSinceEpoch();
        return true;
    }

    bool ok = false;
    qint64 seconds = text.toLongLong(&ok);
    if (ok)
    {
        outSecs = seconds;
        return true;
    }
    return false;
}

bool RESTManager::start(quint16 port)
{
    if (!m_sql)
    {
        qWarning() << "RESTManager start failed: SqlManager not set";
        return false;
    }

    setupRoutes();
    if (!m_tcpServer)
    {
        m_tcpServer = std::make_unique<QTcpServer>(this);
    }
    if (!m_tcpServer->listen(QHostAddress::Any, port))
    {
        qWarning() << "HTTP server listen failed on port" << port;
        return false;
    }
    if (!m_httpServer.bind(m_tcpServer.get()))
    {
        qWarning() << "HTTP server bind failed";
        return false;
    }
    qInfo() << "Running on http://127.0.0.1:" << m_tcpServer->serverPort() << "/";
    return true;
}

#pragma once

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include <optional>

namespace heartbeat {

inline constexpr auto kServerName = "CodexHeartbeatWatchdogServer";
inline constexpr int kHeartbeatIntervalMs = 250;
inline constexpr int kHeartbeatTimeoutMs = 1000;
inline constexpr int kMonitorIntervalMs = 250;
inline constexpr int kActionCooldownMs = 1000;

struct Message {
    qint64 processId = 0;
    qint64 counter = 0;
    qint64 sentAtMs = 0;
    QString source;
    QString detail;
    bool automatic = true;

    [[nodiscard]] bool isValid() const
    {
        return processId > 0 && sentAtMs > 0;
    }
};

inline QByteArray serializeLine(const Message &message)
{
    QJsonObject payload;
    payload.insert(QStringLiteral("pid"), QString::number(message.processId));
    payload.insert(QStringLiteral("counter"), QString::number(message.counter));
    payload.insert(QStringLiteral("sentAtMs"), QString::number(message.sentAtMs));
    payload.insert(QStringLiteral("source"), message.source);
    payload.insert(QStringLiteral("detail"), message.detail);
    payload.insert(QStringLiteral("automatic"), message.automatic);

    QByteArray line = QJsonDocument(payload).toJson(QJsonDocument::Compact);
    line.append('\n');
    return line;
}

inline std::optional<Message> parseLine(const QByteArray &line)
{
    const QJsonDocument document = QJsonDocument::fromJson(line.trimmed());
    if (!document.isObject()) {
        return std::nullopt;
    }

    const QJsonObject payload = document.object();
    bool pidOk = false;
    bool counterOk = false;
    bool timeOk = false;

    const qint64 processId = payload.value(QStringLiteral("pid")).toString().toLongLong(&pidOk);
    const qint64 counter = payload.value(QStringLiteral("counter")).toString().toLongLong(&counterOk);
    const qint64 sentAtMs = payload.value(QStringLiteral("sentAtMs")).toString().toLongLong(&timeOk);

    Message message;
    message.processId = processId;
    message.counter = counter;
    message.sentAtMs = sentAtMs;
    message.source = payload.value(QStringLiteral("source")).toString();
    message.detail = payload.value(QStringLiteral("detail")).toString();
    message.automatic = payload.contains(QStringLiteral("automatic"))
        ? payload.value(QStringLiteral("automatic")).toBool(true)
        : true;

    if (!pidOk || !counterOk || !timeOk || !message.isValid()) {
        return std::nullopt;
    }

    return message;
}

} // namespace heartbeat

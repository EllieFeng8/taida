#include "watchdogheartbeatclient.h"

#include "heartbeatprotocol.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QTimer>

WatchdogHeartbeatClient &WatchdogHeartbeatClient::instance()
{
    static WatchdogHeartbeatClient *client = new WatchdogHeartbeatClient(qApp);
    return *client;
}

WatchdogHeartbeatClient::WatchdogHeartbeatClient(QObject *parent)
    : QObject(parent)
{
    m_reconnectTimer = new QTimer(this);
    m_automaticHeartbeatTimer = new QTimer(this);

    connect(m_reconnectTimer, &QTimer::timeout, this, &WatchdogHeartbeatClient::ensureConnected);
    connect(m_automaticHeartbeatTimer, &QTimer::timeout, this, &WatchdogHeartbeatClient::sendAutomaticHeartbeat);
    connect(&m_socket, &QTcpSocket::connected, this, &WatchdogHeartbeatClient::handleConnected);
    connect(&m_socket, &QTcpSocket::disconnected, this, &WatchdogHeartbeatClient::handleDisconnected);
}

void WatchdogHeartbeatClient::initialize(const Settings &settings)
{
    m_settings = settings;
    if (m_settings.hostName.trimmed().isEmpty()) {
        m_settings.hostName = QStringLiteral("127.0.0.1");
    }

    if (m_settings.port == 0) {
        m_settings.port = 45454;
    }

    if (m_settings.sourceName.trimmed().isEmpty()) {
        m_settings.sourceName = QCoreApplication::applicationName();
    }

    if (m_settings.reconnectIntervalMs <= 0) {
        m_settings.reconnectIntervalMs = 1000;
    }

    if (m_settings.automaticIntervalMs <= 0) {
        m_settings.automaticIntervalMs = heartbeat::kHeartbeatIntervalMs;
    }

    m_initialized = true;
    applySettings();
}

void WatchdogHeartbeatClient::start()
{
    if (!m_initialized) {
        initialize();
    }

    m_started = true;
    m_reconnectTimer->start();
    if (m_settings.automaticHeartbeatEnabled) {
        m_automaticHeartbeatTimer->start();
    }
    ensureConnected();
}

void WatchdogHeartbeatClient::stop()
{
    m_started = false;
    m_reconnectTimer->stop();
    m_automaticHeartbeatTimer->stop();
    m_socket.abort();
    updateStatus(QStringLiteral("Heartbeat stopped"), false);
}

void WatchdogHeartbeatClient::setAutomaticHeartbeatEnabled(bool enabled)
{
    m_settings.automaticHeartbeatEnabled = enabled;
    if (!m_started) {
        return;
    }

    if (enabled) {
        m_automaticHeartbeatTimer->start();
    } else {
        m_automaticHeartbeatTimer->stop();
    }
}

void WatchdogHeartbeatClient::setAutomaticInterval(int intervalMs)
{
    if (intervalMs <= 0) {
        return;
    }

    m_settings.automaticIntervalMs = intervalMs;
    m_automaticHeartbeatTimer->setInterval(intervalMs);
}

void WatchdogHeartbeatClient::setCounter(qint64 counter)
{
    m_counter = counter;
}

void WatchdogHeartbeatClient::setDetail(const QString &detail)
{
    m_detail = detail;
}

void WatchdogHeartbeatClient::setPaused(bool paused)
{
    m_paused = paused;
    updateStatus(paused ? QStringLiteral("Heartbeat paused for test") : QStringLiteral("Heartbeat active"),
                 !paused && m_socket.state() == QAbstractSocket::ConnectedState);
}

void WatchdogHeartbeatClient::pulse()
{
    sendHeartbeatInternal(false);
}

void WatchdogHeartbeatClient::pulse(const QString &detail)
{
    sendHeartbeatInternal(false, &detail);
}

void WatchdogHeartbeatClient::pulse(qint64 counter, const QString &detail)
{
    sendHeartbeatInternal(false, &detail, &counter);
}

void WatchdogHeartbeatClient::ensureConnected()
{
    if (m_paused || m_socket.state() == QAbstractSocket::ConnectedState || m_socket.state() == QAbstractSocket::ConnectingState) {
        return;
    }

    m_socket.abort();
    m_socket.connectToHost(m_settings.hostName, m_settings.port);
    updateStatus(QStringLiteral("Connecting to watchdog %1:%2...")
                     .arg(m_settings.hostName, QString::number(m_settings.port)),
                 false);
}

void WatchdogHeartbeatClient::sendAutomaticHeartbeat()
{
    sendHeartbeatInternal(true);
}

void WatchdogHeartbeatClient::handleConnected()
{
    updateStatus(QStringLiteral("Connected to watchdog %1:%2")
                     .arg(m_settings.hostName, QString::number(m_settings.port)),
                 true);
}

void WatchdogHeartbeatClient::handleDisconnected()
{
    updateStatus(QStringLiteral("Watchdog disconnected"), false);
}

void WatchdogHeartbeatClient::applySettings()
{
    m_reconnectTimer->setInterval(m_settings.reconnectIntervalMs);
    m_automaticHeartbeatTimer->setInterval(m_settings.automaticIntervalMs);
}

void WatchdogHeartbeatClient::updateStatus(const QString &statusText, bool connected)
{
    emit statusChanged(statusText, connected);
}

void WatchdogHeartbeatClient::sendHeartbeatInternal(bool automaticSend,
                                                    const QString *detailOverride,
                                                    const qint64 *counterOverride)
{
    if (m_paused || m_socket.state() != QAbstractSocket::ConnectedState) {
        return;
    }

    heartbeat::Message message;
    message.processId = QCoreApplication::applicationPid();
    message.counter = counterOverride ? *counterOverride : m_counter;
    message.sentAtMs = QDateTime::currentMSecsSinceEpoch();
    message.source = m_settings.sourceName;
    message.detail = detailOverride ? *detailOverride : m_detail;
    message.automatic = automaticSend;

    m_socket.write(heartbeat::serializeLine(message));
    m_socket.flush();
}

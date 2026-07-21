#pragma once

#include <QObject>

#include <QtNetwork/QTcpSocket>

class QTimer;

class WatchdogHeartbeatClient : public QObject
{
    Q_OBJECT

public:
    struct Settings {
        QString hostName = QStringLiteral("127.0.0.1");
        quint16 port = 45454;
        QString sourceName;
        int reconnectIntervalMs = 1000;
        int automaticIntervalMs = 250;
        bool automaticHeartbeatEnabled = true;
    };

    static WatchdogHeartbeatClient &instance();

    void initialize(const Settings &settings = Settings());
    void start();
    void stop();

    void setAutomaticHeartbeatEnabled(bool enabled);
    void setAutomaticInterval(int intervalMs);
    void setCounter(qint64 counter);
    void setDetail(const QString &detail);
    void setPaused(bool paused);

    void pulse();
    void pulse(const QString &detail);
    void pulse(qint64 counter, const QString &detail = QString());

signals:
    void statusChanged(const QString &statusText, bool connected);

private slots:
    void ensureConnected();
    void sendAutomaticHeartbeat();
    void handleConnected();
    void handleDisconnected();

private:
    explicit WatchdogHeartbeatClient(QObject *parent = nullptr);

    void applySettings();
    void updateStatus(const QString &statusText, bool connected);
    void sendHeartbeatInternal(bool automaticSend,
                               const QString *detailOverride = nullptr,
                               const qint64 *counterOverride = nullptr);

    Settings m_settings;
    QTcpSocket m_socket;
    QTimer *m_reconnectTimer = nullptr;
    QTimer *m_automaticHeartbeatTimer = nullptr;
    qint64 m_counter = 0;
    QString m_detail;
    bool m_paused = false;
    bool m_started = false;
    bool m_initialized = false;
};

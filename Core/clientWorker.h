#pragma once

#include <qobject>
#include <Qvector>
#include <QTimer>
#include <qvariant>
#include <QModbusTcpClient>
#include <QModbusReply>
class clientWorker : public QObject
{
    Q_OBJECT

public:
    clientWorker(QObject* parent = nullptr);
    ~clientWorker();

    void init();
    void poll();
    void writeSingleCoil(int address, bool value);
    void writeSV(int Addr, double targetSV);
    void WriteSingleHoldingRegisters(bool target ,int slave, int address, int value);
    void ReadHoldingRegisters(bool target, int slave, int startAddress, int number);
    void ReadCoils(bool target, int slave, int startAddress, int number);

    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);

signals:
    void m_5000Coil(QVector <quint16> result);
    void m_5000HodingRegister(QVector <quint16> result);
    void m_6022HodingRegister(QVector <quint16> result);

private:
    QModbusTcpClient* m_5000 = nullptr;
    QModbusTcpClient* m_6022 = nullptr;
    QTimer* m_pollTimer = nullptr;
    QTimer* m_reconnectTimer = nullptr;
    QString m_ip = "192.168.1.201";
    int m_port = 502;
    QString m_ip2 = "192.168.1.202";
    int m_port2 = 502;
};
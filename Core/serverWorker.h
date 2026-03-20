#pragma once

#include <QObject>
#include <QModbusTcpServer>
#include <QModbusDataUnit>
#include <QVector>
#include <QDebug>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject* parent = nullptr);
    ~ServerWorker();
    QModbusTcpServer* m_server = nullptr;

    void init(); // 初始化 Server

signals:
    void modbusDataChanged(QModbusDataUnit::RegisterType table, int address, quint16 value);
public slots:
    // 接收來自 Client 執行緒的資料並更新至 Server 暫存器
    void updateHoldingRegisters(int startAddr, const QVector<quint16>& data);
    void updateHoldingRegister(int startAddr, const quint16 data);

    void updateInputRegisters(int startAddr, const QVector<quint16>& data);
    void updateInputRegister(int startAddr, const quint16 data);
    void updateCoils(int startAddr, const bool data);

    void onDataWritten(QModbusDataUnit::RegisterType table, int address, int size);


private:
    const int m_serverPort = 5020; // 建議先用 5020 測試
    const int m_slaveId = 1;
};
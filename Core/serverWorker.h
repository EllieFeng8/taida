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

    void init(); // 初始化 Server

public slots:
    // 接收來自 Client 執行緒的資料並更新至 Server 暫存器
    void updateHoldingRegisters(int startAddr, const QVector<quint16>& data);

private:
    QModbusTcpServer* m_server = nullptr;
    const int m_serverPort = 5020; // 建議先用 5020 測試
    const int m_slaveId = 1;
};
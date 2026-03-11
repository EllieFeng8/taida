#include "ServerWorker.h"

ServerWorker::ServerWorker(QObject* parent) : QObject(parent) {}

ServerWorker::~ServerWorker() {
    if (m_server) m_server->disconnectDevice();
}

void ServerWorker::init()
{
    m_server = new QModbusTcpServer(this);

    // 設定暫存器範圍：HoldingRegisters 從位址 0 開始，共 100 筆
    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::HoldingRegisters,
        { QModbusDataUnit::HoldingRegisters, 0, 100 });

    m_server->setMap(reg);
    m_server->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "0.0.0.0");
    m_server->setConnectionParameter(QModbusDevice::NetworkPortParameter, m_serverPort);
    m_server->setServerAddress(m_slaveId);

    if (!m_server->connectDevice()) {
        qDebug() << "Modbus Server 啟動失敗:" << m_server->errorString();
    }
    else {
        qDebug() << "Modbus Server 已啟動，Port:" << m_serverPort;
    }
}

void ServerWorker::updateHoldingRegisters(int startAddr, const QVector<quint16>& data)
{
    {
        if (!m_server || m_server->state() != QModbusDevice::ConnectedState) return;

        // 將 ClientWorker 讀到的資料同步到 Server 
        for (int i = 0; i < data.size(); ++i) {
            m_server->setData(QModbusDataUnit::HoldingRegisters, startAddr + i, data[i]);
        }
    }
}
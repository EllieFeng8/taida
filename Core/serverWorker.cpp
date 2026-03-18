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
    reg.insert(QModbusDataUnit::InputRegisters,
        { QModbusDataUnit::InputRegisters, 0, 30 });
    reg.insert(QModbusDataUnit::HoldingRegisters,
        { QModbusDataUnit::HoldingRegisters, 0, 80 });

    m_server->setMap(reg);
    m_server->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "127.0.0.1");
    m_server->setConnectionParameter(QModbusDevice::NetworkPortParameter, m_serverPort);
    m_server->setServerAddress(m_slaveId);
    //m_server->connectDevice();
    if (!m_server->connectDevice()) {
        qDebug() << "FAILED  Modbus Server :" << m_server->errorString();
    }
    else {
        qDebug() << "Modbus Server is START , Port:" << m_serverPort;
    }
}

void ServerWorker::updateInputRegisters(int startAddr, const QVector<quint16>& data)
{
    {
        //if (!m_server || m_server->state() != QModbusDevice::ConnectedState) return;

        // 將 ClientWorker 讀到的資料同步到 Server 
        for (int i = 0; i < data.size(); ++i) {
            //qDebug() << "set InputRegisters";
            m_server->setData(QModbusDataUnit::InputRegisters,startAddr+i, data[i]);
        }
    }
}
void ServerWorker::updateHoldingRegisters(int startAddr, const QVector<quint16>& data)
{
    {
        //if (!m_server || m_server->state() != QModbusDevice::ConnectedState) return;

        // 將 ClientWorker 讀到的資料同步到 Server 
        for (int i = 0; i < data.size(); ++i) {
            //qDebug() << "set HoldingRegisters";
            m_server->setData(QModbusDataUnit::HoldingRegisters, startAddr + i, data[i]);
        }
    }
}
void ServerWorker::updateHoldingRegister(int startAddr, const quint16 data)
{
        //if (!m_server || m_server->state() != QModbusDevice::ConnectedState) return;

        // 將 ClientWorker 讀到的資料同步到 Server 

        //qDebug() << "set HoldingRegisters " << startAddr << "value" << data;
        m_server->setData(QModbusDataUnit::HoldingRegisters, startAddr, data);   
}
void ServerWorker::updateInputRegister(int startAddr, const quint16 data)
{
    //if (!m_server || m_server->state() != QModbusDevice::ConnectedState) return;

    // 將 ClientWorker 讀到的資料同步到 Server 

    //qDebug() << "set HoldingRegisters " << startAddr << "value" << data;
    m_server->setData(QModbusDataUnit::InputRegisters, startAddr, data);
}
#include "ServerWorker.h"
#include <QMutexLocker>
ServerWorker::ServerWorker(QObject* parent) : QObject(parent) {}

ServerWorker::~ServerWorker() {
    if (m_server) {
        m_server->disconnectDevice(); // 中斷所有連線
        delete m_server;
        m_server = nullptr;
    }
}

void ServerWorker::init(int port)
{
    SaveData.resize(100);
    if(m_server)
    {
        m_server->disconnectDevice();
        m_server = nullptr;
        status = false;
        emit server_stat(status);
    }
    m_server = new QModbusTcpServer(this);

    // 設定暫存器範圍：HoldingRegisters 從位址 0 開始，共 100 筆
    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::Coils,
        { QModbusDataUnit::Coils, 0, 20 });
    reg.insert(QModbusDataUnit::InputRegisters,
        { QModbusDataUnit::InputRegisters, 0, 30 });
    reg.insert(QModbusDataUnit::HoldingRegisters,
        { QModbusDataUnit::HoldingRegisters, 0, 80 });

    m_server->setMap(reg);
    m_server->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "127.0.0.1");
    m_server->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
    m_server->setServerAddress(m_slaveId);
    //m_server->connectDevice();

    connect(m_server, &QModbusServer::dataWritten, this, &ServerWorker::onDataWritten);

    if (!m_server->connectDevice()) {
        qDebug() << "FAILED  Modbus Server :" << m_server->errorString();
    }
    else {
        qDebug() << "Modbus Server is START , Port:" << port;
        status = true;
        emit server_stat(status);
    }
}

QVector<quint16>  ServerWorker::getSavedata()
{
    QMutexLocker m_lock(&lock);
    QVector<quint16> data = SaveData;
    data.detach();
    return data;

}

void ServerWorker::updateCoils(int startAddr, const bool data)
{
    //if (!m_server || m_server->state() != QModbusDevice::ConnectedState) return;

    // 將 ClientWorker 讀到的資料同步到 Server 

    //qDebug() << "set HoldingRegisters " << startAddr << "value" << data;
    m_server->setData(QModbusDataUnit::Coils, startAddr, data);
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
        QMutexLocker m_lock(&lock);
        // 將 ClientWorker 讀到的資料同步到 Server 
        for (int i = 0; i < data.size(); ++i) {
            //qDebug() << "set HoldingRegisters";
            m_server->setData(QModbusDataUnit::HoldingRegisters, startAddr + i, data[i]);
            SaveData[startAddr + i] = data[i];
        }
    }
}
void ServerWorker::updateHoldingRegister(int startAddr, const quint16 data)
{
        //if (!m_server || m_server->state() != QModbusDevice::ConnectedState) return;

        // 將 ClientWorker 讀到的資料同步到 Server 
    QMutexLocker m_lock(&lock);

        //qDebug() << "set HoldingRegisters " << startAddr << "value" << data;
        m_server->setData(QModbusDataUnit::HoldingRegisters, startAddr, data);   
        SaveData[startAddr] = data;

}
void ServerWorker::updateInputRegister(int startAddr, const quint16 data)
{
    //if (!m_server || m_server->state() != QModbusDevice::ConnectedState) return;

    // 將 ClientWorker 讀到的資料同步到 Server 

    //qDebug() << "set HoldingRegisters " << startAddr << "value" << data;
    m_server->setData(QModbusDataUnit::InputRegisters, startAddr, data);
}

void ServerWorker::onDataWritten(QModbusDataUnit::RegisterType table, int address, int size) {

    for (int i = 0; i < size; ++i) {
        int currentAddr = address + i;
        quint16 value;

        // 從 Server 的內部資料表讀取該位址的新數值
        if (m_server->data(table, currentAddr, &value)) {
            //qDebug() << " server :  set " << table
            //    << " addr:" << currentAddr
            //    << " new value:" << value;

            // 建議：發送一個帶有位址與數值的自定義訊號給 Manager
            //qDebug() << table << " set " << currentAddr << " = " << value;
            emit modbusDataChanged(table, currentAddr, value);
        }
    }
}
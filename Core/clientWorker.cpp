
#include "clientWorker.h"
#include <QEventLoop>

clientWorker::clientWorker(QObject* parent)
{

}

clientWorker::~clientWorker()
{
}

void clientWorker::init()
{
    if (!m_pollTimer) {

        m_pollTimer = new QTimer(this);
        connect(m_pollTimer, &QTimer::timeout, this, &clientWorker::poll, Qt::DirectConnection);
        // DirectConnection 因為 timer 與 this 在同一 thread (保障)
    }

    if (!m_reconnectTimer) {
        m_reconnectTimer = new QTimer(this);
        m_reconnectTimer->setInterval(2000);
        m_reconnectTimer->setSingleShot(true);
        connect(m_reconnectTimer, &QTimer::timeout, this, &clientWorker::init, Qt::QueuedConnection);
    }
    if (!m_5000) {
        m_5000 = new QModbusTcpClient(this);
        m_5000->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m_ip);
        m_5000->setConnectionParameter(QModbusDevice::NetworkPortParameter, m_port);
        m_5000->setTimeout(1000);
        m_5000->setNumberOfRetries(2);
        connect(m_5000, &QModbusTcpClient::stateChanged,
            this, &clientWorker::onStateChanged);
        connect(m_5000, &QModbusTcpClient::errorOccurred,
            this, &clientWorker::onErrorOccurred);
        m_5000->connectDevice();
    }

    if (!m_6022) {
        m_6022 = new QModbusTcpClient(this);
        m_6022->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m_ip2);
        m_6022->setConnectionParameter(QModbusDevice::NetworkPortParameter, m_port2);
        m_6022->setTimeout(1000);
        m_6022->setNumberOfRetries(2);
        //connect(m_6022, &QModbusTcpClient::stateChanged,
        //    this, &clientWorker::onStateChanged);
        //connect(m_6022, &QModbusTcpClient::errorOccurred,
        //    this, &clientWorker::onErrorOccurred);
        //m_6022->connectDevice();
    }
}
void clientWorker::onStateChanged(QModbusDevice::State state)
{
    if (state == QModbusDevice::ConnectedState) {
        qDebug() << "clientWorker" << "connected.";
        if (m_pollTimer && !m_pollTimer->isActive())
            m_pollTimer->start(50);
    }
    else if (state == QModbusDevice::UnconnectedState) {
        qDebug() << "clientWorker" <<  "disconnected.";

        if (m_pollTimer && m_pollTimer->isActive())
            m_pollTimer->stop();

        if (m_reconnectTimer)
            m_reconnectTimer->start();
    }
}

void clientWorker::onErrorOccurred(QModbusDevice::Error error)
{
    qDebug() << error;
}

void clientWorker::WriteSingleHoldingRegisters(bool target, int slave, int address, int value)
{
    // 如果target = true 代表Adam5000
    // 如果target = false 代表Adam6022
    // slave = 站號
    // address = modbus寫入位置
    // value = 寫入的值
    QModbusTcpClient* client = target ? m_5000 : m_6022;
    if (!client || client->state() != QModbusDevice::ConnectedState) return;

    // 4. 準備 Modbus 寫入單元 (必須寫入 2 個暫存器)
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, address, 1);
    writeUnit.setValue(0, value);
    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);

    if (auto reply = client->sendWriteRequest(writeUnit, slave)) {
        connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
        connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);

        timeoutTimer.start(1000); // 1秒寫入逾時
        loop.exec();

        if (timeoutTimer.isActive()) {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "success " << (target ? "5000" : "6022") << "write :" << address << "value:" << value;
            }
            else {
                qDebug() << "failed:" << reply->errorString();
            }
        }
        else {
            qDebug() << "timeout";
            reply->deleteLater();
        }
        reply->deleteLater();
    }
}

void clientWorker::ReadHoldingRegisters(bool target, int slave, int startAddress, int number)
{
    // 如果target = true 代表Adam5000
    // 如果target = false 代表Adam6022
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
    if (target) {
      
        if (!m_5000) return;
        QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, number);
        QEventLoop loop;
        QVector <quint16> result;

        if (auto reply = m_5000->sendReadRequest(readUnit, slave)) {
            QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
                if (reply->error() == QModbusDevice::NoError) {
                    for(int i =0;i< reply->result().valueCount();i++)
                    {
                        result.append(reply->result().value(i));
                        qDebug() << result[i]<<"\n";
                    }
                    emit m_5000HodingRegister(result);
                }
                else {
                    qDebug() << "Modbus read error:" << reply->errorString();
                }
                reply->deleteLater();
                loop.quit();
                });
            loop.exec();  
        }

        return ;
    }
    else if(!target) 
    {

        if (!m_6022) return;
        QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, number);
        QEventLoop loop;
        QVector <quint16> result;

        if (auto reply = m_6022->sendReadRequest(readUnit, slave)) {
            QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
                if (reply->error() == QModbusDevice::NoError) {
                    for (int i = 0; i < reply->result().valueCount(); i++)
                    {
                        result.append(reply->result().value(i));
                        qDebug() << result[i];
                    }
                    emit m_6022HodingRegister(result);

                }
                else {
                    qDebug() << "Modbus read error:" << reply->errorString();
                }
                reply->deleteLater();
                loop.quit();
                });
            loop.exec();  
        }

        return;
    }
}

void clientWorker::ReadCoils(bool target, int slave, int startAddress, int number)
{
    // 如果target = true 代表Adam5000
    // 如果target = false 代表Adam6022
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
        if (!m_5000) return;
        QModbusDataUnit readUnit(QModbusDataUnit::Coils, 0, 15);
        QEventLoop loop;
        QVector <quint16> result;

        if (auto reply = m_5000->sendReadRequest(readUnit, slave)) {
            QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
                if (reply->error() == QModbusDevice::NoError) {
                    for (int i = 0; i < reply->result().valueCount(); i++)
                    {
                        result.append(reply->result().value(i));
                    }
                    emit m_5000Coil(result);
                }
                else {
                    qDebug() << "Modbus read error:" << reply->errorString();
                }
                reply->deleteLater();
                loop.quit();
                });
            loop.exec();
        }
        return;    
}

void clientWorker::writeSingleCoil(int address, bool value)
{
    qDebug() << "Write single coil addr:" << address << " = " << value;

    if ( m_5000->state() != QModbusDevice::ConnectedState)
    {
        return;
    }

    // 建立 DataUnit: 類型為 Coils, 起始地址為 address, 數量為 1
    QModbusDataUnit unit(QModbusDataUnit::Coils, address, 1);
    unit.setValue(0, value ? 1 : 0); // 設定第一個(也是唯一一個)數值

    // 發送請求
    QModbusReply* reply = m_5000->sendWriteRequest(unit, 1); // 1 為 Server ID
    if (!reply)
    {
        return;
    }

    // 2. 建立區域 EventLoop
    QEventLoop loop;

    // 3. 連接完成訊號到 EventLoop 的 quit 槽
    // 無論成功或失敗，只要 reply 結束就跳出 loop
    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    // 4. 開始事件循環 (程式碼會在此阻塞，但 thread 不會當死，仍能處理其他事件)
    loop.exec();

    // 處理寫入結果

    if (reply->error() == QModbusDevice::NoError) {

    }
    else {
        qDebug() << "Worker" << "write single coil error:" << address << reply->errorString();
    }
    reply->deleteLater();
}


void clientWorker::writeSV(int Addr, double targetSV) {
    if (!m_6022 || m_6022->state() != QModbusDevice::ConnectedState) {
        qDebug() << "錯誤：Modbus 未連線";
        return ;
    }

    // 1. 根據 ADAM-6022 手冊計算數值
    // SV 地址 41020 -> Offset 1019
    // 假設小數位數為 3，需乘以 1000
    int32_t rawValue = static_cast<int32_t>(targetSV * 1000);
    uint16_t highWord = static_cast<uint16_t>((rawValue >> 16) & 0xFFFF);
    uint16_t lowWord = static_cast<uint16_t>(rawValue & 0xFFFF);

    // 準備寫入數據單位 (PID 區塊必須用 Function Code 0x10，即 HoldingRegisters)
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, Addr, 2);
    writeUnit.setValue(0, highWord);
    writeUnit.setValue(1, lowWord);

    // 2. 發送寫入請求
    QModbusReply* reply = m_6022->sendWriteRequest(writeUnit, 1);
    if (!reply) {
        qDebug() << "發送請求失敗：" << m_6022->errorString();
        return ;
    }

    // 3. 使用 QEventLoop 達成同步阻塞
    QEventLoop loop;

    // 當 reply 完成或超時時，退出事件迴圈
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec(); // 程式碼會在此停留，直到收到訊號

    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "同步寫入成功！SV =" << targetSV;
    }
    else {
        qDebug() << "寫入錯誤：" << reply->errorString();
    }

    reply->deleteLater();
}
void clientWorker::poll()
{
    m_pollTimer->stop(); // 暫停計時器，避免重入

    ReadHoldingRegisters(true, 1, 9, 15);


    m_pollTimer->start(); // 全部讀完後，才開啟下一次計時
}
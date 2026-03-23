
#include "clientWorker.h"
#include <QEventLoop>

clientWorker::clientWorker(QObject* parent)
{

}

clientWorker::~clientWorker()
{
    // 停止並釋放計時器
    if (m_pollTimer) {
        m_pollTimer->stop();
        delete m_pollTimer;
        m_pollTimer = nullptr;
    }
    if (m_reconnectTimer) {
        m_reconnectTimer->stop();
        delete m_reconnectTimer;
        m_reconnectTimer = nullptr;
    }

    // 中斷 Modbus 連線並釋放物件
    if (m_5000) {
        m_5000->disconnectDevice();
        delete m_5000;
        m_5000 = nullptr;
    }
    if (m_6022) {
        m_6022->disconnectDevice();
        delete m_6022;
        m_6022 = nullptr;
    }
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
        m_5000->setTimeout(500);
        //m_5000->setNumberOfRetries(2);
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
        m_6022->setTimeout(500);
      /*  m_6022->setNumberOfRetries(2);*/
        connect(m_6022, &QModbusTcpClient::stateChanged,
            this, &clientWorker::onStateChanged);
        connect(m_6022, &QModbusTcpClient::errorOccurred,
            this, &clientWorker::onErrorOccurred);
        m_6022->connectDevice();
    }
}
void clientWorker::onStateChanged(QModbusDevice::State state)
{
    if (state == QModbusDevice::ConnectedState) {
        qDebug() << "clientWorker" << "connected.";
        writeSingleCoil(12, false);
        writeSingleCoil(14, true);
        QTimer::singleShot(1000, this,
            [=]()
            {
 
                Fan_PowerControl(true);

                writeSingleCoil(12, true);
            });   

        if (m_pollTimer && !m_pollTimer->isActive())       
            m_pollTimer->start(50);
        emit connected();
    }
    else if (state == QModbusDevice::UnconnectedState) {
        qDebug() << "clientWorker" << "disconnected.";



    }
}

void clientWorker::onErrorOccurred(QModbusDevice::Error error)
{
    qDebug() << error;
}

void clientWorker::reconnectDevices()
{
    // 如果不是正在連線或已連線，就發起連線請求
    if (m_5000 && m_5000->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-5000 is offline, attempting to reconnect...";
        m_5000->connectDevice();
    }

    if (m_6022 && m_6022->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-6022 is offline, attempting to reconnect...";
        m_6022->connectDevice();
    }
}

void clientWorker::WriteSingleHoldingRegisters(bool target, int slave, int address, int value)
{
    // 如果target = true 代表Adam5000
    // 如果target = false 代表Adam6022
    // slave = 站號
    // address = modbus寫入位置
    // value = 寫入的值
    qDebug() << "write HoldingRegister : " << address << " = " << value;
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

void clientWorker::MotorControl(bool v)
{
    // slave = 站號
    // address = modbus寫入位置
    // value = 寫入的值
    QModbusTcpClient* client =  m_5000 ;
    if (!client || client->state() != QModbusDevice::ConnectedState) return;

    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, 12, 1);
    writeUnit.setValue(0, v);

    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);

    if (auto reply = client->sendWriteRequest(writeUnit, 1)) {
        connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
        connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);

        timeoutTimer.start(1000); // 1秒寫入逾時
        loop.exec();

        if (timeoutTimer.isActive()) {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "success ";
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
void clientWorker::Fan_PowerControl(bool v)
{
    // slave = 站號
    // address = modbus寫入位置
    // value = 寫入的值
    QModbusTcpClient* client = m_5000;
    if (!client || client->state() != QModbusDevice::ConnectedState) return;

    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, 11, 1);
    writeUnit.setValue(0, v);

    QEventLoop loop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);

    if (auto reply = client->sendWriteRequest(writeUnit, 1)) {
        connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
        connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);

        timeoutTimer.start(1000); // 1秒寫入逾時
        loop.exec();

        if (timeoutTimer.isActive()) {
            if (reply->error() == QModbusDevice::NoError) {
                qDebug() << "success ";
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
void clientWorker::Read5000HoldingRegisters(int slave, int startAddress, int number)
{
    
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
    if (!m_5000) return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddress, number);
    QEventLoop loop;
    QVector <quint16> result;
    QVector <quint16> result_in;
    QVector <quint16> result_out;
    if (auto reply = m_5000->sendReadRequest(readUnit, slave)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                for (int i = 0; i < reply->result().valueCount(); i++)
                {
                    result.append(reply->result().value(i));
                    if (i < 16)
                    {
                        result_in.append(reply->result().value(i));
                    }
                    else
                    {
                        result_out.append(reply->result().value(i));
                    }
                }
                MV1 = result[15]/16;
                emit m_5000HodingRegister(result, result_in, result_out);
            }
            else {
                qDebug() << "Modbus adam-5000 read error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
}
void clientWorker::ReadPID1()
{
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
    if (!m_6022) return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 1073, 6);
    QEventLoop loop;
    QVector <quint16> result;
    result.resize(3);
    if (auto reply = m_6022->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit res = reply->result();

                quint16 P0 = res.value(0);
                quint16 P1 = res.value(1);
                quint16 I0 = res.value(2);
                quint16 I1 = res.value(3);
                quint16 D0 = res.value(4);
                quint16 D1 = res.value(5);
                result[0] = (static_cast<int32_t>(P1) << 16) | (P0 & 0xFFFF);
                result[1] = (static_cast<int32_t>(I1) << 16) | (I0 & 0xFFFF);
                result[2] = (static_cast<int32_t>(D1) << 16) | (D0 & 0xFFFF);

                emit m_6022PID1(result);

            }
            else {
                qDebug() << "Modbus read error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
}
void clientWorker::ReadPID2()
{
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
    if (!m_6022) return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 1327, 6);
    QEventLoop loop;
    QVector <quint16> result;
    result.resize(3);
    if (auto reply = m_6022->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit res = reply->result();

                quint16 P0 = res.value(0);
                quint16 P1 = res.value(1);
                quint16 I0 = res.value(2);
                quint16 I1 = res.value(3);
                quint16 D0 = res.value(4);
                quint16 D1 = res.value(5);
                result[0] = (static_cast<int32_t>(P1) << 16) | (P0 & 0xFFFF);
                result[1] = (static_cast<int32_t>(I1) << 16) | (I0 & 0xFFFF);
                result[2] = (static_cast<int32_t>(D1) << 16) | (D0 & 0xFFFF);

                emit m_6022PID2(result);

            }
            else {
                qDebug() << "Modbus read error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
}
void clientWorker::Read6022PV1()
{
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
    if (!m_6022) return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 1019, 2);
    QEventLoop loop;
    QVector <quint16> result;
    result.resize(2);
    if (auto reply = m_6022->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit res = reply->result();

                quint16 reg0 = res.value(0);
                quint16 reg1 = res.value(1);
                quint32 rel = ((static_cast<int32_t>(reg0) << 16) | static_cast<int32_t>(reg1));
                result[0]= rel/10;

                emit m_6022PV1(result);
                qDebug() << "loop-0 SV*1000 = " << result[0];

            }
            else {
                qDebug() << "Modbus read error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
}
void clientWorker::Read6022PV2()
{
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
    if (!m_6022) return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 1275, 2);
    QEventLoop loop;

    QVector <quint16> result;
    result.resize(1);
    if (auto reply = m_6022->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit res = reply->result();

                quint16 reg0 = res.value(0);
                quint16 reg1 = res.value(1);
                quint32 rel = ((static_cast<int32_t>(reg0) << 16) | static_cast<int32_t>(reg1));
                result[0] = rel/10;
                qDebug() << "loop-1 SV*1000 = " << rel;
                emit m_6022PV2(result);

            }
            else {
                qDebug() << "Modbus read error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
}

void clientWorker::read_test()
{
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
    if (!m_6022) return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0, 4);
    QEventLoop loop;
    QVector <quint16> result;
    if (auto reply = m_6022->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit res = reply->result();
                for (int i = 0; i < res.valueCount(); i++)
                {
                    result.append(res.value(i));
                }
                qDebug() << "PV0 = " << result[0] << "&&&" << " PV3 = " << result[3];

                emit R_PV(result);

            }
            else {
                qDebug() << "Modbus read error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
}

void clientWorker::Read6022MV()
{
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
    if (!m_6022) return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 10, 2);
    QEventLoop loop;
    QVector <quint16> result;
    if (auto reply = m_6022->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                const QModbusDataUnit res = reply->result();
                for (int i = 0; i < res.valueCount(); i++)
                {
                    result.append(res.value(i));
                }
                MV1 = result[0];
                MV2 = result[1];

                emit m_6022MV(result);

            }
            else {
                qDebug() << "Modbus read error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
}

void clientWorker::ReadCoils( int slave, int startAddress, int number)
{
    // slave = 站號
    // startAddress = modbus 起始位置
    // number = 讀取數量 例如 nimber = 10 , 代表讀取10筆
        if (!m_5000) return;
        QModbusDataUnit readUnit(QModbusDataUnit::Coils, 0, 11);
        QEventLoop loop;
        QVector <quint16> result;
        QVector <quint16> result_in;
        QVector <quint16> result_out;

        if (auto reply = m_5000->sendReadRequest(readUnit, slave)) {
            QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
                if (reply->error() == QModbusDevice::NoError) {
                    for (int i = 0; i < reply->result().valueCount(); i++)
                    { 
                        result.append(reply->result().value(i));

                        if (i < 11)
                        {
                            result_in.append(reply->result().value(i));
                        }
                        else 
                        {
                            result_out.append(reply->result().value(i));

                        }

                    }
                    emit m_5000Coil(result,result_in,result_out);
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
    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    // 處理寫入結果
    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "set coil = " << value;
    }
    else {
        qDebug() << "Worker" << "write single coil error:" << address << reply->errorString();
    }
    reply->deleteLater();
}
void clientWorker::writeHoldingRegisters(int address, double value, int number)
{
    //qDebug() << "Write single coil addr:" << address << " = " << value;

    if (m_5000->state() != QModbusDevice::ConnectedState)
    {
        return;
    }
    //qDebug() << "set all fan value = " << value;
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, address, number);
    for (int i = 0; i < 17; ++i) {
        writeUnit.setValue(i, value);
    }
    // 發送請求
    QModbusReply* reply = m_5000->sendWriteRequest(writeUnit, 1); // 1 為 Server ID
    if (!reply)
    {
        return;
    }

    // 2. 建立區域 EventLoop
    QEventLoop loop;
    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    // 處理寫入結果
    if (reply->error() == QModbusDevice::NoError) {

    }
    else {
        qDebug() << "Worker" << "write single coil error:" << address << reply->errorString();
    }
    reply->deleteLater();
}

void clientWorker::set6022Mode_1(bool v)
{
    if (!m_6022 || m_6022->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Modbus is not connect";
        return;
    }

    // 1. 根據 ADAM-6022 手冊計算數值

    uint16_t highWord = static_cast<uint16_t>((v >> 16) & 0xFFFF);
    uint16_t lowWord = static_cast<uint16_t>(v & 0xFFFF);


    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 999, 2);
    
    //writeUnit.setValue(0, highWord);
    //writeUnit.setValue(1, lowWord);
    writeUnit.setValue(0, 0);
    writeUnit.setValue(1, v ? 1 : 2);

    QModbusReply* reply = m_6022->sendWriteRequest(writeUnit, 1);
    if (!reply) {
        qDebug() << "set mode failed = " << m_6022->errorString();
        return;
    }


    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "success set 6022 Loop-0  Mode  = " << v;
    }
    else {
        qDebug() << "set mode failed :" << reply->errorString();
    }

    reply->deleteLater();

}

void clientWorker::set_MV(double value) // 假設傳入的是 16bit 數值
{
    if (!m_6022 || m_6022->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Modbus is not connected";
        return;
    }



    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 11, 1);
    writeUnit.setValue(0, value); // 直接設定 16-bit 數值

    // 發送請求 (Server ID 預設為 1)
    QModbusReply* reply = m_6022->sendWriteRequest(writeUnit, 1);

    if (!reply) {
        qDebug() << "Send request failed:" << m_6022->errorString();
        return;
    }

    // 使用 EventLoop 等待非同步結果 (同步化處理)
    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "Successfully wrote AO 1 value:" << value;
    }
    else {
        qDebug() << "Write failed:" << reply->errorString();
    }

    reply->deleteLater();
}

void clientWorker::set6022Mode_2(bool v)
{
    if (!m_6022 || m_6022->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Modbus is not connect";
        return;
    }

    // 1. 根據 ADAM-6022 手冊計算數值

    uint16_t highWord = static_cast<uint16_t>((v >> 16) & 0xFFFF);
    uint16_t lowWord = static_cast<uint16_t>(v & 0xFFFF);


    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 1255, 2);
    writeUnit.setValue(0, 0);
    writeUnit.setValue(1, v ? 1:2);

    QModbusReply* reply = m_6022->sendWriteRequest(writeUnit, 1);
    if (!reply) {
        qDebug() << "set mode failed = " << m_6022->errorString();
        return;
    }


    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "success set 6022 Loop-1  Mode  = " << v;
    }
    else {
        qDebug() << "set mode failed :" << reply->errorString();
    }

    reply->deleteLater();

}

void clientWorker::writeSV1(float targetSV) {
    if (!m_6022 || m_6022->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Modbus is not connect";
        return;
    }

    // 1. 根據 ADAM-6022 手冊計算數值
    // SV 地址 41020 -> Offset 1019
    // 假設小數位數為 3，需乘以 1000
    int32_t rawValue = static_cast<int32_t>(targetSV );
    uint16_t highWord = static_cast<uint16_t>((rawValue >> 16) & 0xFFFF);
    uint16_t lowWord = static_cast<uint16_t>(rawValue & 0xFFFF);


    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 1019, 2);
    writeUnit.setValue(0, highWord);
    writeUnit.setValue(1, lowWord);

    QModbusReply* reply = m_6022->sendWriteRequest(writeUnit, 1);
    if (!reply) {
        qDebug() << "set SV failed = " << m_6022->errorString();
        return;
    }


    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "success set SV =" << targetSV;
    }
    else {
        qDebug() << "set SV failed :" << reply->errorString();
    }

    reply->deleteLater();

}

void clientWorker::writeSV2(float targetSV) {
    if (!m_6022 || m_6022->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Modbus is not connect";
        return;
    }

    // 1. 根據 ADAM-6022 手冊計算數值
    // SV 地址 41020 -> Offset 1019
    // 假設小數位數為 3，需乘以 1000
    int32_t rawValue = static_cast<int32_t>(targetSV );
    uint16_t highWord = static_cast<uint16_t>((rawValue >> 16) & 0xFFFF);
    uint16_t lowWord = static_cast<uint16_t>(rawValue & 0xFFFF);


    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 1275, 2);
    writeUnit.setValue(0, highWord);
    writeUnit.setValue(1, lowWord);

    QModbusReply* reply = m_6022->sendWriteRequest(writeUnit, 1);
    if (!reply) {
        qDebug() << "set SV failed = " << m_6022->errorString();
        return;
    }


    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "success set SV =" << targetSV;
    }
    else {
        qDebug() << "set SV failed :" << reply->errorString();
    }

    reply->deleteLater();

}

void clientWorker::writePID1(double p, double i, double d) {
    if (!m_6022 || m_6022->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Modbus is not connect";
        return;
    }

    int32_t P = static_cast<int32_t>(p );
    uint16_t highWord_P = static_cast<uint16_t>((P >> 16) & 0xFFFF);
    uint16_t lowWord_P = static_cast<uint16_t>(P & 0xFFFF);

    int32_t I = static_cast<int32_t>(i );
    uint16_t highWord_I = static_cast<uint16_t>((I >> 16) & 0xFFFF);
    uint16_t lowWord_I = static_cast<uint16_t>(I & 0xFFFF);

    int32_t D = static_cast<int32_t>(d );
    uint16_t highWord_D = static_cast<uint16_t>((D >> 16) & 0xFFFF);
    uint16_t lowWord_D = static_cast<uint16_t>(D & 0xFFFF);

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 1061, 6);
    writeUnit.setValue(0, highWord_P);
    writeUnit.setValue(1, lowWord_P);
    writeUnit.setValue(2, highWord_I);
    writeUnit.setValue(3, lowWord_I);
    writeUnit.setValue(4, highWord_D);
    writeUnit.setValue(5, lowWord_D);

    // 2. 發送寫入請求
    QModbusReply* reply = m_6022->sendWriteRequest(writeUnit, 1);
    if (!reply) {
        qDebug() << "set PID-0 failed :" << m_6022->errorString();
        return;
    }


    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "success set loop-0  P = " << p << "I = "<<i<<"D = "<<d;
    }
    else {
        qDebug() << "set PID-0 failed :" << reply->errorString();
    }

    reply->deleteLater();
}

void clientWorker::writePID2(double p, double i, double d) {
    if (!m_6022 || m_6022->state() != QModbusDevice::ConnectedState) {
        qDebug() << "Modbus is not connect";
        return;
    }

    int32_t P = static_cast<int32_t>(p );
    uint16_t highWord_P = static_cast<uint16_t>((P >> 16) & 0xFFFF);
    uint16_t lowWord_P = static_cast<uint16_t>(P & 0xFFFF);

    int32_t I = static_cast<int32_t>(i );
    uint16_t highWord_I = static_cast<uint16_t>((I >> 16) & 0xFFFF);
    uint16_t lowWord_I = static_cast<uint16_t>(I & 0xFFFF);

    int32_t D = static_cast<int32_t>(d );
    uint16_t highWord_D = static_cast<uint16_t>((D >> 16) & 0xFFFF);
    uint16_t lowWord_D = static_cast<uint16_t>(D & 0xFFFF);

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 1317, 6);
    writeUnit.setValue(0, highWord_P);
    writeUnit.setValue(1, lowWord_P);
    writeUnit.setValue(2, highWord_I);
    writeUnit.setValue(3, lowWord_I);
    writeUnit.setValue(4, highWord_D);
    writeUnit.setValue(5, lowWord_D);

    // 2. 發送寫入請求
    QModbusReply* reply = m_6022->sendWriteRequest(writeUnit, 1);
    if (!reply) {
        qDebug() << "set PID-1 failed :" << m_6022->errorString();
        return;
    }


    QEventLoop loop;
    QObject::connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    if (reply->error() == QModbusDevice::NoError) {
        qDebug() << "success set loop-1  P = " << p << "I = " << i << "D = " << d;
    }
    else {
        qDebug() << "set PID-1 failed :" << reply->errorString();
    }

    reply->deleteLater();
}

void clientWorker::set_MotorRun(bool v)
{
    motor = v;
    f_MotorCtrl = true;
}
void clientWorker::set_FanPower(bool v)
{
    power = v;
    f_FanCtrl = true;
}
void clientWorker::set_Mode1(bool v)
{
    m_mode1 = v;
    f_setMode1 = true;
}
void clientWorker::set_Mode2(bool v)
{
    m_mode2 = v;
    f_setMode2 = true;
}
void clientWorker::set_5000HoldingRegister(bool t, int addr, double v)
{

    HoldingRegisterRequest req;
    req.target = t;
    req.address = addr;
    req.value =v; 

    m_writeQueue.enqueue(req); // 加入佇列
    // 不需要再設定 f_write5000，後面直接檢查 Queue 是否為空
}
void clientWorker::set_STO(bool v)
{
    f_STO = true;
    if (v) 
    {
        m_STO = false;
    }
    else if (!v)
    {
        m_STO = true;
    }
}
void clientWorker::set_Reset()
{
    f_Reset = true;
}
void clientWorker::set_SV1(double v)
{
    SV1 = v;
    f_setSV1 = true;
}
void clientWorker::set_SV2(double v) 
{
    SV2 = v;
    f_setSV2 = true;
}
void clientWorker::set_AO1(double v)
{
    AO1 = v;
    f_setAO1 = true;
}
void clientWorker::set_PID1(double p, double i, double d)
{
    p1 = p; 
    i1 = i;
    d1 = d;
    f_setPID1 = true;
}
void clientWorker::set_PID2(double p, double i, double d)
{
    p2 = p;
    i2 = i;
    d2 = d;
    f_setPID2 = true;
}
void clientWorker::set_Fan(double v)
{
    m_setALL = v * 40.95;
    f_setFAN = true;
}
void clientWorker::set_Fan1Open(bool v)
{
    fan1_open = v;
    m_Open1 = true;
}
void clientWorker::set_Fan2Open(bool v)
{
    fan2_open = v;
    m_Open2 = true;
}
void clientWorker::set_Fan3Open(bool v)
{
    fan3_open = v;
    m_Open3 = true;
}
void clientWorker::set_Fan4Open(bool v)
{
    fan4_open = v;
    m_Open4 = true;
}
void clientWorker::set_Fan5Open(bool v)
{
    fan5_open = v;
    m_Open5 = true;
}
void clientWorker::set_Fan6Open(bool v)
{
    fan6_open = v;
    m_Open6 = true;
}
void clientWorker::set_Fan7Open(bool v)
{
    fan7_open = v;
    m_Open7 = true;
}
void clientWorker::set_Fan8Open(bool v)
{
    fan8_open = v;
    m_Open8 = true;
}
void clientWorker::set_Fan9Open(bool v)
{
    fan9_open = v;
    m_Open9 = true;
}
void clientWorker::init_flag()
{
    f_setMode1 = false;
    f_STO = false;
    f_setFAN = false;
    f_setSV1 = false;
    f_setSV2 = false;
    f_setPID1 = false;
    f_setPID2 = false;
}

void clientWorker::poll()
{
    m_pollTimer->stop(); // 暫停計時器，避免重入
    bool is5000Connected = (m_5000 && m_5000->state() == QModbusDevice::ConnectedState);
    bool is6022Connected = (m_6022 && m_6022->state() == QModbusDevice::ConnectedState);

    if (!is5000Connected || !is6022Connected) {
        qDebug() << "Device disconnected, skipping poll and attempting reconnect...";
        reconnectDevices();
        // 斷線時，加長下次 poll 的間隔（例如 2秒），避免過度頻繁重試
        m_pollTimer->start(2000);
        return;
    }
    if (f_STO)
    {
        if (m_STO)
        {
            writeSingleCoil(14, m_STO);
            QTimer::singleShot(1000, this,
                [=]()
                {
                    writeSingleCoil(12, true);
                });
        }
        else
        {
            writeSingleCoil(14, m_STO);
            QTimer::singleShot(1000, this,
                [=]()
                {
                    writeSingleCoil(12, false);
                });
        }
        f_STO = false;
    }
    if (f_Reset)
    {
        writeSingleCoil(13, true);
        QTimer::singleShot(1000, this,
            [=]()
            {
                writeSingleCoil(13, false);
            });
        f_Reset = false;

    }
    if (f_MotorCtrl)
    {
        MotorControl(motor);
        f_MotorCtrl = false;
    }
    if (f_FanCtrl)
    {
        Fan_PowerControl(power);
        writeHoldingRegisters(25, 0, 17);
        f_FanCtrl = false;
    }
    if (m_Open1)
    {
        if (!fan1_open)
        {
            WriteSingleHoldingRegisters(true, 1, 25, 0);
        }
        m_Open1 = false;

    }
    if (m_Open2)
    {
        if (!fan2_open)
        {
            WriteSingleHoldingRegisters(true, 1, 26, 0);
        }
        m_Open2 = false;

    }
    if (m_Open3)
    {
        if (!fan3_open)
        {
            WriteSingleHoldingRegisters(true, 1, 27, 0);
        }
        m_Open3 = false;

    }
    if (m_Open4)
    {
        if (!fan4_open)
        {
            WriteSingleHoldingRegisters(true, 1, 32, 0);
        }
        m_Open4 = false;

    }
    if (m_Open5)
    {
        if (!fan5_open)
        {
            WriteSingleHoldingRegisters(true, 1, 33, 0);
        }
        m_Open5 = false;

    }
    if (m_Open6)
    {
        if (!fan6_open)
        {
            WriteSingleHoldingRegisters(true, 1, 34, 0);
        }
        m_Open6 = false;

    }
    if (m_Open7)
    {
        if (!fan7_open)
        {
            WriteSingleHoldingRegisters(true, 1, 35, 0);
        }
        m_Open7 = false;

    }
    if (m_Open8)
    {
        if (!fan8_open)
        {
            WriteSingleHoldingRegisters(true, 1, 40, 0);
        }
        m_Open8 = false;

    }
    if (m_Open9)
    {
        if (!fan9_open)
        {
            WriteSingleHoldingRegisters(true, 1, 41, 0);
        }
        m_Open9 = false;
    }

    if (f_setMode1)
    {
        set6022Mode_1(m_mode1);
        f_setMode1 = false;
    }
    if (f_setMode2)
    {
        set6022Mode_2(m_mode1);
        f_setMode2 = false;
    }
    if (m_mode1)
    {
        writeHoldingRegisters(25, MV1, 17);
    }
    if (m_mode2)
    {
        //writeHoldingRegisters(42, MV2, 1);
    }
    if (f_setFAN)
    {
        writeHoldingRegisters(25, m_setALL, 17);
        f_setFAN = false;
    }

    while (!m_writeQueue.isEmpty())
    {
        HoldingRegisterRequest req = m_writeQueue.dequeue();

        // 釋放鎖定再執行 Modbus 通訊 (避免 Block 其它執行緒太久)
        // 因為 WriteSingleHoldingRegisters 裡面有 QEventLoop，會暫停在這裡直到通訊完成


        WriteSingleHoldingRegisters(req.target, 1, req.address, req.value);

    }

    if (f_setSV1)
    {
        writeSV1(SV1);
        f_setSV1 = false;

    }
    if (f_setSV2)
    {
        writeSV2(SV2);
        f_setSV2 = false;

    }
    if (f_setPID1)
    {
        writePID1(p1, i1, d1);
        f_setPID1 = false;
    }
    if (f_setPID2)
    {
        writePID2(p2, i2, d2);
        f_setPID2 = false;
    }
    if (f_setAO1)
    {
        set_MV(AO1);
        f_setAO1 = false;
    }

    ReadCoils(1, 0, 15);
    Read5000HoldingRegisters(1, 8, 35);
    read_test();
    Read6022PV1();
    Read6022PV2();
    Read6022MV();


    //init_flag();
    m_pollTimer->start(); // 全部讀寫完後，才開啟下一次計時
}


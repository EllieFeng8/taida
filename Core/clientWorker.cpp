
#include "clientWorker.h"
#include <qstring.h>
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
    if (m_201) {
        m_201->disconnectDevice();
        delete m_201;
        m_201 = nullptr;
    }
    if (m_202) {
        m_202->disconnectDevice();
        delete m_202;
        m_202 = nullptr;
    }
    if (m_203) {
        m_203->disconnectDevice();
        delete m_203;
        m_203 = nullptr;
    }
    if (m_204) {
        m_204->disconnectDevice();
        delete m_204;
        m_204 = nullptr;
    }
    if (m_205) {
        m_205->disconnectDevice();
        delete m_205;
        m_205 = nullptr;
    }
    if (m_206) {
        m_206->disconnectDevice();
        delete m_206;
        m_206 = nullptr;
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
        if (!m_pollTimer->isActive())
            m_pollTimer->start(1000);
    }

    if (!m_reconnectTimer) {
        m_reconnectTimer = new QTimer(this);
        m_reconnectTimer->setInterval(1000);
        m_reconnectTimer->setSingleShot(true);
        connect(m_reconnectTimer, &QTimer::timeout, this, &clientWorker::init, Qt::QueuedConnection);
    }

    if (!m_201) {
        m_201 = new QModbusTcpClient(this);
        m_201->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.201");
        m_201->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        m_201->setObjectName("201");
        m_201->setTimeout(500);
        connect(m_201, &QModbusTcpClient::stateChanged,
            this, &clientWorker::onStateChanged_201);
        connect(m_201, &QModbusTcpClient::errorOccurred,
            this, &clientWorker::onErrorOccurred);
        m_201->connectDevice();
    }

    if (!m_202) {
        m_202 = new QModbusTcpClient(this);
        m_202->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.202");
        m_202->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        m_202->setObjectName("202");
        m_202->setTimeout(500);
        connect(m_202, &QModbusTcpClient::stateChanged,
            this, &clientWorker::onStateChanged);
        connect(m_202, &QModbusTcpClient::errorOccurred,
            this, &clientWorker::onErrorOccurred);
        m_202->connectDevice();
    }

    if (!m_203) {
        m_203 = new QModbusTcpClient(this);
        m_203->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.203");
        m_203->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        m_203->setObjectName("203");
        m_203->setTimeout(500);
        connect(m_203, &QModbusTcpClient::stateChanged,
            this, &clientWorker::onStateChanged);
        connect(m_203, &QModbusTcpClient::errorOccurred,
            this, &clientWorker::onErrorOccurred);
        m_203->connectDevice();
    }

    if (!m_204) {
        m_204 = new QModbusTcpClient(this);
        m_204->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.204");
        m_204->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        m_204->setObjectName("204");
        m_204->setTimeout(500);
        connect(m_204, &QModbusTcpClient::stateChanged,
            this, &clientWorker::onStateChanged);
        connect(m_204, &QModbusTcpClient::errorOccurred,
            this, &clientWorker::onErrorOccurred);
        m_204->connectDevice();
    }

    if (!m_205) {
        m_205 = new QModbusTcpClient(this);
        m_205->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.205");
        m_205->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        m_205->setObjectName("205");
        m_205->setTimeout(500);
        connect(m_205, &QModbusTcpClient::stateChanged,
            this, &clientWorker::onStateChanged);
        connect(m_205, &QModbusTcpClient::errorOccurred,
            this, &clientWorker::onErrorOccurred);
        m_205->connectDevice();
    }

    if (!m_206) {
        m_206 = new QModbusTcpClient(this);
        m_206->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.206");
        m_206->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        m_206->setObjectName("206");
        m_206->setTimeout(500);
        connect(m_206, &QModbusTcpClient::stateChanged,
            this, &clientWorker::onStateChanged);
        connect(m_206, &QModbusTcpClient::errorOccurred,
            this, &clientWorker::onErrorOccurred);
        m_206->connectDevice();
    }
    if (!m_6022) {
        m_6022 = new QModbusTcpClient(this);
        m_6022->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.1.207");
        m_6022->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        m_6022->setObjectName("6022");
        m_6022->setTimeout(500);
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
    }
    else if (state == QModbusDevice::UnconnectedState) {
        qDebug() << "clientWorker" << "disconnected.";
    }
}
void clientWorker::onStateChanged_201(QModbusDevice::State state)
{
    if (state == QModbusDevice::ConnectedState) {
        qDebug() << "client 201" << "connected.";
        //writeSingleCoil(12, false);
        writeSingleCoil(m_201,19, true);//STO 點位  on=解除STO
        Fan_PowerControl(true);
    //    //TODO 確認馬達及STO點位 連線時啟動STO
        QTimer::singleShot(1000, this,
            [=]()
            {

                //Fan_PowerControl(true);//控制風扇
                //連線時預設風扇停止
                // 
                writeSingleCoil(m_201,17, true);//控制馬達
            });


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
    if (m_201 && m_201->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-6250 is offline, attempting to reconnect...";
        m_201->connectDevice();
    }
    if (m_202 && m_202->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-6217-1 is offline, attempting to reconnect...";
        m_202->connectDevice();
    }
    if (m_203 && m_203->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-6217-2 is offline, attempting to reconnect...";
        m_203->connectDevice();
    }
    if (m_204 && m_204->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-6224-1 is offline, attempting to reconnect...";
        m_204->connectDevice();
    }
    if (m_205 && m_205->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-6224-2 is offline, attempting to reconnect...";
        m_205->connectDevice();
    }
    if (m_206 && m_206->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-6224-3 is offline, attempting to reconnect...";
        m_206->connectDevice();
    }
    if (m_6022 && m_6022->state() == QModbusDevice::UnconnectedState) {
        qDebug() << "ADAM-6022 is offline, attempting to reconnect...";
        m_6022->connectDevice();
    }
}

void clientWorker::WriteSingleHoldingRegisters(QModbusTcpClient* client, int slave, int address, int value)
{
    qDebug() << "write HoldingRegister : " << address << " = " << value;

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
                qDebug() << "success " << client->objectName() << "write :" << address << "value:" << value;
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
    //TODO 確認並寫入馬達開關的coil位置
    //QModbusTcpClient* client =  m_5000 ;
    //if (!client || client->state() != QModbusDevice::ConnectedState) return;

    //QModbusDataUnit writeUnit(QModbusDataUnit::Coils, 12, 1);
    //writeUnit.setValue(0, v);

    //QEventLoop loop;
    //QTimer timeoutTimer;
    //timeoutTimer.setSingleShot(true);

    //if (auto reply = client->sendWriteRequest(writeUnit, 1)) {
    //    connect(reply, &QModbusReply::finished, &loop, &QEventLoop::quit);
    //    connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);

    //    timeoutTimer.start(1000); // 1秒寫入逾時
    //    loop.exec();

    //    if (timeoutTimer.isActive()) {
    //        if (reply->error() == QModbusDevice::NoError) {
    //            qDebug() << "success ";
    //        }
    //        else {
    //            qDebug() << "failed:" << reply->errorString();
    //        }
    //    }
    //    else {
    //        qDebug() << "timeout";
    //        reply->deleteLater();
    //    }
    //    reply->deleteLater();
    //}
}
void clientWorker::Fan_PowerControl(bool v)
{
    QModbusTcpClient* client = m_201;
    if (!client || client->state() != QModbusDevice::ConnectedState) return;
    
      //TODO 確認並寫入風扇開關的正確位置
 
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils, 16, 1);
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
void clientWorker::ReadPID1()
{
    if (!m_6022) return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 1061, 6);
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
                quint32 P = ((static_cast<int32_t>(P0) << 16) | static_cast<int32_t>(P1));
                quint32 I = ((static_cast<int32_t>(I0) << 16) | static_cast<int32_t>(I1));
                quint32 D = ((static_cast<int32_t>(D0) << 16) | static_cast<int32_t>(D1));
                qDebug() << "PID loop0 =" << P <<"," << I << "," << D;
                result[0] = P;
                result[1] = I;
                result[2] = D;

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
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 1317, 6);
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
                quint32 P = ((static_cast<int32_t>(P0) << 16) | static_cast<int32_t>(P1));
                quint32 I = ((static_cast<int32_t>(I0) << 16) | static_cast<int32_t>(I1));
                quint32 D = ((static_cast<int32_t>(D0) << 16) | static_cast<int32_t>(D1));

                result[0] = P;
                result[1] = I;
                result[2] = D;
                qDebug() << "PID loop1 =" << P << "," << I << "," << D;

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

QVector <quint16> clientWorker::readAdam6250DI()
{
    //DI 0 = 電源相位檢出
    //DI 4 = 水泵異常
    QModbusDataUnit readUnit(QModbusDataUnit::Coils, 0, 8);
    QEventLoop loop;
    QVector <quint16> result;
    if (!m_201) return result;
    if (m_201->state() != QModbusDevice::ConnectedState) {
        qDebug() << m_201 << "not connected";
        return result;
    }
    if (auto reply = m_201->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                for (int i = 0; i < reply->result().valueCount(); i++)
                {
                    result.append(reply->result().value(i));
                }
            }
            else {
                qDebug() << "201 read DI error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
    return result;
}
QVector <quint16> clientWorker::readAdam6250DO()
{
    
    QModbusDataUnit readUnit(QModbusDataUnit::Coils, 16, 7);
    QEventLoop loop;
    QVector <quint16> result;
    if (!m_201) return result;
    if (m_201->state() != QModbusDevice::ConnectedState) {
        qDebug() << m_201 << "not connected";
        return result;
    }
    if (auto reply = m_201->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                for (int i = 0; i < reply->result().valueCount(); i++)
                {
                    result.append(reply->result().value(i));
                }
            }
            else {
                qDebug() << "201 read DO error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
    return result;
}
QVector <quint16> clientWorker::readAdam6217AI(QModbusTcpClient* client)
{
    QVector <quint16> result;
    if (!client) return result;
    if (client->state() != QModbusDevice::ConnectedState) {
        qDebug() << client->objectName() << "not connected";
        return result;
    }
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0, 8);
    QEventLoop loop;


    if (auto reply = client->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                for (int i = 0; i < reply->result().valueCount(); i++)
                {
                    result.append(reply->result().value(i));
                }
            }
            else {
                qDebug() << client->objectName() << "read AI error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
    return result;
}
QVector <quint16> clientWorker::readAdam6224AO(QModbusTcpClient* client)
{
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0, 4);
    QEventLoop loop;
    QVector <quint16> result;
    if (!client) return result;
    if (client->state() != QModbusDevice::ConnectedState) {
        qDebug() << client->objectName() << "not connected";
        return result;
    }

    if (auto reply = client->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                for (int i = 0; i < reply->result().valueCount(); i++)
                {
                    result.append(reply->result().value(i));
                }
            }
            else {
                qDebug() << client->objectName() << "read AO error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
    return result;
}
QVector <quint16> clientWorker::readAdam6224DI(QModbusTcpClient* client)
{
    QModbusDataUnit readUnit(QModbusDataUnit::Coils, 0, 4);
    QEventLoop loop;
    QVector <quint16> result;
    if (!client) return result;
    if (client->state() != QModbusDevice::ConnectedState) {
        qDebug() << client->objectName() << "not connected";
        return result;
    }
    if (auto reply = client->sendReadRequest(readUnit, 1)) {
        QObject::connect(reply, &QModbusReply::finished, &loop, [&]() {
            if (reply->error() == QModbusDevice::NoError) {
                for (int i = 0; i < reply->result().valueCount(); i++)
                {
                    result.append(reply->result().value(i));
                }
            }
            else {
                qDebug() << client->objectName() <<" read DI error:" << reply->errorString();
            }
            reply->deleteLater();
            loop.quit();
            });
        loop.exec();
    }
    return result;
}
void clientWorker::writeSingleCoil(QModbusTcpClient* client ,int address, bool value)
{
    qDebug() << "Write single coil addr:" << address << " = " << value;

    if (client->state() != QModbusDevice::ConnectedState)
    {
        return;
    }

    // 建立 DataUnit: 類型為 Coils, 起始地址為 address, 數量為 1
    QModbusDataUnit unit(QModbusDataUnit::Coils, address, 1);
    unit.setValue(0, value ? 1 : 0); // 設定第一個(也是唯一一個)數值

    // 發送請求
    QModbusReply* reply = client->sendWriteRequest(unit, 1); // 1 為 Server ID
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
void clientWorker::writeHoldingRegisters(QModbusTcpClient* client,int address, double value, int number)
{
    //qDebug() << "Write single coil addr:" << address << " = " << value;

    if (client->state() != QModbusDevice::ConnectedState)
    {
        return;
    }
    //qDebug() << "set all fan value = " << value;
    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, address, number);
    for (int i = 0; i < 17; ++i) {
        writeUnit.setValue(i, value);
    }
    // 發送請求
    QModbusReply* reply = client->sendWriteRequest(writeUnit, 1); // 1 為 Server ID
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
    writeUnit.setValue(1, v ? 1 : 0);

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
    writeUnit.setValue(1, v ? 1:0);

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
void clientWorker::set_204HoldingRegister(int addr, double v)
{

    HoldingRegisterRequest req;
    req.client = m_204;
    req.address = addr;
    req.value =v; 
    if (!m_isFanSTO) //如果在STO情況下 寫入的數值不進入queue (不寫入)
    {
        m_writeQueue.enqueue(req);
    } // 加入佇列
    // 不需要再設定 f_write5000，後面直接檢查 Queue 是否為空
}
void clientWorker::set_205HoldingRegister(int addr, double v)
{

    HoldingRegisterRequest req;
    req.client = m_205;
    req.address = addr;
    req.value =v; 
    if (!m_isFanSTO) //如果在STO情況下 寫入的數值不進入queue (不寫入)
    {
        m_writeQueue.enqueue(req);
    } 
}
void clientWorker::set_206HoldingRegister(int addr, double v)
{

    HoldingRegisterRequest req;
    req.client = m_206;
    req.address = addr;
    req.value = v;
    if (!m_isFanSTO) //如果在STO情況下 寫入的數值不進入queue (不寫入)
    {
        m_writeQueue.enqueue(req);
    }
}
void clientWorker::set_6022HoldingRegister(int addr, double v)
{

    HoldingRegisterRequest req;
    req.client = m_6022;
    req.address = addr;
    req.value = v;
    if (!m_isSTO || m_isFanSTO) //如果在STO情況下 寫入的數值不進入queue (不寫入)
    {
        m_writeQueue.enqueue(req);
    }
}
void clientWorker::set_STO(bool v)
{
    m_isSTO = v;
    f_STO = true;
    if (v) 
    {
        m_STO = false;
    }
    else if (!v)
    {
        m_STO = true;
    }
    qDebug() << "set motor power = " << m_STO;

}
void clientWorker::set_STO2(bool v)
{
    m_isSTO2 = v;
    f_STO2 = true;
    if (v)
    {
        m_STO2 = false;
    }
    else if (!v)
    {
        m_STO2 = true;
    }
    qDebug() << "set fan power = "<<m_STO2;
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
    qDebug() << "set AO1 = "<<v;
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
    bool is201Connected = (m_201 && m_201->state() == QModbusDevice::ConnectedState);
    bool is202Connected = (m_202 && m_202->state() == QModbusDevice::ConnectedState);
    bool is203Connected = (m_203 && m_203->state() == QModbusDevice::ConnectedState);
    bool is204Connected = (m_204 && m_204->state() == QModbusDevice::ConnectedState);
    bool is205Connected = (m_205 && m_205->state() == QModbusDevice::ConnectedState);
    bool is206Connected = (m_206 && m_206->state() == QModbusDevice::ConnectedState);

    bool is6022Connected = (m_6022 && m_6022->state() == QModbusDevice::ConnectedState);

    if (!is201Connected || !is6022Connected|| !is202Connected || !is203Connected || !is204Connected || !is205Connected || !is206Connected  ) {
        qDebug() << "Device disconnected, skipping poll and attempting reconnect...";
        reconnectDevices();
        // 斷線時，加長下次 poll 的間隔（例如 2秒），避免過度頻繁重試
        m_pollTimer->start(1000);
        return;
    }
    auto _201DI = readAdam6250DI();
    auto _201DO = readAdam6250DO();
    auto _202AI = readAdam6217AI(m_202);
    auto _203AI = readAdam6217AI(m_203);
    auto _204DI = readAdam6224DI(m_204);
    auto _204AO = readAdam6224AO(m_204);
    auto _205AO = readAdam6224AO(m_205);
    auto _206AO = readAdam6224AO(m_206);
    readInput_Data data;
    data.DI_201 = _201DI;
    data.DO_201 = _201DO;
    data.AI_202 = _202AI;
    data.AI_203 = _203AI;
    data.DI_204 = _204DI;
    data.AO_204 = _204AO;
    data.AO_205 = _205AO;
    data.AO_206 = _206AO;
    if (!data.AI_202.isEmpty() && !data.AI_203.isEmpty() && !data.AO_204.isEmpty() && !data.AO_205.isEmpty() && !data.AO_206.isEmpty())
    {
        emit input_DATA(data);
    }
    read_test();
    if (f_STO)
    {
        if (m_STO)
        {
            writeSingleCoil(m_201,19, m_STO);
            QTimer::singleShot(1000, this,
                [=]()
                {
                    writeSingleCoil(m_201,17, true);
                });
        }
        else
        {
            writeSingleCoil(m_201,19, m_STO);
            QTimer::singleShot(1000, this,
                [=]()
                {
                    writeSingleCoil(m_201,17, false);
                });
        }
        f_STO = false;
    }
    if (f_STO2)
    {
        writeSingleCoil(m_201, 16, m_STO2);

        f_STO2 = false;
    }
    if (f_Reset)
    {
        //writeSingleCoil(13, true);
        QTimer::singleShot(1000, this,
            [=]()
            {
                //writeSingleCoil(13, false);
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
        writeHoldingRegisters(m_204,1, 0, 3);
        writeHoldingRegisters(m_205, 0, 0, 4);
        writeHoldingRegisters(m_206, 0, 0, 2);

        f_FanCtrl = false;
    }
    if (m_Open1)
    {
        if (!fan1_open)
        {
            WriteSingleHoldingRegisters(m_204, 1, 1, 0);
            //將第一台風扇的AO位置寫入0
        }
        m_Open1 = false;

    }
    if (m_Open2)
    {
        if (!fan2_open)
        {
            WriteSingleHoldingRegisters(m_204, 1, 2, 0);

            //將第二台風扇的AO位置寫入0

        }
        m_Open2 = false;

    }
    if (m_Open3)
    {
        if (!fan3_open)
        {
            WriteSingleHoldingRegisters(m_204, 1, 3, 0);

            //將第三台風扇的AO位置寫入0

        }
        m_Open3 = false;

    }
    if (m_Open4)
    {
        if (!fan4_open)
        {
            WriteSingleHoldingRegisters(m_205, 1, 0, 0);

            //將第四台風扇的AO位置寫入0

        }
        m_Open4 = false;

    }
    if (m_Open5)
    {
        if (!fan5_open)
        {
            WriteSingleHoldingRegisters(m_205, 1, 1, 0);

            //將第五台風扇的AO位置寫入0

        }
        m_Open5 = false;

    }
    if (m_Open6)
    {
        if (!fan6_open)
        {
            WriteSingleHoldingRegisters(m_205, 1, 2, 0);

            //將第六台風扇的AO位置寫入0

        }
        m_Open6 = false;

    }
    if (m_Open7)
    {
        if (!fan7_open)
        {
            WriteSingleHoldingRegisters(m_205, 1, 3, 0);

            //將第七台風扇的AO位置寫入0

        }
        m_Open7 = false;

    }
    if (m_Open8)
    {
        if (!fan8_open)
        {
            WriteSingleHoldingRegisters(m_206, 1, 0, 0);

            //將第八台風扇的AO位置寫入0

        }
        m_Open8 = false;

    }
    if (m_Open9)
    {
        if (!fan9_open)
        {
            WriteSingleHoldingRegisters(m_206, 1, 1, 0);

            //將第九台風扇的AO位置寫入0

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
        set6022Mode_2(m_mode2);
        f_setMode2 = false;
    }
    if (m_mode1)
    {
        writeHoldingRegisters(m_204, 1, MV1, 3);
        writeHoldingRegisters(m_205, 0, MV1, 4);
        writeHoldingRegisters(m_204, 0, MV1, 2);
        emit pidcontrolFan(MV1/40.95);
    }
    if (m_mode2)
    {
        emit pidcontroloutvalue(MV2/40.95);
    }
    if (f_setFAN)
    {
        if (power) {
            writeHoldingRegisters(m_204, 1, m_setALL, 3);
            writeHoldingRegisters(m_205, 0, m_setALL, 4);
            writeHoldingRegisters(m_204, 0, m_setALL, 2);

            f_setFAN = false;
        }
    }

    while (!m_writeQueue.isEmpty())
    {
        HoldingRegisterRequest req = m_writeQueue.dequeue();

        // 釋放鎖定再執行 Modbus 通訊 (避免 Block 其它執行緒太久)
        // 因為 WriteSingleHoldingRegisters 裡面有 QEventLoop，會暫停在這裡直到通訊完成

        
        WriteSingleHoldingRegisters(req.client, 1, req.address, req.value);

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

    Read6022PV1();
    Read6022PV2();
    Read6022MV();
    ReadPID2();
    ReadPID1();
    //init_flag();
    m_pollTimer->start(); // 全部讀寫完後，才開啟下一次計時
}


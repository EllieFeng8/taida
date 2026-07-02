#include <QModbusReply>
#include "MS300.h"

MS300::MS300(QObject* parent) : QObject(parent) {}


void MS300::initPort() {
    m_modbus = new QModbusRtuSerialClient(this);
    m_modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM2");
    m_modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    m_modbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_modbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbus->setTimeout(200);
    m_modbus->setNumberOfRetries(3);
    if (m_modbus->connectDevice()) {
        qDebug() << "COM2 connect";
        m_pollTimer = new QTimer(this);
        connect(m_pollTimer, &QTimer::timeout, this, &MS300::onPollTimeout);
        m_pollTimer->start(100);
}
    else
    {
        qDebug() << "connect COM2 fail";
    }
}
void MS300::onPollTimeout()
{

    // 1. 設定讀取請求：目前的故障代碼地址為 0x2100，讀取 1 個暫存器
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0x2100, 1);

    // 2. 發送請求 (假設從站 ID 為 1，請根據實際參數 09-00 設定修改)
    if (auto* reply = m_modbus->sendReadRequest(readUnit, 1)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const QModbusDataUnit unit = reply->result();
                    // 3. 取得異常代碼數值
                    int errorCode = unit.value(0);

                        //qDebug() << "error ID:" << errorCode;
                        emit dataUpdated(errorCode);
                }
                else {
                    //qDebug() << "讀取失敗:" << reply->errorString();
                }
                reply->deleteLater();
                });
        }
        else {
            qDebug() << "error";

            reply->deleteLater(); // 已結束但發生錯誤
        }
    }
}

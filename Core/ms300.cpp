#include <QModbusReply>
#include "MS300.h"

MS300::MS300(QObject* parent) : QObject(parent) {}


void MS300::initPort()
{
    if (m_isShuttingDown) {
        return;
    }

    if (!m_modbus) {
        m_modbus = new QModbusRtuSerialClient(this);
        m_modbus->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM2");
        m_modbus->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        m_modbus->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        m_modbus->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        m_modbus->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        m_modbus->setTimeout(200);
        m_modbus->setNumberOfRetries(3);
        m_pollTimer = new QTimer(this);
        connect(m_pollTimer, &QTimer::timeout, this, &MS300::onPollTimeout);
        connect(m_modbus, &QModbusDevice::stateChanged, this, [this](QModbusDevice::State state) {
            if (state == QModbusDevice::ConnectedState) {
                qDebug() << "COM2 connect";
                m_reconnectScheduled = false;
                m_pollTimer->start(100);
            } else if (state == QModbusDevice::UnconnectedState) {
                m_pollTimer->stop();
                m_requestInFlight = false;
                scheduleReconnect();
            }
        });
    }

    if (m_modbus->state() == QModbusDevice::ConnectedState ||
        m_modbus->state() == QModbusDevice::ConnectingState) {
        return;
    }

    if (!m_modbus->connectDevice()) {
        qWarning() << "COM2 connect failed:" << m_modbus->errorString();
        scheduleReconnect();
    }
}

void MS300::scheduleReconnect()
{
    if (m_isShuttingDown || m_reconnectScheduled) {
        return;
    }

    m_reconnectScheduled = true;
    QTimer::singleShot(2000, this, [this]() {
        m_reconnectScheduled = false;
        initPort();
    });
}

void MS300::onPollTimeout()
{
    if (!m_modbus ||
        m_modbus->state() != QModbusDevice::ConnectedState ||
        m_requestInFlight) {
        return;
    }

    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 0x2100, 1);
    QModbusReply* reply = m_modbus->sendReadRequest(readUnit, 1);
    if (!reply) {
        m_modbus->disconnectDevice();
        scheduleReconnect();
        return;
    }

    m_requestInFlight = true;
    const auto handleReply = [this, reply]() {
        m_requestInFlight = false;
        if (reply->error() == QModbusDevice::NoError) {
            const QModbusDataUnit unit = reply->result();
            emit dataUpdated(unit.value(0));
        } else {
            qWarning() << "MS300 read failed:" << reply->errorString();
            if (m_modbus && m_modbus->state() != QModbusDevice::UnconnectedState) {
                m_modbus->disconnectDevice();
            }
            scheduleReconnect();
        }
        reply->deleteLater();
    };
    connect(reply, &QModbusReply::finished, this, handleReply);
    if (reply->isFinished()) {
        handleReply();
    }
}

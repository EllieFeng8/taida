#pragma once

#include <QObject>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QTimer>
#include <QDebug>
#include <qvariant>
#include <QModbusClient>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QModbusRtuSerialClient>
#include <qthread>

class MS300 : public QObject {
    Q_OBJECT

public:
    explicit MS300(QObject* parent = nullptr);

    //static MS300* instance() {
    //    static MS300 _instance;
    //    return &_instance;
    //}
    MS300(const MS300&) = delete;
    MS300& operator=(const MS300&) = delete;


signals:
    void dataUpdated(int v);

public slots:
    void initPort();
    // UI 呼叫此 Slot 來更新value
    void updateFreqCache(int id, double hz) {
        if (id >= 1 && id <= 10) m_targetFreqs[id] = hz;
    }

    void setTargetFrequency(double hz) {
        if (hz < 0.0) hz = 0.0;
        if (hz > 600.0) hz = 600.0;
        if (m_targetHz != hz) { // 如果數值真的有變動
            m_targetHz = hz;
            m_needWriteID2 = true; // 標記需要寫入
        }
    }// UI 呼叫此 Slot 來更新運轉狀態
    void updateControlCache(int id, quint16 cmd) {
        if (id >= 1 && id <= 10) m_targetCmds[id] = cmd;
    }
    void updateResetCache(int id, quint16 val) {
        if (id >= 1 && id <= 10) m_targetReset[id] = val;
    }
    void cleanup() {
        if (m_pollTimer) {
            m_pollTimer->stop();
            m_pollTimer->deleteLater();
            m_pollTimer = nullptr;
        }
        if (m_modbus) {
            m_modbus->disconnectDevice();
            m_modbus->deleteLater();
            m_modbus = nullptr;
        }
        QThread::currentThread()->quit();

        qDebug() << "MS300 resources cleaned up.";
    }
private slots:
    void onPollTimeout();

private:
    double m_targetFreqs[11]; //  2001H (頻率)
    quint16 m_targetCmds[11]; //  2000H (mode)
    quint16 m_targetReset[11];//  2002H (Reset 指令位址)
    QModbusRtuSerialClient* m_modbus = nullptr;
    QTimer* m_pollTimer = nullptr;
    quint16 m_accelDecelWord = 0x0000;
    int m_currentIndex = 1;
    double m_targetHz = 0.0;
    bool m_needWriteID2 = false;
};
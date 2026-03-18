#pragma once

#include <qobject>
#include <Qvector>
#include <QTimer>
#include <qvariant>
#include <QModbusTcpClient>
#include <QModbusReply>
struct WriteRequest {
    QModbusClient* targetDevice; // m_5000 或 m_6022
    int address;
    QVector<uint16_t> values;    // 存放要寫入的一或多個值
};

class clientWorker : public QObject
{
    Q_OBJECT

public:
    clientWorker(QObject* parent = nullptr);
    ~clientWorker();

    void init();
    void init_flag();
    void poll();

    void writeSingleCoil(int address, bool value);

    //寫入
    void set_SV1(double v);
    void set_SV2(double v);
    void set_PID1(double p,double i,double d);
    void set_PID2(double p, double i, double d);
    void set_Fan(double v);
    void write5000(int addr, double v);
    
    void writeSV1(double targetSV);
    void writeSV2(double targetSV);
    void writePID1( double p, double i, double d);
    void writePID2( double p, double i, double d);
    void writeHoldingRegisters(int address, double value, int number);
    void WriteSingleHoldingRegisters(bool target ,int slave, int address, int value);
    //讀取
    void Read5000HoldingRegisters( int slave, int startAddress, int number); 

    void Read6022PV1(); //第一組PV 
    void Read6022PV2(); //第二組PV
    void Read6022MV(); //PID 輸出

    void ReadPID1(); //第一組PID
    void ReadPID2(); //第二組PID 
    void ReadCoils( int slave, int startAddress, int number); 

    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);
    bool m_mode1 = false;
    bool m_mode2 = false;

signals:
    void m_5000Coil(QVector <quint16> result, QVector <quint16> input, QVector <quint16> output);
    void m_5000HodingRegister(QVector <quint16> result, QVector <quint16> input, QVector <quint16> output);
    
    void m_6022PV1(QVector <quint16> result);
    void m_6022SV1(QVector <quint16> result);
    void m_6022PV2(QVector <quint16> result);
    void m_6022SV2(QVector <quint16> result);
    void m_6022MV(QVector <quint16> result);
    void m_6022PID1(QVector <quint16> result);
    void m_6022PID2(QVector <quint16> result);

private:
    WriteRequest m_pendingWrite;
    QModbusTcpClient* m_5000 = nullptr;
    QModbusTcpClient* m_6022 = nullptr;
    QTimer* m_pollTimer = nullptr;
    QTimer* m_reconnectTimer = nullptr;
    QString m_ip = "192.168.1.201";
    int m_port = 502;
    QString m_ip2 = "192.168.1.202";
    int m_port2 = 502;
    double MV1 = 0.0;
    double MV2 = 0.0;
    double SV1 = 0.0;
    double SV2 = 0.0;
    double p1 = 0.0;
    double p2 = 0.0;
    double i1 = 0.0;
    double i2 = 0.0;
    double d1 = 0.0;
    double d2 = 0.0;
    double m_setALL = 0.0;
    bool f_setSV1 = false;
    bool f_setSV2 = false;
    bool f_setPID1 = false;
    bool f_setPID2 = false;
    bool f_write5000 = false;
    bool f_setFAN = false;
};
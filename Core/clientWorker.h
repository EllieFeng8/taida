#pragma once

#include <qobject>
#include <Qvector>
#include <QTimer>
#include <QMutex>
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
    void set_MV(double v);
    void set_MotorRun(bool v);
    void set_FanPower(bool v);
    void set_Fan1Open(bool v);
    void set_Fan2Open(bool v);
    void set_Fan3Open(bool v);
    void set_Fan4Open(bool v);
    void set_Fan5Open(bool v);
    void set_Fan6Open(bool v);
    void set_Fan7Open(bool v);
    void set_Fan8Open(bool v);
    void set_Fan9Open(bool v);


    void set_Mode1(bool v);
    void set_Mode2(bool v);
    void set_STO(bool v);
    void set_Reset();
    void set_SV1(double v);
    void set_SV2(double v);
    void set_PID1(double p,double i,double d);
    void set_PID2(double p, double i, double d);
    void set_AO1(double v);
    void set_Fan(double v);
    void set_5000HoldingRegister(bool t,int addr, double v);
    
    void set6022Mode_1(bool v);
    void set6022Mode_2(bool v);

    void writeSV1(double targetSV);
    void writeSV2(double targetSV);
    void writePID1( double p, double i, double d);
    void writePID2( double p, double i, double d);
    void writeHoldingRegisters(int address, double value, int number);
    void WriteSingleHoldingRegisters(bool target ,int slave, int address, int value);
    void MotorControl(bool v);
    void Fan_PowerControl(bool v);


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
    QMutex m_lock;
    QModbusTcpClient* m_5000 = nullptr;
    QModbusTcpClient* m_6022 = nullptr;
    QTimer* m_pollTimer = nullptr;
    QTimer* m_reconnectTimer = nullptr;
    QString m_ip = "192.168.1.201";
    int m_port = 502;
    QString m_ip2 = "192.168.1.202";
    int m_port2 = 502;
    bool m5000_target = false;
    int m5000_addr=0;
    double m5000_value = 0;

    bool m_Open1 = false;
    bool m_Open2 = false;
    bool m_Open3 = false;
    bool m_Open4 = false;
    bool m_Open5 = false;
    bool m_Open6 = false;
    bool m_Open7 = false;
    bool m_Open8 = false;
    bool m_Open9 = false;
    bool fan1_open = false;
    bool fan2_open = false;
    bool fan3_open = false;
    bool fan4_open = false;
    bool fan5_open = false;
    bool fan6_open = false;
    bool fan7_open = false;
    bool fan8_open = false;
    bool fan9_open = false;

    bool m_STO = false;
    double AO1 = 0.0;
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
    bool motor = false;
    bool power = false;
    double m_setALL = 0.0;
    bool f_setMode1 = false;
    bool f_setMode2 = false;
    bool f_STO = false;
    bool f_Reset = false;
    bool f_setSV1 = false;
    bool f_setSV2 = false;
    bool f_setPID1 = false;
    bool f_setPID2 = false;
    bool f_write5000 = false;
    bool f_setFAN = false;
    bool f_FanCtrl = false;
    bool f_MotorCtrl = false; //
    bool f_setAO1 = false; //出水閥開度
};
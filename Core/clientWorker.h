#pragma once

#include <qobject>
#include <Qvector>
#include <QTimer>
#include <QMutex>
#include <qvariant>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QQueue>

struct HoldingRegisterRequest {
    bool target;
    int address;
    double value; // �쥻�� double�A�����h WriteSingleHoldingRegisters �� int�A��ĳ�Τ@
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
    void reconnectDevices();
    void writeSingleCoil(int address, bool value);

    //�g�J
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
    void set_STO2(bool v);

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

    void writeSV1(float targetSV);
    void writeSV2(float targetSV);
    void writePID1( double p, double i, double d);
    void writePID2( double p, double i, double d);
    void writeHoldingRegisters(int address, double value, int number);
    void WriteSingleHoldingRegisters(bool target ,int slave, int address, int value);
    void MotorControl(bool v);
    void Fan_PowerControl(bool v);


    //Ū��
    void Read5000HoldingRegisters( int slave, int startAddress, int number); 
    void read_test();
    void Read6022PV1(); //�Ĥ@��PV 
    void Read6022PV2(); //�ĤG��PV
    void Read6022MV(); //PID ��X
    //void readtest();
    void ReadPID1(); //�Ĥ@��PID
    void ReadPID2(); //�ĤG��PID 
    void ReadCoils( int slave, int startAddress, int number); 

    void onStateChanged(QModbusDevice::State state);
    void onErrorOccurred(QModbusDevice::Error error);
    bool m_mode1 = false;
    bool m_mode2 = false;

signals:
    void connected();
    void m_5000Coil(QVector <quint16> result, QVector <quint16> input, QVector <quint16> output);
    void m_5000HodingRegister(QVector <quint16> result, QVector <quint16> input, QVector <quint16> output);
    void pidcontrolFan(double v);
    void pidcontroloutvalue(double v);
    void R_PV(QVector <quint16> result);
    void m_6022PV1(QVector <quint16> result);
    void m_6022SV1(QVector <quint16> result);
    void m_6022PV2(QVector <quint16> result);
    void m_6022SV2(QVector <quint16> result);
    void m_6022MV(QVector <quint16> result);
    void m_6022PID1(QVector <quint16> result);
    void m_6022PID2(QVector <quint16> result);

private:
    QQueue<HoldingRegisterRequest> m_writeQueue; // �s�W��C
    QMutex m_lock;
    QModbusTcpClient* m_5000 = nullptr;
    QModbusTcpClient* m_6022 = nullptr;
    QTimer* m_pollTimer = nullptr;
    QTimer* m_reconnectTimer = nullptr;
    // QString m_ip = "127.0.0.1";
    QString m_ip = "192.168.1.201";
    // int m_port = 1502;
    int m_port = 502;
    // QString m_ip2 = "127.0.0.1";
    QString m_ip2 = "192.168.1.202";
    // int m_port2 = 2502;
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
    bool m_STO2 = false;

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
    bool f_STO2 = false;
    bool f_Reset = false;
    bool f_setSV1 = false;
    bool f_setSV2 = false;
    bool f_setPID1 = false;
    bool f_setPID2 = false;
    bool f_write5000 = false;
    bool f_setFAN = false;
    bool f_FanCtrl = false;
    bool f_MotorCtrl = false; //
    bool f_setAO1 = false; //�X���ֶ}��
    bool m_isSTO = false;
    bool m_isSTO2 = false;

    bool m_isFanSTO = false;
};
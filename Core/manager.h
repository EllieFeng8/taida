#pragma once

#include <qobject>
#include <Qvector>
#include <qthread>
#include "clientWorker.h"
#include "serverWorker.h"
#include "ms300.h"
class Manager : public QObject
{
    Q_OBJECT

public:
    explicit Manager(QObject* parent = nullptr);
    ~Manager();

    QString ip;
    void init();
    void set_mode1(bool v);
    void set_mode2(bool v);
    void set_server(int port);
    void set_sv(int v);
    void set_sv2(int v);

    void set_PID(double p, double i, double d);
    void set_PID2(double p, double i, double d);

    void WriteHoldingRegister(bool t, int add, double value);

    void motorFrequency(double v);
    void fan1TargetRpm(double v);
    void fan2TargetRpm(double v);
    void fan3TargetRpm(double v);
    void fan4TargetRpm(double v);
    void fan5TargetRpm(double v);
    void fan6TargetRpm(double v);
    void fan7TargetRpm(double v);
    void fan8TargetRpm(double v);
    void fan9TargetRpm(double v);
    void returnValveOpening(double v);
    void set_FanPower(bool v);
    void set_motor(bool v);
    void set_Fan1Open(bool v);
    void set_Fan2Open(bool v);
    void set_Fan3Open(bool v);
    void set_Fan4Open(bool v);
    void set_Fan5Open(bool v);
    void set_Fan6Open(bool v);
    void set_Fan7Open(bool v);
    void set_Fan8Open(bool v);
    void set_Fan9Open(bool v);
    void set_allFan(double v);
    void set_AO1(double v);
    void set_Estop(bool v);
    void set_Reset(bool v);
signals:
    void server_on();
    void Coil(QVector <quint16> result);
    void HodingRegister(QVector <quint16> result);
    void Adam6022Data(QVector <quint16> result);
    void _PID1(QVector <quint16> result);
    void _PID2(QVector <quint16> result);
    void R_PV(QVector <quint16> result);
    void _PV1(QVector <quint16> result);
    void _PV2(QVector <quint16> result);
    void _MV(QVector <quint16> result);
    void updateToUi(int index,quint16 v);
    void update_PID(int index, double p, double i, double d);
    void update_switch(int index, bool v);
    void update_input(QVector <quint16> result);
    void update_savedata(QVector <quint16> result);
    void STOset0();
    void E_STOPset0();

private:
    bool _E_STOP = false;
    bool _STO = false;
    bool server_OK = false;
    bool normal = true;
    bool m_PID1 = false;
    bool m_PID2 = false;
    quint16 p1 = 0.0;
    quint16 p2 = 0.0;
    quint16 i1 = 0.0;
    quint16 i2 = 0.0;
    quint16 d1 = 0.0;
    quint16 d2 = 0.0;
    quint16 PID_AO1;
    quint16 PID_AO2;
    clientWorker* m_clientWorker = nullptr;
    QThread* m_clientThread = nullptr;

    ServerWorker* m_serverWorker = nullptr;
    QThread* m_serverThread = nullptr;

    MS300* m_ms300 = nullptr;
    QThread* m_ms300Thread = nullptr;
    quint16 version_num1 = 0;
    quint16 version_num2 = 14;
    quint16 version_num3 = 15;
    quint16 version_year = 2026;
    quint16 version_date = 423;
};
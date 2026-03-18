#pragma once

#include <qobject>
#include <Qvector>
#include <qthread>
#include "clientWorker.h"
#include "serverWorker.h"

class Manager : public QObject
{
    Q_OBJECT

public:
    explicit Manager(QObject* parent = nullptr);
    ~Manager();

    void init();
    void set_mode1(bool v);
    void set_mode2(bool v);

    void set_sv(int v);
    void set_sv2(int v);

    void set_PID(double p, double i, double d);
    void set_PID2(double p, double i, double d);

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
signals:
    void Coil(QVector <quint16> result);
    void HodingRegister(QVector <quint16> result);
    void Adam6022Data(QVector <quint16> result);
    void _PID1(QVector <quint16> result);
    void _PID2(QVector <quint16> result);

    void _PV1(QVector <quint16> result);
    void _PV2(QVector <quint16> result);
    void _MV(QVector <quint16> result);
private:
    bool m_PID1 = false;
    bool m_PID2 = false;

    quint16 PID_AO1;
    quint16 PID_AO2;
    clientWorker* m_clientWorker = nullptr;
    QThread* m_clientThread = nullptr;

    ServerWorker* m_serverWorker = nullptr;
    QThread* m_serverThread = nullptr;
};
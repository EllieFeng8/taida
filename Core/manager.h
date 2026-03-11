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
    void set_mode(bool v);
    void set_sv(int v);
    void set_p1(int v);
    void set_i1(int v);
    void set_d1(int v);
    void set_p2(int v);
    void set_i2(int v);
    void set_d2(int v);
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
private:
    clientWorker* m_clientWorker = nullptr;
    QThread* m_clientThread = nullptr;

    ServerWorker* m_serverWorker = nullptr;
    QThread* m_serverThread = nullptr;
};
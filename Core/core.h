#pragma once
#include<qsettings.h>
#include <qobject>
#include <Qvector>
#include "manager.h"
#include "TdProxy.h"
#include "SqlManager.h"
#include "RESTManager.h"
#include <QRandomGenerator>

class Core : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    static Core& instance();
    TdProxy* m_proxy = nullptr; 
    void init();

public slots:
    //proxy
    void set_PID_click();
    void set_PID(double v);
    void set_PID2(double v);
    //manager
    void onPVdata(QVector <quint16> result)
    {
        double pv0 = result[0]/65.535;
        double pv3 = result[3] /655.35;

        m_proxy->setPressureDiff(qRound(pv0 * 100.0) / 100.0);
        senserData[17] = pv0;
        m_proxy->setOutletAirTemp(qRound(pv3 * 100.0) / 100.0);
        senserData[16] = pv3;
    }
    void Coil_Data(QVector <quint16> result);
    void HodingRegister_Data(QVector <quint16> result);
    void pidPV1(QVector <quint16> result);
    void pidPV2(QVector <quint16> result);
    void PID1(QVector <quint16> result);
    void PID2(QVector <quint16> result);
signals:
    void ip(QString ip);
private:

    explicit Core(QObject* parent = nullptr){}
    ~Core();
    void updateProxyProperty(int index, quint16 value);
    void updateProxyProperty2(int index, quint16 value);

    void saveProductionSettings();
    void loadProductionSettings();
    quint16 v_0;
    quint16 v_1;
    quint16 v_2;
    quint16 v_3;
    quint16 v_4;
    quint16 v_5;
    quint16 v_6;
    quint16 v_7;
    quint16 v_8;
    quint16 v_9;
    quint16 v_10;
    quint16 v_11;
    quint16 v_12;
    quint16 v_13;
    quint16 v_14;
    quint16 v_15;
    quint16 v_16;
    quint16 v_17;
    quint16 v_18;
    quint16 v_19;
    quint16 v_24;
    quint16 v_25;
    quint16 v_26;
    quint16 v_27;
    quint16 v_32;
    quint16 v_33;
    quint16 v_34;
    qint64 m_lastSaveTime = 0;
    QVector <double> senserData;
    QVector <double> senserData2;
    double mv1=0.0;
    SqlManager* m_sqlManager;
    RESTManager* m_restManager;
    Manager* m_manager = nullptr;
    
};
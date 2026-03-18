#pragma once

#include <qobject>
#include <Qvector>
#include "manager.h"
#include "TdProxy.h"
#include "SqlManager.h"
#include "RESTManager.h"
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
    void set_PID(double v);
    void set_PID2(double v);
    //manager
    void Coil_Data(QVector <quint16> result);
    void HodingRegister_Data(QVector <quint16> result);
    void pidPV1(QVector <quint16> result);
    void pidPV2(QVector <quint16> result);
    void PID1(QVector <quint16> result);
    void PID2(QVector <quint16> result);
private:

    explicit Core(QObject* parent = nullptr) {}
    ~Core() {}
    void updateProxyProperty(int index, quint16 value);


    QVector <double> senserData;

    SqlManager* m_sqlManager;
    RESTManager* m_restManager;
    Manager* m_manager = nullptr;
    
};
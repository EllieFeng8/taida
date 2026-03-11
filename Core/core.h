#pragma once

#include <qobject>
#include <Qvector>
#include "manager.h"
#include "TdProxy.h"
class Core : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    static Core& instance();
    TdProxy* m_proxy = nullptr; 
    void init();
public slots:
    void Coil_Data(QVector <quint16> result);
    void HodingRegister_Data(QVector <quint16> result);

private:

    explicit Core(QObject* parent = nullptr) {}
    ~Core() {}
    void updateProxyProperty(int index, quint16 value);




    
    Manager* m_manager = nullptr;
    
};
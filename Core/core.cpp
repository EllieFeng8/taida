#include "core.h"


Core& Core::instance()
{
    static Core inst; // 建立唯一的靜態實例
    return inst;      // 回傳該實例的引用
}

void Core::init()
{
    m_proxy = new TdProxy(this);
    m_manager = new Manager(this);
    
    QObject::connect(m_manager, &Manager::Coil, this, &Core::Coil_Data);
    QObject::connect(m_manager, &Manager::HodingRegister, this, &Core::HodingRegister_Data);


    
    QObject::connect(m_proxy, &TdProxy::outValvePidOnChanged, m_manager, &Manager::set_mode);
    QObject::connect(m_proxy, &TdProxy::outValveOpeningChanged, m_manager, &Manager::set_sv);
    QObject::connect(m_proxy, &TdProxy::outValvePChanged, m_manager, &Manager::set_p1);
    QObject::connect(m_proxy, &TdProxy::outValveIChanged, m_manager, &Manager::set_i1);
    QObject::connect(m_proxy, &TdProxy::outValveDChanged, m_manager, &Manager::set_d1);

    //Analog Output 
    QObject::connect(m_proxy, &TdProxy::motorFrequencyChanged, m_manager, &Manager::);
    QObject::connect(m_proxy, &TdProxy::fan1TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::fan2TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::fan3TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::fan4TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::fan5TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::fan6TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::fan7TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::fan8TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::fan9TargetRpmChanged, m_manager, &Manager::set_d1);
    QObject::connect(m_proxy, &TdProxy::returnValveOpeningChanged, m_manager, &Manager::set_d1);


    
}

void Core::Coil_Data(QVector <quint16> result)
{
    
    for (int i = 0; i < result.size(); ++i)
    {
        qDebug() << "value" << i << " = " << result[i];
        //updateProxyProperty(i, result[i]);

    }
}

void Core::HodingRegister_Data(QVector <quint16> result)
{

    for (int i = 0; i < result.size(); ++i)
    {
        qDebug() << "value" << i << " = " << result[i];
        updateProxyProperty(i, result[i]);

    }
}

void Core::updateProxyProperty(int index, quint16 value)
{

    if (!m_proxy) return;
    switch (index) {

    case 0:  m_proxy->setInWaterTemp(value); break; //入水溫度
    case 1:  m_proxy->setInWaterPressure(value); break; //入水壓力
    case 2:  break;//冷排出口溫度
    case 3:  break; //冷排出口壓力
    case 4:  m_proxy->setOutWaterTemp(value); break; //出水口溫度
    case 5:  m_proxy->setOutWaterPressure(value); break; //出水口壓力
    case 6:  m_proxy->setCondenserLeft1Temp(value); break; //冷排溼度計-1
    case 7:  m_proxy->setCondenserLeft2Temp(value); break; //冷排溼度計-2
    case 8:  m_proxy->setCondenserRight1Temp(value); break; //冷排溼度計-3
    case 9:  m_proxy->setCondenserRight2Temp(value); break; //冷排溼度計-4
    case 10: m_proxy->setInletAirTemp(value); break; //入風口溫度
    case 11: m_proxy->setInletAirHumidity(value); break; //入風口濕度
    case 12: m_proxy->setCurrentWaterFlow(value); break;// 流量計
    case 13: break; //出水電動閥位置回授
    case 14: break; //回水電動閥位置回授
    case 15: break; //風扇自動速率

    default: break;
    }
}
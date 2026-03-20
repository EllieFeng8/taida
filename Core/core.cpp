#include "core.h"


Core& Core::instance()
{
    static Core inst; // 建立唯一的靜態實例
    return inst;      // 回傳該實例的引用
}
Core::~Core()
{
    // 釋放 Manager 物件 (這會進一步觸發 Manager 的解構式停止執行緒)
    if (m_manager) {
        delete m_manager;
        m_manager = nullptr;
    }

    // 釋放 TdProxy 物件
    if (m_proxy) {
        delete m_proxy;
        m_proxy = nullptr;
    }
    //saveProductionSettings();
}
void Core::init()
{
    m_sqlManager = SqlManager::instance();
    m_proxy = new TdProxy(this);
    m_manager = new Manager(this);
    m_sqlManager->initialize();
    senserData.resize(35);
    senserData.fill(172);
    QObject::connect(m_manager, &Manager::Coil, this, &Core::Coil_Data);
    QObject::connect(m_manager, &Manager::HodingRegister, this, &Core::HodingRegister_Data);
    QObject::connect(m_manager, &Manager::_PV1, this, &Core::pidPV1);
    QObject::connect(m_manager, &Manager::_PV2, this, &Core::pidPV2);
    QObject::connect(m_manager, &Manager::_PID1, this, &Core::PID1);
    QObject::connect(m_manager, &Manager::_PID2, this, &Core::PID2);


    
    QObject::connect(m_proxy, &TdProxy::outValvePidOnChanged, m_manager, &Manager::set_mode2);
    QObject::connect(m_proxy, &TdProxy::fanPidMonitorOnChanged, m_manager, &Manager::set_mode1);

    QObject::connect(m_proxy, &TdProxy::targetPressureDiffChanged, m_manager, &Manager::set_sv);
    QObject::connect(m_proxy, &TdProxy::outValveOpeningChanged, m_manager, &Manager::set_sv2);
    QObject::connect(m_proxy, &TdProxy::fanPidDChanged, this, &Core::set_PID);
    QObject::connect(m_proxy, &TdProxy::outValveDChanged, this,&Core::set_PID2);

    
    //Analog Output 
    QObject::connect(m_proxy, &TdProxy::motorFrequencyChanged, m_manager, &Manager::motorFrequency);
    QObject::connect(m_proxy, &TdProxy::fan1TargetRpmChanged, m_manager, &Manager::fan1TargetRpm);
    QObject::connect(m_proxy, &TdProxy::fan2TargetRpmChanged, m_manager, &Manager::fan2TargetRpm);
    QObject::connect(m_proxy, &TdProxy::fan3TargetRpmChanged, m_manager, &Manager::fan3TargetRpm);
    QObject::connect(m_proxy, &TdProxy::fan4TargetRpmChanged, m_manager, &Manager::fan4TargetRpm);
    QObject::connect(m_proxy, &TdProxy::fan5TargetRpmChanged, m_manager, &Manager::fan5TargetRpm);
    QObject::connect(m_proxy, &TdProxy::fan6TargetRpmChanged, m_manager, &Manager::fan6TargetRpm);
    QObject::connect(m_proxy, &TdProxy::fan7TargetRpmChanged, m_manager, &Manager::fan7TargetRpm);
    QObject::connect(m_proxy, &TdProxy::fan8TargetRpmChanged, m_manager, &Manager::fan8TargetRpm);
    QObject::connect(m_proxy, &TdProxy::fan9TargetRpmChanged, m_manager, &Manager::fan9TargetRpm);
    QObject::connect(m_proxy, &TdProxy::returnValveOpeningChanged, m_manager, &Manager::returnValveOpening);

    QObject::connect(m_proxy, &TdProxy::fan1SwitchOnChanged, m_manager, &Manager::set_Fan1Open);
    QObject::connect(m_proxy, &TdProxy::fan2SwitchOnChanged, m_manager, &Manager::set_Fan2Open);
    QObject::connect(m_proxy, &TdProxy::fan3SwitchOnChanged, m_manager, &Manager::set_Fan3Open);
    QObject::connect(m_proxy, &TdProxy::fan4SwitchOnChanged, m_manager, &Manager::set_Fan4Open);
    QObject::connect(m_proxy, &TdProxy::fan5SwitchOnChanged, m_manager, &Manager::set_Fan5Open);
    QObject::connect(m_proxy, &TdProxy::fan6SwitchOnChanged, m_manager, &Manager::set_Fan6Open);
    QObject::connect(m_proxy, &TdProxy::fan7SwitchOnChanged, m_manager, &Manager::set_Fan7Open);
    QObject::connect(m_proxy, &TdProxy::fan8SwitchOnChanged, m_manager, &Manager::set_Fan8Open);
    QObject::connect(m_proxy, &TdProxy::fan9SwitchOnChanged, m_manager, &Manager::set_Fan9Open);

    QObject::connect(m_proxy, &TdProxy::fanAllTargetRpmChanged, m_manager, &Manager::set_allFan);

    QObject::connect(m_proxy, &TdProxy::motorResetChanged, m_manager, &Manager::set_Reset);

}

void Core::Coil_Data(QVector <quint16> result)
{
    for (int i = 0; i < result.size(); ++i)
    {
        //qDebug() << "value" << i << " = " << result[i];
        //updateProxyProperty(i, result[i]);

    }
}

void Core::HodingRegister_Data(QVector <quint16> result)
{

    for (int i = 0; i < result.size(); ++i)
    {
        //qDebug() << "value" << i << " = " << result[i];
        updateProxyProperty(i, result[i]);
        senserData[i] = result[i];
    }
    QDateTime now = QDateTime::currentDateTime();
    m_sqlManager->saveSensorData(now,senserData );
}

void Core::pidPV1(QVector <quint16> result)
{
    double v = result[0];
    m_proxy->setPressureDiff(v);
}
void Core::pidPV2(QVector <quint16> result)
{
    double pv = result[0];
    double sv = result[1];
    m_proxy->setOutletAirTemp(pv);
    //m_proxy->setOutWaterTargetTemp(sv);
}
void Core::PID1(QVector <quint16> result)
{
    double p = result[0];
    double i = result[1];
    double d = result[2];
    m_proxy->setFanPidPP(p);
    m_proxy->setFanPidIP(i);
    m_proxy->setFanPidDP(d);

}
void Core::PID2(QVector <quint16> result)
{
    double p = result[0];
    double i = result[1];
    double d = result[2];
    m_proxy->setOutValvePP(p);
    m_proxy->setOutValveIP(i);
    m_proxy->setOutValveDP(d);

}
void Core::set_PID(double v)
{
    double Pid = m_proxy->m_fanPidP;
    double pId = m_proxy->m_fanPidI;
    double piD= m_proxy->m_fanPidD;
    m_manager->set_PID(Pid,pId,piD);
}
void Core::set_PID2(double v)
{
    double Pid = m_proxy->m_outValveP;
    double pId = m_proxy->m_outValveI;
    double piD = m_proxy->m_outValveD;
    m_manager->set_PID2(Pid, pId, piD);
}
void Core::updateProxyProperty(int index, quint16 value)
{
    if (!m_proxy) return;
    switch (index) {

    case 0:
        if (value == v_0) { return; }
        v_0 = value;
        m_proxy->setInWaterTemp(qRound((value / 655.35) * 10.0) / 10.0); break; //入水溫度
    case 1: 
        if (value == v_1) { return; }
        v_1 = value; m_proxy->setInWaterPressure(qRound((value / 65.535) * 10.0) / 10.0); break; //入水壓力
    case 2:
        if (value == v_2) { return; }
        v_2 = value; 
        m_proxy->setReturnWaterTemp(qRound((value / 655.35) * 10.0) / 10.0); break;//回水口溫度
    case 3:
        if (value == v_3) { return; }
        v_3 = value; 
        m_proxy->setReturnWaterPressure(qRound((value / 65.535) * 10.0) / 10.0); break; //回水口壓力
    case 4:
        if (value == v_4) { return; }
        v_4 = value; 
        m_proxy->setOutWaterTemp(qRound((value / 655.35) * 10.0) / 10.0); break; //出水口溫度
    case 5:
        if (value == v_5) { return; }
        v_5 = value; 
        m_proxy->setOutWaterPressure(qRound((value / 65.535) * 10.0) / 10.0); break; //出水口壓力
    case 6: 
        if (value == v_6) { return; }
        v_6 = value; 
        m_proxy->setCondenserLeft1Temp(qRound((value / 655.35) * 10.0) / 10.0); break; //冷排溼度計-1
    case 7:
        if (value == v_7) { return; }
        v_7 = value; 
        m_proxy->setCondenserLeft2Temp(qRound((value / 655.35) * 10.0) / 10.0); break; //冷排溼度計-2
    case 8:
        if (value == v_8) { return; }
        v_8 = value; 
        m_proxy->setCondenserRight1Temp(qRound((value / 655.35) * 10.0) / 10.0); break; //冷排溼度計-3
    case 9: 
        if (value == v_9) { return; }
        v_9 = value; 
        m_proxy->setCondenserRight2Temp(qRound((value / 655.35) * 10.0) / 10.0); break; //冷排溼度計-4
    case 10:
        if (value == v_10) { return; }
        v_10 = value; 
        m_proxy->setInletAirTemp(qRound((value / 655.35) * 10.0) / 10.0); break; //入風口溫度
    case 11:
        if (value == v_11) { return; }
        v_11 = value; 
        m_proxy->setInletAirHumidity(qRound((value / 655.35) * 10.0) / 10.0); break; //入風口濕度
    case 12:
        if (value == v_12) { return; }
        v_12 = value; 
        m_proxy->setCurrentWaterFlow(value); break;// 流量計
    case 13:
        if (value == v_13) { return; }
        v_13 = value; 
        m_proxy->setOutValveOpeningP(qRound((value / 655.35) * 10.0) / 10.0); break; //出水電動閥位置回授
    case 14:
        if (value == v_14) { return; }
        v_14 = value;
        m_proxy->setReturnValveOpeningP(qRound((value / 655.35) * 10.0) / 10.0); break; //回水電動閥位置回授
    case 15: break; //風扇自動速率
    case 16: 
        if (value == v_16) { return; }
        v_16 = value; 
        m_proxy->setMotorFrequencyP(qRound((value / 40.95) * 10.0) / 10.0); break; //循環水泵速率輸出
    case 17: 
        if (value == v_17) { return; }
        v_17 = value; 
        m_proxy->setFan1TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇1
    case 18: 
        if (value == v_18) { return; }
        v_18 = value;
        m_proxy->setFan2TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇2
    case 19: 
        if (value == v_19) { return; }
        v_19 = value; 
        m_proxy->setFan3TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇3
    case 20: break; //
    case 21: break; //
    case 22: break; //
    case 23: break; //
    case 24: 
        if (value == v_24) { return; }
        v_24 = value; 
        m_proxy->setFan4TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇4
    case 25:
        if (value == v_25) { return; }
        v_25 = value;
        m_proxy->setFan5TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇5
    case 26: 
        if (value == v_26) { return; }
        v_26 = value; 
        m_proxy->setFan6TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇6
    case 27:
        if (value == v_27) { return; }
        v_27 = value; 
        m_proxy->setFan7TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇7
    case 28: break; //
    case 29: break; //
    case 30: break; //
    case 31: break; //
    case 32:
        if (value == v_32) { return; }
        v_32 = value; 
        m_proxy->setFan8TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇8
    case 33:
        if (value == v_33) { return; }
        v_33 = value; 
        m_proxy->setFan9TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇9
    case 34:
        if (value == v_34) { return; }
        v_34 = value; 
        m_proxy->setReturnValveOpeningP(qRound((value / 40.95) * 10.0) / 10.0); break; //回水閥開度
    case 35: break; //Null

    default: break;
}
}

void Core::saveProductionSettings()
{
    QSettings settings("production.ini", QSettings::IniFormat);

    settings.setValue("Production/Hz", m_proxy->m_motorFrequency);
    settings.setValue("Production/fan1", m_proxy->m_fan1TargetRpm);
    settings.setValue("Production/fan2", m_proxy->m_fan2TargetRpm);
    settings.setValue("Production/fan3", m_proxy->m_fan3TargetRpm);
    settings.setValue("Production/fan4", m_proxy->m_fan4TargetRpm);
    settings.setValue("Production/fan5", m_proxy->m_fan5TargetRpm);
    settings.setValue("Production/fan6", m_proxy->m_fan6TargetRpm);
    settings.setValue("Production/fan7", m_proxy->m_fan7TargetRpm);
    settings.setValue("Production/fan8", m_proxy->m_fan8TargetRpm);
    settings.setValue("Production/fan9", m_proxy->m_fan9TargetRpm);
    settings.setValue("Production/returnWaterOpen", m_proxy->m_returnValveOpening);
    settings.setValue("Production/pressdiff", m_proxy->m_pressureDiff);
    settings.setValue("Production/outAirTemp", m_proxy->m_outWaterTargetTemp);



    settings.sync();
}
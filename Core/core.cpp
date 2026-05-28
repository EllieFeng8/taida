#include "core.h"
#include <QNetworkInterface>

Core& Core::instance()
{
    static Core inst; // 建立唯一的靜態實例
    return inst;      // 回傳該實例的引用
}
Core::~Core()
{
    saveProductionSettings();

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
}
void Core::init()
{
    m_sqlManager = SqlManager::instance();
    if (!m_restManager)
    {
        m_restManager = new RESTManager(m_sqlManager, this);
    }
    bool ok = false;
    int port = 8080;

    if (!m_restManager->start(static_cast<quint16>(port)))
    {
        return;
    }
    m_proxy = new TdProxy(this);
    m_manager = new Manager(this);
    m_sqlManager->initialize();
    senserData.resize(40);
    senserData.fill(0);
    senserData2.resize(40);
    senserData2.fill(0);
    QObject::connect(m_manager, &Manager::Coil, this, &Core::Coil_Data);
    QObject::connect(m_manager, &Manager::HodingRegister, this, &Core::HodingRegister_Data);
    QObject::connect(m_manager, &Manager::update_savedata, this, [=](QVector<quint16> result)
        {
            

            // 判斷時間差是否大於等於設定的 n 秒
            if (QDateTime::currentDateTime().currentMSecsSinceEpoch() - m_lastSaveTime >= m_sqlManager->readFrequency())
            {
               
                QDateTime now = QDateTime::currentDateTime();
                m_lastSaveTime = now.currentMSecsSinceEpoch();
                // --- 關鍵：使用 QtConcurrent 避免卡住 UI ---
                // 注意：確保 saveSensorData 內部的資料庫連接是該線程私有的
                m_sqlManager->saveSensorData(now, senserData2, result);
                saveProductionSettings();
                //qDebug() << "：" << now.toString("hh:mm:ss");
            }
            else
            {
                // 時間還沒到，可以選擇跳過，或僅更新 UI 顯示
            }
        });
    QObject::connect(m_manager, &Manager::update_input, this, [=](QVector<quint16> result) 
        {
            for (int i = 0; i < result.size(); ++i)
            {
                if (i == 0 || i == 2 || i == 4 || i == 6 || i==7 || i == 8 || i == 9 || i == 10 || i == 11 || i==13 || i == 14 || i == 15)
                {
                    senserData[i] = qRound(result[i] / 655.35 * 100.0) / 100.0;
                }
                else if (i == 12) {
                    senserData[i] = qRound((result[i] / 655.35 * 8) * 100.0) / 100.0;
                }
                else 
                {
                    senserData[i] = qRound(result[i] / 65.535 * 100.0) / 100.0;
                }
            }
           
            
          // (冷排平均溫度 - 出風溫度) * 流量 * 4186 / 60000 * 998   
           double rawHeat = (((senserData[6] - senserData[7] + senserData[8] - senserData[9]) / 2) * senserData[12] * 4186) / 60000 * 998.5/1000;
           senserData[18] = qRound(rawHeat * 100.0) / 100.0;
           m_proxy->setHeatExchange(senserData[18]);
            //QDateTime now = QDateTime::currentDateTime();
            //m_sqlManager->saveSensorData(now,senserData );
           senserData2[0] = senserData[0];//入水溫
           senserData2[1] = senserData[1];//入水壓
           senserData2[2] = senserData[4];//出水溫
           senserData2[3] = senserData[5];//出水壓
           senserData2[4] = senserData[2];//回水溫
           senserData2[5] = senserData[3];//回水壓
           senserData2[6] = senserData[6];//盤管左入溫
           senserData2[7] = senserData[7];//盤管左出溫
           senserData2[8] = senserData[8];//盤管右入溫
           senserData2[9] = senserData[9];//盤管右出溫
           senserData2[10] = senserData[10];//入風溫
           senserData2[11] = senserData[11];//入風濕
           senserData2[12] = senserData[12];//流量計
           senserData2[13] = m_proxy->getOutValveOpening();//出水閥SV 
           senserData2[14] = senserData[13];//出水閥PV
           senserData2[15] = m_proxy->getReturnValveOpening();//混水閥SV
           senserData2[16] = senserData[14];//混水閥PV
           senserData2[17] = m_proxy->getFan1TargetRpm();//風扇SV
           senserData2[18] = m_proxy->getFan1TargetRpmP();//風扇PV
           senserData2[19] = senserData[16];//出風溫
           senserData2[20] = m_proxy->getTargetPressureDiff();//壓差SV
           senserData2[21] = senserData[17];//壓差PV
           senserData2[22] = senserData[18];//熱交換
           senserData2[23] = mode1;//風扇自動
           senserData2[24] = mode2;//溫度自動
           senserData2[25] = m_proxy->getMotorFrequency();//泵浦SV 
           senserData2[26] = m_proxy->getMotorFrequencyP();//泵浦PV 
        });
    QObject::connect(m_manager, &Manager::pidcontrolFan, this, [this](double v) {
        m_proxy->setFan1TargetRpm(v); 
        m_proxy->setFan2TargetRpm(v); 
        m_proxy->setFan3TargetRpm(v); 
        m_proxy->setFan4TargetRpm(v); 
        m_proxy->setFan5TargetRpm(v); 
        m_proxy->setFan6TargetRpm(v); 
        m_proxy->setFan7TargetRpm(v); 
        m_proxy->setFan8TargetRpm(v); 
        m_proxy->setFan9TargetRpm(v);
        mv1 = v;
        });
    QObject::connect(m_manager, &Manager::pidcontroloutvalue, this, [this](double v) {
        m_proxy->setOutValveOpening(qRound((v* 1) / 1));
        });

    QObject::connect(m_manager, &Manager::updateToUi, this, &Core::updateProxyProperty2);
    QObject::connect(m_manager, &Manager::update_switch, this, [=](int index, bool v)
        {
            if (index == 1) 
            {
                m_proxy->setFanPidMonitorOn(v);
            }
            else if (index == 2) {
                m_proxy->setOutValvePidOn(v);
            }
            else if (index == 4) {
                m_proxy->setMotorFrequencySwitchOn(v);
            }
            else if (index == 3) {
                m_proxy->setFanEmergencySwitchOn(v);
            }
        });

    QObject::connect(m_manager, &Manager::update_PID ,this, [=](int index, double p, double i, double d)
        {
            if (index == 1) {
                m_proxy->setFanPidP(p);
                m_proxy->setFanPidI(i);
                m_proxy->setFanPidD(d);
            }
            else if (index == 2) {
                m_proxy->setOutValveP(p);
                m_proxy->setOutValveI(i);
                m_proxy->setOutValveD(d);

            }
        });

    QObject::connect(m_manager, &Manager::R_PV, this, &Core::onPVdata);
    QObject::connect(m_manager, &Manager::server_on, this, [this]() { this->loadProductionSettings(); });

    QObject::connect(m_manager, &Manager::_PV1, this, &Core::pidPV1);
    QObject::connect(m_manager, &Manager::_PV2, this, &Core::pidPV2);
    QObject::connect(m_manager, &Manager::_PID1, this, &Core::PID1);
    QObject::connect(m_manager, &Manager::_PID2, this, &Core::PID2);
    //QObject::connect(m_manager, &Manager::_MV, this, [=](QVector<quint16> v) {
        //m_proxy->setOutValveOpeningP(v[1]);
        //});

    QObject::connect(m_proxy, &TdProxy::motorFrequencySwitchOnChanged, m_manager, &Manager::set_motor);
    QObject::connect(m_proxy, &TdProxy::motorFrequencySwitchOnChanged, this, [this](bool v)
        {
            if (v) {
                m_proxy->setMotorFrequency(0);
            }
        }
    );

    QObject::connect(m_proxy, &TdProxy::outValveOpeningChanged, m_manager, &Manager::set_AO1);

    
    QObject::connect(m_proxy, &TdProxy::outValvePidOnChanged, m_manager, &Manager::set_mode2);
    QObject::connect(m_proxy, &TdProxy::outValvePidOnChanged, this, [this](bool v){
        mode1 = v ? 1 : 0;
        }
    );

    QObject::connect(m_proxy, &TdProxy::fanPidMonitorOnChanged, m_manager, &Manager::set_mode1);
    QObject::connect(m_proxy, &TdProxy::fanPidMonitorOnChanged, this, [this](bool v) {
        mode2 = v ? 1 : 0;

        }
    );

    QObject::connect(m_proxy, &TdProxy::targetPressureDiffChanged, this, [=](double v) {m_manager->set_sv(v*10); });
    QObject::connect(m_proxy, &TdProxy::outWaterTargetTempChanged, this, [=](double v) {m_manager->set_sv2(v*100); });
    QObject::connect(m_proxy, &TdProxy::fanPidSetSignal, this, &Core::set_PID_click);
    //QObject::connect(m_proxy, &TdProxy::fanPidDChanged, this, &Core::set_PID);
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
    QObject::connect(m_proxy, &TdProxy::fanEmergencySwitchOnChanged, m_manager, &Manager::set_FanPower);
    QObject::connect(m_proxy, &TdProxy::fanEmergencySwitchOnChanged, this, [this](bool v)
        {
            if(v)
            {
                m_proxy->setFan1TargetRpm(0);
                m_proxy->setFan2TargetRpm(0);
                m_proxy->setFan3TargetRpm(0);
                m_proxy->setFan4TargetRpm(0);
                m_proxy->setFan5TargetRpm(0);
                m_proxy->setFan6TargetRpm(0);
                m_proxy->setFan7TargetRpm(0);
                m_proxy->setFan8TargetRpm(0);
                m_proxy->setFan9TargetRpm(0);
            }
        });

    QObject::connect(m_proxy, &TdProxy::motorResetChanged, m_manager, &Manager::set_Reset);
    QObject::connect(m_proxy, &TdProxy::modeSelectChanged, m_manager,&Manager::set_server);

    QObject::connect(m_proxy, &TdProxy::captureFreqChanged, this, [=](int v) 
        {
            m_sqlManager->setReadFrequency(v);
        });


    QStringList ips;
    const auto all = QNetworkInterface::allAddresses();

    for (const QHostAddress& addr : all)
    {
        // 1. 基本過濾：排除回環位址 (127.0.0.1) 且只抓 IPv4
        if (addr.isLoopback() || addr.protocol() != QAbstractSocket::IPv4Protocol)
            continue;

        QString ipStr = addr.toString();

        // 2. 核心邏輯：篩選以 "192." 開頭的位址
        if (ipStr.startsWith("192."))
        {
            ips << ipStr;

            m_proxy->setIpAddress(ipStr);
            m_manager->ip = ipStr;
        }
    }

    if (ips.isEmpty())
    {
        //qInfo() << "找不到 192 開頭的 IPv4 位址";
    }
    else
    {
        qInfo() << "符合條件的 IP 位址:" << ips;
    }
    int freq = m_sqlManager->readFrequency();
    m_proxy->setCaptureFreq(freq);

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
        //senserData[i] = result[i];
    }
    
}

void Core::pidPV1(QVector <quint16> result)
{
   // double sv = result[0];
   // m_proxy->setTargetPressureDiff(qRound(sv / 10));
    //double v = result[0];
    //m_proxy->setPressureDiff(qRound(v * 100.0) / 100.0);
    //senserData[17] = v*40.96;
}
void Core::pidPV2(QVector <quint16> result)
{
    //double pv = result[0];  
    double sv = result[0];
    //m_proxy->setOutletAirTemp(qRound(pv * 100.0) / 100.0);
    //senserData[16] = pv*40.96;

    m_proxy->setOutWaterTargetTempP(qRound(sv/100));
}
void Core::PID1(QVector <quint16> result)
{
    double p = result[0]*1.0/1000;
    double i = result[1] * 1.0 /1000;
    double d = result[2] * 1.0 /1000;
    m_proxy->setFanPidPP(p);
    m_proxy->setFanPidIP(i);
    m_proxy->setFanPidDP(d);

}
void Core::PID2(QVector <quint16> result)
{
    double p = result[0] * 1.0 /1000;
    double i = result[1] * 1.0 /1000;
    double d = result[2] * 1.0 /1000;
    m_proxy->setOutValvePP(p);
    m_proxy->setOutValveIP(i);
    m_proxy->setOutValveDP(d);

}
void Core::set_PID(double v)
{
    double Pid = m_proxy->m_fanPidP;
    double pId = m_proxy->m_fanPidI;
    double piD= m_proxy->m_fanPidD;
    m_manager->set_PID(Pid*1000,pId*1000,piD*1000);
}
void Core::set_PID_click()
{
    double Pid = m_proxy->m_fanPidP;
    double pId = m_proxy->m_fanPidI;
    double piD = m_proxy->m_fanPidD;
    m_manager->set_PID(Pid * 1000, pId * 1000, piD * 1000);
}
void Core::set_PID2(double v)
{   
    double Pid = m_proxy->m_outValveP;
    double pId = m_proxy->m_outValveI;
    double piD = m_proxy->m_outValveD;
    m_manager->set_PID2(Pid*1000, pId * 1000, piD * 1000);
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
        m_proxy->setCurrentWaterFlow(qRound((value / 655.35) * 80.0) / 10.0); break;// 流量計 0~800
    case 13:
        if (value == v_13) { return; }
        v_13 = value; 
        m_proxy->setOutValveOpeningP(qRound(value  * 10.0) / 10.0); break; //出水電動閥位置回授
    case 14:
        if (value == v_14) { return; }
        v_14 = value;
        m_proxy->setReturnValveOpeningP(qRound((value * 10.0) / 10.0)); break; //回水電動閥位置回授
    case 15: break; //風扇自動速率
    case 16: 
        if (value == v_16) { return; }
        v_16 = value; 
        m_proxy->setMotorFrequencyP(qRound((value / 40.95*0.6) * 10.0) / 10.0); break; //循環水泵速率輸出
    case 17: 
        if (value == v_17) { return; }
        v_17 = value; 
        m_proxy->setFan1TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan1TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇1

    case 18: 
        if (value == v_18) { return; }
        v_18 = value;
        m_proxy->setFan2TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan2TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇2
    case 19: 
        if (value == v_19) { return; }
        v_19 = value; 
        m_proxy->setFan3TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan3TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇3
    case 20: break; //
    case 21: break; //
    case 22: break; //
    case 23: break; //
    case 24: 
        if (value == v_24) { return; }
        v_24 = value; 
        m_proxy->setFan4TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan4TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇4
        
    case 25:
        if (value == v_25) { return; }
        v_25 = value;
        m_proxy->setFan5TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan5TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇5
    case 26: 
        if (value == v_26) { return; }
        v_26 = value; 
        m_proxy->setFan6TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan6TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇6
    case 27:
        if (value == v_27) { return; }
        v_27 = value; 
        m_proxy->setFan7TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan7TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇7
    case 28: break; //
    case 29: break; //
    case 30: break; //
    case 31: break; //
    case 32:
        if (value == v_32) { return; }
        v_32 = value; 
        m_proxy->setFan8TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan8TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇8
    case 33:
        if (value == v_33) { return; }
        v_33 = value; 
        m_proxy->setFan9TargetRpmP(qRound(((value / 40.95) * 10.0) / 10.0) * 37.50);
        m_proxy->setFan9TargetRpmPercent(qRound((value / 40.95) * 10.0) / 10.0); break; //風扇9
    case 34:
        if (value == v_34) { return; }
        v_34 = value; 
        //m_proxy->setReturnValveOpeningP(qRound((value / 40.95) * 10.0) / 10.0); break; //回水閥開度
    case 35: break; //Null

    default: break;
}
}

void Core::updateProxyProperty2(int index, quint16 value)
{
    switch (index)
    {
    case 1:

        m_proxy->setMotorFrequency(qRound((value / 40.95*0.6) * 10.0) / 10.0); break;
    case 2:
        if (value == 0)
        {
            m_proxy->setFan1SwitchOn(false);
        }
        else
        {
            m_proxy->setFan1SwitchOn(true);
        }
        m_proxy->setFan1TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 3:
        if (value == 0)
        {
            m_proxy->setFan2SwitchOn(false);
        }
        else
        {
            m_proxy->setFan2SwitchOn(true);
        }
        m_proxy->setFan2TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 4:
        if (value == 0)
        {
            m_proxy->setFan3SwitchOn(false);
        }
        else
        {
            m_proxy->setFan3SwitchOn(true);
        }
        m_proxy->setFan3TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 5:
        if (value == 0)
        {
            m_proxy->setFan4SwitchOn(false);
        }
        else
        {
            m_proxy->setFan4SwitchOn(true);
        }
        m_proxy->setFan4TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 6:
        if (value == 0)
        {
            m_proxy->setFan5SwitchOn(false);
        }
        else
        {
            m_proxy->setFan5SwitchOn(true);
        }
        m_proxy->setFan5TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 7:
        if (value == 0)
        {
            m_proxy->setFan6SwitchOn(false);
        }
        else
        {
            m_proxy->setFan6SwitchOn(true);
        }
        m_proxy->setFan6TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 8:
        if (value == 0)
        {
            m_proxy->setFan7SwitchOn(false);
        }
        else
        {
            m_proxy->setFan7SwitchOn(true);
        }
        m_proxy->setFan7TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 9:
        if (value == 0)
        {
            m_proxy->setFan8SwitchOn(false);
        }
        else
        {
            m_proxy->setFan8SwitchOn(true);
        }
        m_proxy->setFan8TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 10:
        if (value == 0)
        {
            m_proxy->setFan9SwitchOn(false);
        }
        else 
        {
            m_proxy->setFan9SwitchOn(true);
        }
        m_proxy->setFan9TargetRpm(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 11:
        m_proxy->setReturnValveOpening(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 12:
        m_proxy->setOutValveOpening(qRound((value / 40.95) * 10.0) / 10.0); break;
    case 15: 
        m_proxy->setOutWaterTargetTemp(qRound((value) * 10.0) / 10.0); break;
    case 16:
        m_proxy->setTargetPressureDiff(qRound((value) * 10.0) / 10.0); break;
    default:
        break;
    }
}

void Core::saveProductionSettings()
{
    QSettings settings("production.ini", QSettings::IniFormat);
    settings.setValue("Production/ServerMode", m_proxy->m_modeSelect);
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
    settings.setValue("Production/targetPressureDiff", m_proxy->m_targetPressureDiff);
    settings.setValue("Production/outAirTemp", m_proxy->m_outWaterTargetTemp);
    settings.setValue("Production/P1", m_proxy->m_fanPidP);
    settings.setValue("Production/I1", m_proxy->m_fanPidI);
    settings.setValue("Production/D1", m_proxy->m_fanPidD);
    settings.setValue("Production/P2", m_proxy->m_outValveP);
    settings.setValue("Production/I2", m_proxy->m_outValveI);
    settings.setValue("Production/D2", m_proxy->m_outValveD);
    //settings.setValue("Production/ESTOP", m_proxy->m_fanEmergencySwitchOn);
    //settings.setValue("Production/motorpower", m_proxy->m_motorFrequencySwitchOn);



    settings.sync();
}
void Core::loadProductionSettings()
{
    QSettings settings("production.ini", QSettings::IniFormat);

    // 讀取數值，若檔案不存在則使用預設值 0.0
    m_proxy->setMotorFrequency(settings.value("Production/Hz", 0).toDouble());
    m_proxy->setFan1TargetRpm(settings.value("Production/fan1", 0).toDouble());
    m_proxy->setFan2TargetRpm(settings.value("Production/fan2", 0).toDouble());
    m_proxy->setFan3TargetRpm(settings.value("Production/fan3", 0).toDouble());
    m_proxy->setFan4TargetRpm(settings.value("Production/fan4", 0).toDouble());
    m_proxy->setFan5TargetRpm(settings.value("Production/fan5", 0).toDouble());
    m_proxy->setFan6TargetRpm(settings.value("Production/fan6", 0).toDouble());
    m_proxy->setFan7TargetRpm(settings.value("Production/fan7", 0).toDouble());
    m_proxy->setFan8TargetRpm(settings.value("Production/fan8", 0).toDouble());
    m_proxy->setFan9TargetRpm(settings.value("Production/fan9", 0).toDouble());
    m_proxy->setFan1TargetRpm(settings.value("Production/fan1", 0).toDouble());
    m_proxy->setTargetPressureDiff(settings.value("Production/targetPressureDiff", 0).toDouble());
    m_proxy->setReturnValveOpening(settings.value("Production/returnWaterOpen", 0).toDouble());
    m_proxy->setOutWaterTargetTemp(settings.value("Production/outAirTemp", 0).toDouble());
    m_proxy->setFanPidP(settings.value("Production/P1", 0).toDouble());
    m_proxy->setFanPidI(settings.value("Production/I1", 0).toDouble());
    m_proxy->setFanPidD(settings.value("Production/D1", 0).toDouble());
    m_proxy->setOutValveP(settings.value("Production/P2", 0).toDouble());
    m_proxy->setOutValveI(settings.value("Production/I2", 0).toDouble());
    m_proxy->setOutValveD(settings.value("Production/D2", 0).toDouble());
    m_proxy->setFanEmergencySwitchOn(settings.value("Production/ESTOP", true).toBool());
    m_proxy->setMotorFrequencySwitchOn(settings.value("Production/motorpower", true).toBool());
}
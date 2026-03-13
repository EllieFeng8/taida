#pragma once
#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <sstream>
#include <iomanip>
#include <string>

class TdProxy : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    // =========================
    // 入水數據
    // =========================
    Q_PROPERTY(double inWaterTemp READ getInWaterTemp WRITE setInWaterTemp NOTIFY inWaterTempChanged)
    Q_PROPERTY(double inWaterPressure READ getInWaterPressure WRITE setInWaterPressure NOTIFY inWaterPressureChanged)

    // =========================
    // 出水數據
    // =========================
    Q_PROPERTY(double outWaterTemp READ getOutWaterTemp WRITE setOutWaterTemp NOTIFY outWaterTempChanged)
    Q_PROPERTY(double outWaterPressure READ getOutWaterPressure WRITE setOutWaterPressure NOTIFY outWaterPressureChanged)

    // =========================
    // 回水數據
    // =========================
    Q_PROPERTY(double returnWaterTemp READ getReturnWaterTemp WRITE setReturnWaterTemp NOTIFY returnWaterTempChanged)
    Q_PROPERTY(double returnWaterPressure READ getReturnWaterPressure WRITE setReturnWaterPressure NOTIFY returnWaterPressureChanged)

    // =========================
    // 冷排溫度監控
    // =========================
    Q_PROPERTY(double condenserLeft1Temp READ getCondenserLeft1Temp WRITE setCondenserLeft1Temp NOTIFY condenserLeft1TempChanged)
    Q_PROPERTY(double condenserRight1Temp READ getCondenserRight1Temp WRITE setCondenserRight1Temp NOTIFY condenserRight1TempChanged)
    Q_PROPERTY(double condenserLeft2Temp READ getCondenserLeft2Temp WRITE setCondenserLeft2Temp NOTIFY condenserLeft2TempChanged)
    Q_PROPERTY(double condenserRight2Temp READ getCondenserRight2Temp WRITE setCondenserRight2Temp NOTIFY condenserRight2TempChanged)

    // =========================
    // 入風溫濕度
    // =========================
    Q_PROPERTY(double inletAirTemp READ getInletAirTemp WRITE setInletAirTemp NOTIFY inletAirTempChanged)
    Q_PROPERTY(double inletAirHumidity READ getInletAirHumidity WRITE setInletAirHumidity NOTIFY inletAirHumidityChanged)

    // =========================
    // 出風溫度
    // =========================
    Q_PROPERTY(double outletAirTemp READ getOutletAirTemp WRITE setOutletAirTemp NOTIFY outletAirTempChanged)
    Q_PROPERTY(double outWaterTargetTemp READ getOutWaterTargetTemp WRITE setOutWaterTargetTemp NOTIFY outWaterTargetTempChanged)
    Q_PROPERTY(double outWaterTargetTempP READ getOutWaterTargetTempP WRITE setOutWaterTargetTempP NOTIFY outWaterTargetTempPChanged)

    // =========================
    // 出水閥控制
    // =========================
    Q_PROPERTY(double outValveOpening READ getOutValveOpening WRITE setOutValveOpening NOTIFY outValveOpeningChanged)
    Q_PROPERTY(double outValveP READ getOutValveP WRITE setOutValveP NOTIFY outValvePChanged)
    Q_PROPERTY(double outValveI READ getOutValveI WRITE setOutValveI NOTIFY outValveIChanged)
    Q_PROPERTY(double outValveD READ getOutValveD WRITE setOutValveD NOTIFY outValveDChanged)

    Q_PROPERTY(double outValveOpeningP READ getOutValveOpeningP WRITE setOutValveOpeningP NOTIFY outValveOpeningPChanged)
    Q_PROPERTY(double outValvePP READ getOutValvePP WRITE setOutValvePP NOTIFY outValvePPChanged)
    Q_PROPERTY(double outValveIP READ getOutValveIP WRITE setOutValveIP NOTIFY outValveIPChanged)
    Q_PROPERTY(double outValveDP READ getOutValveDP WRITE setOutValveDP NOTIFY outValveDPChanged)

    // =========================
    // 回水閥控制
    // =========================
    Q_PROPERTY(double returnValveOpening READ getReturnValveOpening WRITE setReturnValveOpening NOTIFY returnValveOpeningChanged)
    Q_PROPERTY(double returnValveOpeningP READ getReturnValveOpeningP WRITE setReturnValveOpeningP NOTIFY returnValveOpeningPChanged)

    Q_PROPERTY(double returnValveValue READ getReturnValveValue WRITE setReturnValveValue NOTIFY returnValveValueChanged)
    Q_PROPERTY(double returnValveValueP READ getReturnValveValueP WRITE setReturnValveValueP NOTIFY returnValveValuePChanged)

    // =========================
    // 馬達頻率控制
    // =========================
    Q_PROPERTY(double motorFrequency READ getMotorFrequency WRITE setMotorFrequency NOTIFY motorFrequencyChanged)
    Q_PROPERTY(double motorFrequencyP READ getMotorFrequencyP WRITE setMotorFrequencyP NOTIFY motorFrequencyPChanged)
    Q_PROPERTY(double currentWaterFlow READ getCurrentWaterFlow WRITE setCurrentWaterFlow NOTIFY currentWaterFlowChanged)

    Q_PROPERTY(double heatExchange READ getHeatExchange WRITE setHeatExchange NOTIFY heatExchangeChanged)
    // Q_PROPERTY(double heatExchangeP READ getHeatExchangeP WRITE setHeatExchangeP NOTIFY heatExchangePChanged)

    // =========================
    // 風扇控制 / 壓差 / PID
    // =========================
    Q_PROPERTY(double pressureDiff READ getPressureDiff WRITE setPressureDiff NOTIFY pressureDiffChanged)
    Q_PROPERTY(double targetPressureDiff READ getTargetPressureDiff WRITE setTargetPressureDiff NOTIFY targetPressureDiffChanged)
    Q_PROPERTY(double fanPidP READ getFanPidP WRITE setFanPidP NOTIFY fanPidPChanged)
    Q_PROPERTY(double fanPidI READ getFanPidI WRITE setFanPidI NOTIFY fanPidIChanged)
    Q_PROPERTY(double fanPidD READ getFanPidD WRITE setFanPidD NOTIFY fanPidDChanged)
    Q_PROPERTY(double fanPidPP READ getFanPidPP WRITE setFanPidPP NOTIFY fanPidPPChanged)
    Q_PROPERTY(double fanPidIP READ getFanPidIP WRITE setFanPidIP NOTIFY fanPidIPChanged)
    Q_PROPERTY(double fanPidDP READ getFanPidDP WRITE setFanPidDP NOTIFY fanPidDPChanged)

    // =========================
    // 風扇 1 ~ 9 目標轉速
    // =========================
    Q_PROPERTY(double fan1TargetRpm READ getFan1TargetRpm WRITE setFan1TargetRpm NOTIFY fan1TargetRpmChanged)
    Q_PROPERTY(double fan2TargetRpm READ getFan2TargetRpm WRITE setFan2TargetRpm NOTIFY fan2TargetRpmChanged)
    Q_PROPERTY(double fan3TargetRpm READ getFan3TargetRpm WRITE setFan3TargetRpm NOTIFY fan3TargetRpmChanged)
    Q_PROPERTY(double fan4TargetRpm READ getFan4TargetRpm WRITE setFan4TargetRpm NOTIFY fan4TargetRpmChanged)
    Q_PROPERTY(double fan5TargetRpm READ getFan5TargetRpm WRITE setFan5TargetRpm NOTIFY fan5TargetRpmChanged)
    Q_PROPERTY(double fan6TargetRpm READ getFan6TargetRpm WRITE setFan6TargetRpm NOTIFY fan6TargetRpmChanged)
    Q_PROPERTY(double fan7TargetRpm READ getFan7TargetRpm WRITE setFan7TargetRpm NOTIFY fan7TargetRpmChanged)
    Q_PROPERTY(double fan8TargetRpm READ getFan8TargetRpm WRITE setFan8TargetRpm NOTIFY fan8TargetRpmChanged)
    Q_PROPERTY(double fan9TargetRpm READ getFan9TargetRpm WRITE setFan9TargetRpm NOTIFY fan9TargetRpmChanged)
    Q_PROPERTY(double fanAllTargetRpm READ getFanAllTargetRpm WRITE setFanAllTargetRpm NOTIFY fanAllTargetRpmChanged)

    Q_PROPERTY(double fan1TargetRpmPercent READ getFan1TargetRpmPercent WRITE setFan1TargetRpmPercent NOTIFY fan1TargetRpmPercentChanged)
    Q_PROPERTY(double fan2TargetRpmPercent READ getFan2TargetRpmPercent WRITE setFan2TargetRpmPercent NOTIFY fan2TargetRpmPercentChanged)
    Q_PROPERTY(double fan3TargetRpmPercent READ getFan3TargetRpmPercent WRITE setFan3TargetRpmPercent NOTIFY fan3TargetRpmPercentChanged)
    Q_PROPERTY(double fan4TargetRpmPercent READ getFan4TargetRpmPercent WRITE setFan4TargetRpmPercent NOTIFY fan4TargetRpmPercentChanged)
    Q_PROPERTY(double fan5TargetRpmPercent READ getFan5TargetRpmPercent WRITE setFan5TargetRpmPercent NOTIFY fan5TargetRpmPercentChanged)
    Q_PROPERTY(double fan6TargetRpmPercent READ getFan6TargetRpmPercent WRITE setFan6TargetRpmPercent NOTIFY fan6TargetRpmPercentChanged)
    Q_PROPERTY(double fan7TargetRpmPercent READ getFan7TargetRpmPercent WRITE setFan7TargetRpmPercent NOTIFY fan7TargetRpmPercentChanged)
    Q_PROPERTY(double fan8TargetRpmPercent READ getFan8TargetRpmPercent WRITE setFan8TargetRpmPercent NOTIFY fan8TargetRpmPercentChanged)
    Q_PROPERTY(double fan9TargetRpmPercent READ getFan9TargetRpmPercent WRITE setFan9TargetRpmPercent NOTIFY fan9TargetRpmPercentChanged)
    Q_PROPERTY(double fanAllTargetRpmPercent READ getFanAllTargetRpmPercent WRITE setFanAllTargetRpmPercent NOTIFY fanAllTargetRpmPercentChanged)

    Q_PROPERTY(double fan1TargetRpmP READ getFan1TargetRpmP WRITE setFan1TargetRpmP NOTIFY fan1TargetRpmPChanged)
    Q_PROPERTY(double fan2TargetRpmP READ getFan2TargetRpmP WRITE setFan2TargetRpmP NOTIFY fan2TargetRpmPChanged)
    Q_PROPERTY(double fan3TargetRpmP READ getFan3TargetRpmP WRITE setFan3TargetRpmP NOTIFY fan3TargetRpmPChanged)
    Q_PROPERTY(double fan4TargetRpmP READ getFan4TargetRpmP WRITE setFan4TargetRpmP NOTIFY fan4TargetRpmPChanged)
    Q_PROPERTY(double fan5TargetRpmP READ getFan5TargetRpmP WRITE setFan5TargetRpmP NOTIFY fan5TargetRpmPChanged)
    Q_PROPERTY(double fan6TargetRpmP READ getFan6TargetRpmP WRITE setFan6TargetRpmP NOTIFY fan6TargetRpmPChanged)
    Q_PROPERTY(double fan7TargetRpmP READ getFan7TargetRpmP WRITE setFan7TargetRpmP NOTIFY fan7TargetRpmPChanged)
    Q_PROPERTY(double fan8TargetRpmP READ getFan8TargetRpmP WRITE setFan8TargetRpmP NOTIFY fan8TargetRpmPChanged)
    Q_PROPERTY(double fan9TargetRpmP READ getFan9TargetRpmP WRITE setFan9TargetRpmP NOTIFY fan9TargetRpmPChanged)
    Q_PROPERTY(double fanAllTargetRpmP READ getFanAllTargetRpmP WRITE setFanAllTargetRpmP NOTIFY fanAllTargetRpmPChanged)

    // =========================
    // 系統 / 區塊開關
    // =========================
    Q_PROPERTY(bool systemRunning READ getSystemRunning WRITE setSystemRunning NOTIFY systemRunningChanged)
    Q_PROPERTY(bool outValvePidOn READ getOutValvePidOn WRITE setOutValvePidOn NOTIFY outValvePidOnChanged)
    //TRUE=正向 FALSE=反向
    Q_PROPERTY(bool outValveCorrectionOn READ getOutValveCorrectionOn WRITE setOutValveCorrectionOn NOTIFY outValveCorrectionOnChanged)
    Q_PROPERTY(bool motorFrequencySwitchOn READ getMotorFrequencySwitchOn WRITE setMotorFrequencySwitchOn NOTIFY motorFrequencySwitchOnChanged)
    Q_PROPERTY(bool fanAllOn READ getFanAllOn WRITE setFanAllOn NOTIFY fanAllOnChanged)
    Q_PROPERTY(bool fanPidMonitorOn READ getFanPidMonitorOn WRITE setFanPidMonitorOn NOTIFY fanPidMonitorOnChanged)

    // =========================
    // 風扇開關
    // =========================
    //TRUE=正向 FALSE=反向
    Q_PROPERTY(bool fanCorrectionSwitchOn READ getFanCorrectionSwitchOn WRITE setFanCorrectionSwitchOn NOTIFY fanCorrectionSwitchOnChanged)
    Q_PROPERTY(bool fan1SwitchOn READ getFan1SwitchOn WRITE setFan1SwitchOn NOTIFY fan1SwitchOnChanged)
    Q_PROPERTY(bool fan2SwitchOn READ getFan2SwitchOn WRITE setFan2SwitchOn NOTIFY fan2SwitchOnChanged)
    Q_PROPERTY(bool fan3SwitchOn READ getFan3SwitchOn WRITE setFan3SwitchOn NOTIFY fan3SwitchOnChanged)
    Q_PROPERTY(bool fan4SwitchOn READ getFan4SwitchOn WRITE setFan4SwitchOn NOTIFY fan4SwitchOnChanged)
    Q_PROPERTY(bool fan5SwitchOn READ getFan5SwitchOn WRITE setFan5SwitchOn NOTIFY fan5SwitchOnChanged)
    Q_PROPERTY(bool fan6SwitchOn READ getFan6SwitchOn WRITE setFan6SwitchOn NOTIFY fan6SwitchOnChanged)
    Q_PROPERTY(bool fan7SwitchOn READ getFan7SwitchOn WRITE setFan7SwitchOn NOTIFY fan7SwitchOnChanged)
    Q_PROPERTY(bool fan8SwitchOn READ getFan8SwitchOn WRITE setFan8SwitchOn NOTIFY fan8SwitchOnChanged)
    Q_PROPERTY(bool fan9SwitchOn READ getFan9SwitchOn WRITE setFan9SwitchOn NOTIFY fan9SwitchOnChanged)

    // =========================
    // 按鈕狀態
    // =========================
    Q_PROPERTY(bool confirmOutValveButton READ getConfirmOutValveButton WRITE setConfirmOutValveButton NOTIFY confirmOutValveButtonChanged)
    Q_PROPERTY(bool confirmReturnValveButton READ getConfirmReturnValveButton WRITE setConfirmReturnValveButton NOTIFY confirmReturnValveButtonChanged)
    Q_PROPERTY(bool applyMotorFrequencyButton READ getApplyMotorFrequencyButton WRITE setApplyMotorFrequencyButton NOTIFY applyMotorFrequencyButtonChanged)
    Q_PROPERTY(bool applyFanPidButton READ getApplyFanPidButton WRITE setApplyFanPidButton NOTIFY applyFanPidButtonChanged)

    Q_PROPERTY(bool fan1ConfirmButton READ getFan1ConfirmButton WRITE setFan1ConfirmButton NOTIFY fan1ConfirmButtonChanged)
    Q_PROPERTY(bool fan2ConfirmButton READ getFan2ConfirmButton WRITE setFan2ConfirmButton NOTIFY fan2ConfirmButtonChanged)
    Q_PROPERTY(bool fan3ConfirmButton READ getFan3ConfirmButton WRITE setFan3ConfirmButton NOTIFY fan3ConfirmButtonChanged)
    Q_PROPERTY(bool fan4ConfirmButton READ getFan4ConfirmButton WRITE setFan4ConfirmButton NOTIFY fan4ConfirmButtonChanged)
    Q_PROPERTY(bool fan5ConfirmButton READ getFan5ConfirmButton WRITE setFan5ConfirmButton NOTIFY fan5ConfirmButtonChanged)
    Q_PROPERTY(bool fan6ConfirmButton READ getFan6ConfirmButton WRITE setFan6ConfirmButton NOTIFY fan6ConfirmButtonChanged)
    Q_PROPERTY(bool fan7ConfirmButton READ getFan7ConfirmButton WRITE setFan7ConfirmButton NOTIFY fan7ConfirmButtonChanged)
    Q_PROPERTY(bool fan8ConfirmButton READ getFan8ConfirmButton WRITE setFan8ConfirmButton NOTIFY fan8ConfirmButtonChanged)
    Q_PROPERTY(bool fan9ConfirmButton READ getFan9ConfirmButton WRITE setFan9ConfirmButton NOTIFY fan9ConfirmButtonChanged)

    // =========================
    // 網路設定數值欄位
    // =========================
    Q_PROPERTY(QString ipAddress READ getIpAddress WRITE setIpAddress NOTIFY ipAddressChanged)
    Q_PROPERTY(QString subnetMask READ getSubnetMask WRITE setSubnetMask NOTIFY subnetMaskChanged)
    Q_PROPERTY(QString defaultGateway READ getDefaultGateway WRITE setDefaultGateway NOTIFY defaultGatewayChanged)
    Q_PROPERTY(QString dnsServer READ getDnsServer WRITE setDnsServer NOTIFY dnsServerChanged)


public:

    explicit TdProxy(QObject *parent = nullptr) : QObject(parent) {}
    // =========================
    // 入水數據
    // =========================
    Q_INVOKABLE double getInWaterTemp() const { return m_inWaterTemp; }
    Q_INVOKABLE void setInWaterTemp(double value)
    {
        m_inWaterTemp = value;
        emit inWaterTempChanged(m_inWaterTemp);
    }

    Q_INVOKABLE double getInWaterPressure() const { return m_inWaterPressure; }
    Q_INVOKABLE void setInWaterPressure(double value)
    {
        m_inWaterPressure = value;
        emit inWaterPressureChanged(m_inWaterPressure);
    }

    // =========================
    // 出水數據
    // =========================
    Q_INVOKABLE double getOutWaterTemp() const { return m_outWaterTemp; }
    Q_INVOKABLE void setOutWaterTemp(double value)
    {
        m_outWaterTemp = value;
        emit outWaterTempChanged(m_outWaterTemp);
    }

    Q_INVOKABLE double getOutWaterPressure() const { return m_outWaterPressure; }
    Q_INVOKABLE void setOutWaterPressure(double value)
    {
        m_outWaterPressure = value;
        emit outWaterPressureChanged(m_outWaterPressure);
    }

    // =========================
    // 回水數據
    // =========================
    Q_INVOKABLE double getReturnWaterTemp() const { return m_returnWaterTemp; }
    Q_INVOKABLE void setReturnWaterTemp(double value)
    {
        m_returnWaterTemp = value;
        emit returnWaterTempChanged(m_returnWaterTemp);
    }

    Q_INVOKABLE double getReturnWaterPressure() const { return m_returnWaterPressure; }
    Q_INVOKABLE void setReturnWaterPressure(double value)
    {
        m_returnWaterPressure = value;
        emit returnWaterPressureChanged(m_returnWaterPressure);
    }

    // =========================
    // 冷排溫度監控
    // =========================
    Q_INVOKABLE double getCondenserLeft1Temp() const { return m_condenserLeft1Temp; }
    Q_INVOKABLE void setCondenserLeft1Temp(double value)
    {
        m_condenserLeft1Temp = value;
        emit condenserLeft1TempChanged(m_condenserLeft1Temp);
    }

    Q_INVOKABLE double getCondenserRight1Temp() const { return m_condenserRight1Temp; }
    Q_INVOKABLE void setCondenserRight1Temp(double value)
    {
        m_condenserRight1Temp = value;
        emit condenserRight1TempChanged(m_condenserRight1Temp);
    }

    Q_INVOKABLE double getCondenserLeft2Temp() const { return m_condenserLeft2Temp; }
    Q_INVOKABLE void setCondenserLeft2Temp(double value)
    {
        m_condenserLeft2Temp = value;
        emit condenserLeft2TempChanged(m_condenserLeft2Temp);
    }

    Q_INVOKABLE double getCondenserRight2Temp() const { return m_condenserRight2Temp; }
    Q_INVOKABLE void setCondenserRight2Temp(double value)
    {
        m_condenserRight2Temp = value;
        emit condenserRight2TempChanged(m_condenserRight2Temp);
    }

    // =========================
    // 入風溫濕度
    // =========================
    Q_INVOKABLE double getInletAirTemp() const { return m_inletAirTemp; }
    Q_INVOKABLE void setInletAirTemp(double value)
    {
        m_inletAirTemp = value;
        emit inletAirTempChanged(m_inletAirTemp);
    }

    Q_INVOKABLE double getInletAirHumidity() const { return m_inletAirHumidity; }
    Q_INVOKABLE void setInletAirHumidity(double value)
    {
        m_inletAirHumidity = value;
        emit inletAirHumidityChanged(m_inletAirHumidity);
    }

    // =========================
    // 出風溫度
    // =========================
    Q_INVOKABLE double getOutletAirTemp() const { return m_outletAirTemp; }
    Q_INVOKABLE void setOutletAirTemp(double value)
    {
        m_outletAirTemp = value;
        emit outletAirTempChanged(m_outletAirTemp);
    }

    Q_INVOKABLE double getOutWaterTargetTemp() const { return m_outWaterTargetTemp; }
    Q_INVOKABLE void setOutWaterTargetTemp(double value)
    {
        m_outWaterTargetTemp = value;
        emit outWaterTargetTempChanged(m_outWaterTargetTemp);
    }
    Q_INVOKABLE double getOutWaterTargetTempP() const { return m_outWaterTargetTempP; }
    Q_INVOKABLE void setOutWaterTargetTempP(double value)
    {
        m_outWaterTargetTempP = value;
        emit outWaterTargetTempPChanged(m_outWaterTargetTempP);
    }

    // =========================
    // 出水閥控制
    // =========================
    Q_INVOKABLE double getOutValveOpening() const { return m_outValveOpening; }
    Q_INVOKABLE void setOutValveOpening(double value)
    {
        m_outValveOpening = value;
        emit outValveOpeningChanged(m_outValveOpening);
    }

    Q_INVOKABLE double getOutValveP() const { return m_outValveP; }
    Q_INVOKABLE void setOutValveP(double value)
    {
        m_outValveP = value;
        emit outValvePChanged(m_outValveP);
    }

    Q_INVOKABLE double getOutValveI() const { return m_outValveI; }
    Q_INVOKABLE void setOutValveI(double value)
    {
        m_outValveI = value;
        emit outValveIChanged(m_outValveI);
    }

    Q_INVOKABLE double getOutValveD() const { return m_outValveD; }
    Q_INVOKABLE void setOutValveD(double value)
    {
        m_outValveD = value;
        emit outValveDChanged(m_outValveD);
    }

    Q_INVOKABLE double getOutValveOpeningP() const { return m_outValveOpeningP; }
    Q_INVOKABLE void setOutValveOpeningP(double value)
    {
        m_outValveOpeningP = value;
        emit outValveOpeningPChanged(m_outValveOpeningP);
    }

    Q_INVOKABLE double getOutValvePP() const { return m_outValvePP; }
    Q_INVOKABLE void setOutValvePP(double value)
    {
        m_outValvePP = value;
        emit outValvePPChanged(m_outValvePP);
    }

    Q_INVOKABLE double getOutValveIP() const { return m_outValveIP; }
    Q_INVOKABLE void setOutValveIP(double value)
    {
        m_outValveIP = value;
        emit outValveIChanged(m_outValveIP);
    }

    Q_INVOKABLE double getOutValveDP() const { return m_outValveDP; }
    Q_INVOKABLE void setOutValveDP(double value)
    {
        m_outValveDP = value;
        emit outValveDPChanged(m_outValveDP);
    }

    // =========================
    // 回水閥控制
    // =========================
    Q_INVOKABLE double getReturnValveOpening() const { return m_returnValveOpening; }
    Q_INVOKABLE void setReturnValveOpening(double value)
    {
        m_returnValveOpening = value;
        emit returnValveOpeningChanged(m_returnValveOpening);
    }
    Q_INVOKABLE double getReturnValveOpeningP() const { return m_returnValveOpeningP; }
    Q_INVOKABLE void setReturnValveOpeningP(double value)
    {
        m_returnValveOpeningP = value;
        emit returnValveOpeningPChanged(m_returnValveOpeningP);
    }
    Q_INVOKABLE double getReturnValveValue() const { return m_returnValveValue; }
    Q_INVOKABLE void setReturnValveValue(double value)
    {
        m_returnValveValue = value;
        emit returnValveValueChanged(m_returnValveValue);
    }
    Q_INVOKABLE double getReturnValveValueP() const { return m_returnValveValueP; }
    Q_INVOKABLE void setReturnValveValueP(double value)
    {
        m_returnValveValueP = value;
        emit returnValveValuePChanged(m_returnValveValueP);
    }

    // =========================
    // 馬達頻率控制
    // =========================
    Q_INVOKABLE double getMotorFrequency() const { return m_motorFrequency; }
    Q_INVOKABLE void setMotorFrequency(double value)
    {
        m_motorFrequency = value;
        emit motorFrequencyChanged(m_motorFrequency);
    }
    Q_INVOKABLE double getMotorFrequencyP() const { return m_motorFrequencyP; }
    Q_INVOKABLE void setMotorFrequencyP(double value)
    {
        m_motorFrequencyP = value;
        emit motorFrequencyPChanged(m_motorFrequencyP);
    }

    Q_INVOKABLE double getCurrentWaterFlow() const { return m_currentWaterFlow; }
    Q_INVOKABLE void setCurrentWaterFlow(double value)
    {
        m_currentWaterFlow = value;
        emit currentWaterFlowChanged(m_currentWaterFlow);
    }

    Q_INVOKABLE double getHeatExchange() const { return m_heatExchange; }
    Q_INVOKABLE void setHeatExchange(double value)
    {
        m_heatExchange = value;
        emit heatExchangeChanged(m_heatExchange);
    }
    // Q_INVOKABLE double getHeatExchangeP() const { return m_heatExchangeP; }
    // Q_INVOKABLE void setHeatExchangeP(double value)
    // {
    //     m_heatExchangeP = value;
    //     emit heatExchangePChanged(m_heatExchangeP);
    // }

    // =========================
    // 風扇控制 / 壓差 / PID
    // =========================
    Q_INVOKABLE double getPressureDiff() const { return m_pressureDiff; }
    Q_INVOKABLE void setPressureDiff(double value)
    {
        m_pressureDiff = value;
        emit pressureDiffChanged(m_pressureDiff);
    }
    Q_INVOKABLE double getTargetPressureDiff() const { return m_targetPressureDiff; }
    Q_INVOKABLE void setTargetPressureDiff(double value)
    {
        m_targetPressureDiff = value;
        emit targetPressureDiffChanged(m_targetPressureDiff);
    }

    Q_INVOKABLE double getFanPidP() const { return m_fanPidP; }
    Q_INVOKABLE void setFanPidP(double value)
    {
        m_fanPidP = value;
        emit fanPidPChanged(m_fanPidP);
    }

    Q_INVOKABLE double getFanPidI() const { return m_fanPidI; }
    Q_INVOKABLE void setFanPidI(double value)
    {
        m_fanPidI = value;
        emit fanPidIChanged(m_fanPidI);
    }

    Q_INVOKABLE double getFanPidD() const { return m_fanPidD; }
    Q_INVOKABLE void setFanPidD(double value)
    {
        m_fanPidD = value;
        emit fanPidDChanged(m_fanPidD);
    }

    Q_INVOKABLE double getFanPidPP() const { return m_fanPidPP; }
    Q_INVOKABLE void setFanPidPP(double value)
    {
        m_fanPidPP = value;
        emit fanPidPPChanged(m_fanPidPP);
    }

    Q_INVOKABLE double getFanPidIP() const { return m_fanPidIP; }
    Q_INVOKABLE void setFanPidIP(double value)
    {
        m_fanPidIP = value;
        emit fanPidIPChanged(m_fanPidIP);
    }

    Q_INVOKABLE double getFanPidDP() const { return m_fanPidDP; }
    Q_INVOKABLE void setFanPidDP(double value)
    {
        m_fanPidDP = value;
        emit fanPidDPChanged(m_fanPidDP);
    }

    // =========================
    // 風扇 1 ~ 9
    // =========================
    Q_INVOKABLE double getFan1TargetRpm() const { return m_fan1TargetRpm; }
    Q_INVOKABLE void setFan1TargetRpm(double value)
    {
        m_fan1TargetRpm = value;
        emit fan1TargetRpmChanged(m_fan1TargetRpm);
    }

    Q_INVOKABLE double getFan2TargetRpm() const { return m_fan2TargetRpm; }
    Q_INVOKABLE void setFan2TargetRpm(double value)
    {
        m_fan2TargetRpm = value;
        emit fan2TargetRpmChanged(m_fan2TargetRpm);
    }

    Q_INVOKABLE double getFan3TargetRpm() const { return m_fan3TargetRpm; }
    Q_INVOKABLE void setFan3TargetRpm(double value)
    {
        m_fan3TargetRpm = value;
        emit fan3TargetRpmChanged(m_fan3TargetRpm);
    }

    Q_INVOKABLE double getFan4TargetRpm() const { return m_fan4TargetRpm; }
    Q_INVOKABLE void setFan4TargetRpm(double value)
    {
        m_fan4TargetRpm = value;
        emit fan4TargetRpmChanged(m_fan4TargetRpm);
    }

    Q_INVOKABLE double getFan5TargetRpm() const { return m_fan5TargetRpm; }
    Q_INVOKABLE void setFan5TargetRpm(double value)
    {
        m_fan5TargetRpm = value;
        emit fan5TargetRpmChanged(m_fan5TargetRpm);
    }

    Q_INVOKABLE double getFan6TargetRpm() const { return m_fan6TargetRpm; }
    Q_INVOKABLE void setFan6TargetRpm(double value)
    {
        m_fan6TargetRpm = value;
        emit fan6TargetRpmChanged(m_fan6TargetRpm);
    }

    Q_INVOKABLE double getFan7TargetRpm() const { return m_fan7TargetRpm; }
    Q_INVOKABLE void setFan7TargetRpm(double value)
    {
        m_fan7TargetRpm = value;
        emit fan7TargetRpmChanged(m_fan7TargetRpm);
    }

    Q_INVOKABLE double getFan8TargetRpm() const { return m_fan8TargetRpm; }
    Q_INVOKABLE void setFan8TargetRpm(double value)
    {
        m_fan8TargetRpm = value;
        emit fan8TargetRpmChanged(m_fan8TargetRpm);
    }

    Q_INVOKABLE double getFan9TargetRpm() const { return m_fan9TargetRpm; }
    Q_INVOKABLE void setFan9TargetRpm(double value)
    {
        m_fan9TargetRpm = value;
        emit fan9TargetRpmChanged(m_fan9TargetRpm);
    }
    Q_INVOKABLE double getFanAllTargetRpm() const { return m_fanAllTargetRpm; }
    Q_INVOKABLE void setFanAllTargetRpm(double value)
    {
        m_fanAllTargetRpm = value;
        emit fanAllTargetRpmChanged(m_fanAllTargetRpm);
    }

    Q_INVOKABLE double getFan1TargetRpmP() const { return m_fan1TargetRpmP; }
    Q_INVOKABLE void setFan1TargetRpmP(double value)
    {
        m_fan1TargetRpmP = value;
        emit fan1TargetRpmPChanged(m_fan1TargetRpmP);
    }

    Q_INVOKABLE double getFan2TargetRpmP() const { return m_fan2TargetRpmP; }
    Q_INVOKABLE void setFan2TargetRpmP(double value)
    {
        m_fan2TargetRpmP = value;
        emit fan2TargetRpmPChanged(m_fan2TargetRpmP);
    }

    Q_INVOKABLE double getFan3TargetRpmP() const { return m_fan3TargetRpmP; }
    Q_INVOKABLE void setFan3TargetRpmP(double value)
    {
        m_fan3TargetRpmP = value;
        emit fan3TargetRpmPChanged(m_fan3TargetRpmP);
    }

    Q_INVOKABLE double getFan4TargetRpmP() const { return m_fan4TargetRpmP; }
    Q_INVOKABLE void setFan4TargetRpmP(double value)
    {
        m_fan4TargetRpmP = value;
        emit fan4TargetRpmPChanged(m_fan4TargetRpmP);
    }

    Q_INVOKABLE double getFan5TargetRpmP() const { return m_fan5TargetRpmP; }
    Q_INVOKABLE void setFan5TargetRpmP(double value)
    {
        m_fan5TargetRpmP = value;
        emit fan5TargetRpmPChanged(m_fan5TargetRpmP);
    }

    Q_INVOKABLE double getFan6TargetRpmP() const { return m_fan6TargetRpmP; }
    Q_INVOKABLE void setFan6TargetRpmP(double value)
    {
        m_fan6TargetRpmP = value;
        emit fan6TargetRpmPChanged(m_fan6TargetRpmP);
    }

    Q_INVOKABLE double getFan7TargetRpmP() const { return m_fan7TargetRpmP; }
    Q_INVOKABLE void setFan7TargetRpmP(double value)
    {
        m_fan7TargetRpmP = value;
        emit fan7TargetRpmPChanged(m_fan7TargetRpmP);
    }

    Q_INVOKABLE double getFan8TargetRpmP() const { return m_fan8TargetRpmP; }
    Q_INVOKABLE void setFan8TargetRpmP(double value)
    {
        m_fan8TargetRpmP = value;
        emit fan8TargetRpmPChanged(m_fan8TargetRpmP);
    }

    Q_INVOKABLE double getFan9TargetRpmP() const { return m_fan9TargetRpmP; }
    Q_INVOKABLE void setFan9TargetRpmP(double value)
    {
        m_fan9TargetRpmP = value;
        emit fan9TargetRpmPChanged(m_fan9TargetRpmP);
    }
    Q_INVOKABLE double getFanAllTargetRpmP() const { return m_fanAllTargetRpmP; }
    Q_INVOKABLE void setFanAllTargetRpmP(double value)
    {
        m_fanAllTargetRpmP = value;
        emit fanAllTargetRpmPChanged(m_fanAllTargetRpmP);
    }
    Q_INVOKABLE double getFan1TargetRpmPercent() const { return m_fan1TargetRpmPercent; }
    Q_INVOKABLE void setFan1TargetRpmPercent(double value)
    {
        m_fan1TargetRpmPercent = value;
        emit fan1TargetRpmPercentChanged(m_fan1TargetRpmPercent);
    }

    Q_INVOKABLE double getFan2TargetRpmPercent() const { return m_fan2TargetRpmPercent; }
    Q_INVOKABLE void setFan2TargetRpmPercent(double value)
    {
        m_fan2TargetRpmPercent = value;
        emit fan2TargetRpmPercentChanged(m_fan2TargetRpmPercent);
    }

    Q_INVOKABLE double getFan3TargetRpmPercent() const { return m_fan3TargetRpmPercent; }
    Q_INVOKABLE void setFan3TargetRpmPercent(double value)
    {
        m_fan3TargetRpmPercent = value;
        emit fan3TargetRpmPercentChanged(m_fan3TargetRpmPercent);
    }

    Q_INVOKABLE double getFan4TargetRpmPercent() const { return m_fan4TargetRpmPercent; }
    Q_INVOKABLE void setFan4TargetRpmPercent(double value)
    {
        m_fan4TargetRpmPercent = value;
        emit fan4TargetRpmPercentChanged(m_fan4TargetRpmPercent);
    }

    Q_INVOKABLE double getFan5TargetRpmPercent() const { return m_fan5TargetRpmPercent; }
    Q_INVOKABLE void setFan5TargetRpmPercent(double value)
    {
        m_fan5TargetRpmPercent = value;
        emit fan5TargetRpmPercentChanged(m_fan5TargetRpmPercent);
    }

    Q_INVOKABLE double getFan6TargetRpmPercent() const { return m_fan6TargetRpmPercent; }
    Q_INVOKABLE void setFan6TargetRpmPercent(double value)
    {
        m_fan6TargetRpmPercent = value;
        emit fan6TargetRpmPercentChanged(m_fan6TargetRpmPercent);
    }

    Q_INVOKABLE double getFan7TargetRpmPercent() const { return m_fan7TargetRpmPercent; }
    Q_INVOKABLE void setFan7TargetRpmPercent(double value)
    {
        m_fan7TargetRpmPercent = value;
        emit fan7TargetRpmPercentChanged(m_fan7TargetRpmPercent);
    }

    Q_INVOKABLE double getFan8TargetRpmPercent() const { return m_fan8TargetRpmPercent; }
    Q_INVOKABLE void setFan8TargetRpmPercent(double value)
    {
        m_fan8TargetRpmPercent = value;
        emit fan8TargetRpmPercentChanged(m_fan8TargetRpmPercent);
    }

    Q_INVOKABLE double getFan9TargetRpmPercent() const { return m_fan9TargetRpmPercent; }
    Q_INVOKABLE void setFan9TargetRpmPercent(double value)
    {
        m_fan9TargetRpmPercent = value;
        emit fan9TargetRpmPercentChanged(m_fan9TargetRpmPercent);
    }
    Q_INVOKABLE double getFanAllTargetRpmPercent() const { return m_fanAllTargetRpmPercent; }
    Q_INVOKABLE void setFanAllTargetRpmPercent(double value)
    {
        m_fanAllTargetRpmPercent = value;
        emit fanAllTargetRpmPercentChanged(m_fanAllTargetRpmPercent);
    }
 // =========================
    // 系統 / 區塊開關
    // =========================
    Q_INVOKABLE bool getSystemRunning() const { return m_systemRunning; }
    Q_INVOKABLE void setSystemRunning(bool value)
    {
        m_systemRunning = value;
        emit systemRunningChanged(m_systemRunning);
    }

    Q_INVOKABLE bool getOutValvePidOn() const { return m_outValvePidOn; }
    Q_INVOKABLE void setOutValvePidOn(bool value)
    {
        m_outValvePidOn = value;
        emit outValvePidOnChanged(m_outValvePidOn);
    }
    Q_INVOKABLE bool getOutValveCorrectionOn() const { return m_outValveCorrectionOn; }
    Q_INVOKABLE void setOutValveCorrectionOn(bool value)
    {
        m_outValveCorrectionOn = value;
        emit outValveCorrectionOnChanged(m_outValveCorrectionOn);
    }

    Q_INVOKABLE bool getMotorFrequencySwitchOn() const { return m_motorFrequencySwitchOn; }
    Q_INVOKABLE void setMotorFrequencySwitchOn(bool value)
    {
        m_motorFrequencySwitchOn = value;
        emit motorFrequencySwitchOnChanged(m_motorFrequencySwitchOn);
    }

    Q_INVOKABLE bool getFanAllOn() const { return m_fanAllOn; }
    Q_INVOKABLE void setFanAllOn(bool value)
    {
        m_fanAllOn = value;
        emit fanAllOnChanged(m_fanAllOn);
    }

    Q_INVOKABLE bool getFanPidMonitorOn() const { return m_fanPidMonitorOn; }
    Q_INVOKABLE void setFanPidMonitorOn(bool value)
    {
        m_fanPidMonitorOn = value;
        emit fanPidMonitorOnChanged(m_fanPidMonitorOn);
    }

    // =========================
    // 風扇開關
    // =========================
    Q_INVOKABLE bool getFanCorrectionSwitchOn() const { return m_fanCorrectionSwitchOn; }
    Q_INVOKABLE void setFanCorrectionSwitchOn(bool value)
    {
        m_fanCorrectionSwitchOn = value;
        emit fanCorrectionSwitchOnChanged(m_fanCorrectionSwitchOn);
    }
    Q_INVOKABLE bool getFan1SwitchOn() const { return m_fan1SwitchOn; }
    Q_INVOKABLE void setFan1SwitchOn(bool value)
    {
        m_fan1SwitchOn = value;
        emit fan1SwitchOnChanged(m_fan1SwitchOn);
    }

    Q_INVOKABLE bool getFan2SwitchOn() const { return m_fan2SwitchOn; }
    Q_INVOKABLE void setFan2SwitchOn(bool value)
    {
        m_fan2SwitchOn = value;
        emit fan2SwitchOnChanged(m_fan2SwitchOn);
    }

    Q_INVOKABLE bool getFan3SwitchOn() const { return m_fan3SwitchOn; }
    Q_INVOKABLE void setFan3SwitchOn(bool value)
    {
        m_fan3SwitchOn = value;
        emit fan3SwitchOnChanged(m_fan3SwitchOn);
    }

    Q_INVOKABLE bool getFan4SwitchOn() const { return m_fan4SwitchOn; }
    Q_INVOKABLE void setFan4SwitchOn(bool value)
    {
        m_fan4SwitchOn = value;
        emit fan4SwitchOnChanged(m_fan4SwitchOn);
    }

    Q_INVOKABLE bool getFan5SwitchOn() const { return m_fan5SwitchOn; }
    Q_INVOKABLE void setFan5SwitchOn(bool value)
    {
        m_fan5SwitchOn = value;
        emit fan5SwitchOnChanged(m_fan5SwitchOn);
    }

    Q_INVOKABLE bool getFan6SwitchOn() const { return m_fan6SwitchOn; }
    Q_INVOKABLE void setFan6SwitchOn(bool value)
    {
        m_fan6SwitchOn = value;
        emit fan6SwitchOnChanged(m_fan6SwitchOn);
    }

    Q_INVOKABLE bool getFan7SwitchOn() const { return m_fan7SwitchOn; }
    Q_INVOKABLE void setFan7SwitchOn(bool value)
    {
        m_fan7SwitchOn = value;
        emit fan7SwitchOnChanged(m_fan7SwitchOn);
    }

    Q_INVOKABLE bool getFan8SwitchOn() const { return m_fan8SwitchOn; }
    Q_INVOKABLE void setFan8SwitchOn(bool value)
    {
        m_fan8SwitchOn = value;
        emit fan8SwitchOnChanged(m_fan8SwitchOn);
    }

    Q_INVOKABLE bool getFan9SwitchOn() const { return m_fan9SwitchOn; }
    Q_INVOKABLE void setFan9SwitchOn(bool value)
    {
        m_fan9SwitchOn = value;
        emit fan9SwitchOnChanged(m_fan9SwitchOn);
    }

    // =========================
    // 按鈕狀態
    // =========================
    Q_INVOKABLE bool getConfirmOutValveButton() const { return m_confirmOutValveButton; }
    Q_INVOKABLE void setConfirmOutValveButton(bool value)
    {
        m_confirmOutValveButton = value;
        emit confirmOutValveButtonChanged(m_confirmOutValveButton);
    }

    Q_INVOKABLE bool getConfirmReturnValveButton() const { return m_confirmReturnValveButton; }
    Q_INVOKABLE void setConfirmReturnValveButton(bool value)
    {
        m_confirmReturnValveButton = value;
        emit confirmReturnValveButtonChanged(m_confirmReturnValveButton);
    }

    Q_INVOKABLE bool getApplyMotorFrequencyButton() const { return m_applyMotorFrequencyButton; }
    Q_INVOKABLE void setApplyMotorFrequencyButton(bool value)
    {
        m_applyMotorFrequencyButton = value;
        emit applyMotorFrequencyButtonChanged(m_applyMotorFrequencyButton);
    }

    Q_INVOKABLE bool getApplyFanPidButton() const { return m_applyFanPidButton; }
    Q_INVOKABLE void setApplyFanPidButton(bool value)
    {
        m_applyFanPidButton = value;
        emit applyFanPidButtonChanged(m_applyFanPidButton);
    }

    Q_INVOKABLE bool getFan1ConfirmButton() const { return m_fan1ConfirmButton; }
    Q_INVOKABLE void setFan1ConfirmButton(bool value)
    {
        m_fan1ConfirmButton = value;
        emit fan1ConfirmButtonChanged(m_fan1ConfirmButton);
    }

    Q_INVOKABLE bool getFan2ConfirmButton() const { return m_fan2ConfirmButton; }
    Q_INVOKABLE void setFan2ConfirmButton(bool value)
    {
        m_fan2ConfirmButton = value;
        emit fan2ConfirmButtonChanged(m_fan2ConfirmButton);
    }

    Q_INVOKABLE bool getFan3ConfirmButton() const { return m_fan3ConfirmButton; }
    Q_INVOKABLE void setFan3ConfirmButton(bool value)
    {
        m_fan3ConfirmButton = value;
        emit fan3ConfirmButtonChanged(m_fan3ConfirmButton);
    }

    Q_INVOKABLE bool getFan4ConfirmButton() const { return m_fan4ConfirmButton; }
    Q_INVOKABLE void setFan4ConfirmButton(bool value)
    {
        m_fan4ConfirmButton = value;
        emit fan4ConfirmButtonChanged(m_fan4ConfirmButton);
    }

    Q_INVOKABLE bool getFan5ConfirmButton() const { return m_fan5ConfirmButton; }
    Q_INVOKABLE void setFan5ConfirmButton(bool value)
    {
        m_fan5ConfirmButton = value;
        emit fan5ConfirmButtonChanged(m_fan5ConfirmButton);
    }

    Q_INVOKABLE bool getFan6ConfirmButton() const { return m_fan6ConfirmButton; }
    Q_INVOKABLE void setFan6ConfirmButton(bool value)
    {
        m_fan6ConfirmButton = value;
        emit fan6ConfirmButtonChanged(m_fan6ConfirmButton);
    }

    Q_INVOKABLE bool getFan7ConfirmButton() const { return m_fan7ConfirmButton; }
    Q_INVOKABLE void setFan7ConfirmButton(bool value)
    {
        m_fan7ConfirmButton = value;
        emit fan7ConfirmButtonChanged(m_fan7ConfirmButton);
    }

    Q_INVOKABLE bool getFan8ConfirmButton() const { return m_fan8ConfirmButton; }
    Q_INVOKABLE void setFan8ConfirmButton(bool value)
    {
        m_fan8ConfirmButton = value;
        emit fan8ConfirmButtonChanged(m_fan8ConfirmButton);
    }

    Q_INVOKABLE bool getFan9ConfirmButton() const { return m_fan9ConfirmButton; }
    Q_INVOKABLE void setFan9ConfirmButton(bool value)
    {
        m_fan9ConfirmButton = value;
        emit fan9ConfirmButtonChanged(m_fan9ConfirmButton);
    }

    // =========================
    // IP地址
    // =========================
    Q_INVOKABLE QString getIpAddress() const { return m_ipAddress; }
    Q_INVOKABLE void setIpAddress(const QString &value)
    {
        m_ipAddress = value;
        emit ipAddressChanged(m_ipAddress);
    }
    // =========================
    // 子網遮罩
    // =========================
    Q_INVOKABLE QString getSubnetMask() const { return m_subnetMask; }
    Q_INVOKABLE void setSubnetMask(const QString &value)
    {
        m_subnetMask = value;
        emit subnetMaskChanged(m_subnetMask);
    }

    // =========================
    // 預設閘道
    // =========================
    Q_INVOKABLE QString getDefaultGateway() const { return m_defaultGateway; }
    Q_INVOKABLE void setDefaultGateway(const QString &value)
    {
        m_defaultGateway = value;
        emit defaultGatewayChanged(m_defaultGateway);
    }

    // =========================
    // DNS伺服器
    // =========================
    Q_INVOKABLE QString getDnsServer() const { return m_dnsServer; }
    Q_INVOKABLE void setDnsServer(const QString &value)
    {
        m_dnsServer = value;
        emit dnsServerChanged(m_dnsServer);
    }




    signals:
    void inWaterTempChanged(double value);
    void inWaterPressureChanged(double value);

    void outWaterTempChanged(double value);
    void outWaterPressureChanged(double value);

    void returnWaterTempChanged(double value);
    void returnWaterPressureChanged(double value);

    void condenserLeft1TempChanged(double value);
    void condenserRight1TempChanged(double value);
    void condenserLeft2TempChanged(double value);
    void condenserRight2TempChanged(double value);

    void inletAirTempChanged(double value);
    void inletAirHumidityChanged(double value);

    void outletAirTempChanged(double value);
    void outWaterTargetTempChanged(double value);
    void outWaterTargetTempPChanged(double value);

    void outValveOpeningChanged(double value);
    void outValvePChanged(double value);
    void outValveIChanged(double value);
    void outValveDChanged(double value);
    void outValveOpeningPChanged(double value);
    void outValvePPChanged(double value);
    void outValveIPChanged(double value);
    void outValveDPChanged(double value);

    void returnValveOpeningChanged(double value);
    void returnValveOpeningPChanged(double value);
    void returnValveValueChanged(double value);
    void returnValveValuePChanged(double value);

    void motorFrequencyChanged(double value);
    void motorFrequencyPChanged(double value);
    void currentWaterFlowChanged(double value);
    void heatExchangeChanged(double value);
    // void heatExchangePChanged(double value);

    void pressureDiffChanged(double value);
    void targetPressureDiffChanged(double value);
    void fanPidPChanged(double value);
    void fanPidIChanged(double value);
    void fanPidDChanged(double value);
    void fanPidPPChanged(double value);
    void fanPidIPChanged(double value);
    void fanPidDPChanged(double value);

    void fan1TargetRpmChanged(double value);
    void fan2TargetRpmChanged(double value);
    void fan3TargetRpmChanged(double value);
    void fan4TargetRpmChanged(double value);
    void fan5TargetRpmChanged(double value);
    void fan6TargetRpmChanged(double value);
    void fan7TargetRpmChanged(double value);
    void fan8TargetRpmChanged(double value);
    void fan9TargetRpmChanged(double value);
    void fanAllTargetRpmChanged(double value);

    void fan1TargetRpmPChanged(double value);
    void fan2TargetRpmPChanged(double value);
    void fan3TargetRpmPChanged(double value);
    void fan4TargetRpmPChanged(double value);
    void fan5TargetRpmPChanged(double value);
    void fan6TargetRpmPChanged(double value);
    void fan7TargetRpmPChanged(double value);
    void fan8TargetRpmPChanged(double value);
    void fan9TargetRpmPChanged(double value);
    void fanAllTargetRpmPChanged(double value);

    void fan1TargetRpmPercentChanged(double value);
    void fan2TargetRpmPercentChanged(double value);
    void fan3TargetRpmPercentChanged(double value);
    void fan4TargetRpmPercentChanged(double value);
    void fan5TargetRpmPercentChanged(double value);
    void fan6TargetRpmPercentChanged(double value);
    void fan7TargetRpmPercentChanged(double value);
    void fan8TargetRpmPercentChanged(double value);
    void fan9TargetRpmPercentChanged(double value);
    void fanAllTargetRpmPercentChanged(double value);

    void systemRunningChanged(bool value);
    void outValvePidOnChanged(bool value);
    void outValveCorrectionOnChanged(bool value);
    void motorFrequencySwitchOnChanged(bool value);
    void fanAllOnChanged(bool value);
    void fanPidMonitorOnChanged(bool value);

    void fanCorrectionSwitchOnChanged(bool value);
    void fan1SwitchOnChanged(bool value);
    void fan2SwitchOnChanged(bool value);
    void fan3SwitchOnChanged(bool value);
    void fan4SwitchOnChanged(bool value);
    void fan5SwitchOnChanged(bool value);
    void fan6SwitchOnChanged(bool value);
    void fan7SwitchOnChanged(bool value);
    void fan8SwitchOnChanged(bool value);
    void fan9SwitchOnChanged(bool value);

    void confirmOutValveButtonChanged(bool value);
    void confirmReturnValveButtonChanged(bool value);
    void applyMotorFrequencyButtonChanged(bool value);
    void applyFanPidButtonChanged(bool value);

    void fan1ConfirmButtonChanged(bool value);
    void fan2ConfirmButtonChanged(bool value);
    void fan3ConfirmButtonChanged(bool value);
    void fan4ConfirmButtonChanged(bool value);
    void fan5ConfirmButtonChanged(bool value);
    void fan6ConfirmButtonChanged(bool value);
    void fan7ConfirmButtonChanged(bool value);
    void fan8ConfirmButtonChanged(bool value);
    void fan9ConfirmButtonChanged(bool value);

    void ipAddressChanged(QString value);
    void subnetMaskChanged(QString value);
    void defaultGatewayChanged(QString value);
    void dnsServerChanged(QString value);
private:
    // =========================
    // 成員變數
    // =========================
    double m_inWaterTemp = 0;
    double m_inWaterPressure = 0;

    double m_outWaterTemp = 0;
    double m_outWaterPressure = 0;

    double m_returnWaterTemp = 0;
    double m_returnWaterPressure = 0;

    double m_condenserLeft1Temp = 0;
    double m_condenserRight1Temp = 0;
    double m_condenserLeft2Temp = 0;
    double m_condenserRight2Temp = 0;

    double m_inletAirTemp = 0;
    double m_inletAirHumidity = 0;

    double m_outletAirTemp = 0;
    double m_outWaterTargetTemp = 0;
    double m_outWaterTargetTempP = 0;

    double m_outValveOpening = 0;
    double m_outValveP = 0;
    double m_outValveI = 0;
    double m_outValveD = 0;
    double m_outValveOpeningP = 0;
    double m_outValvePP = 0;
    double m_outValveIP = 0;
    double m_outValveDP = 0;

    double m_returnValveOpening = 0;
    double m_returnValveOpeningP = 0;
    double m_returnValveValue = 0;
    double m_returnValveValueP = 0;

    double m_motorFrequency = 0;
    double m_motorFrequencyP = 0;
    double m_currentWaterFlow = 0;
    double m_heatExchange = 0;
    // double m_heatExchangeP = 0;

    double m_pressureDiff = 0;
    double m_targetPressureDiff = 0;
    double m_fanPidP = 0;
    double m_fanPidI = 0;
    double m_fanPidD = 0;
    double m_fanPidPP = 0;
    double m_fanPidIP = 0;
    double m_fanPidDP = 0;

    double m_fan1TargetRpm = 0;
    double m_fan2TargetRpm = 0;
    double m_fan3TargetRpm = 0;
    double m_fan4TargetRpm = 0;
    double m_fan5TargetRpm = 0;
    double m_fan6TargetRpm = 0;
    double m_fan7TargetRpm = 0;
    double m_fan8TargetRpm = 0;
    double m_fan9TargetRpm = 0;
    double m_fanAllTargetRpm = 0;

    double m_fan1TargetRpmP = 0;
    double m_fan2TargetRpmP = 0;
    double m_fan3TargetRpmP = 0;
    double m_fan4TargetRpmP = 0;
    double m_fan5TargetRpmP = 0;
    double m_fan6TargetRpmP = 0;
    double m_fan7TargetRpmP = 0;
    double m_fan8TargetRpmP = 0;
    double m_fan9TargetRpmP = 0;
    double m_fanAllTargetRpmP = 0;

    double m_fan1TargetRpmPercent = 0;
    double m_fan2TargetRpmPercent = 0;
    double m_fan3TargetRpmPercent = 0;
    double m_fan4TargetRpmPercent = 0;
    double m_fan5TargetRpmPercent = 0;
    double m_fan6TargetRpmPercent = 0;
    double m_fan7TargetRpmPercent = 0;
    double m_fan8TargetRpmPercent = 0;
    double m_fan9TargetRpmPercent = 0;
    double m_fanAllTargetRpmPercent = 0;

    // =========================
    // 成員變數
    // =========================
    bool m_systemRunning = false;
    bool m_outValvePidOn = false;
    bool m_outValveCorrectionOn = false;
    bool m_motorFrequencySwitchOn = false;
    bool m_fanAllOn = false;
    bool m_fanPidMonitorOn = false;

    bool m_fanCorrectionSwitchOn = false;
    bool m_fan1SwitchOn = false;
    bool m_fan2SwitchOn = false;
    bool m_fan3SwitchOn = false;
    bool m_fan4SwitchOn = false;
    bool m_fan5SwitchOn = false;
    bool m_fan6SwitchOn = false;
    bool m_fan7SwitchOn = false;
    bool m_fan8SwitchOn = false;
    bool m_fan9SwitchOn = false;

    bool m_confirmOutValveButton = false;
    bool m_confirmReturnValveButton = false;
    bool m_applyMotorFrequencyButton = false;
    bool m_applyFanPidButton = false;

    bool m_fan1ConfirmButton = false;
    bool m_fan2ConfirmButton = false;
    bool m_fan3ConfirmButton = false;
    bool m_fan4ConfirmButton = false;
    bool m_fan5ConfirmButton = false;
    bool m_fan6ConfirmButton = false;
    bool m_fan7ConfirmButton = false;
    bool m_fan8ConfirmButton = false;
    bool m_fan9ConfirmButton = false;

    QString m_ipAddress = "00.00.00.00";
    QString m_subnetMask = "00.00.00.00";
    QString m_defaultGateway = "0.0.0.0";
    QString m_dnsServer = "0.0.0.0";
};




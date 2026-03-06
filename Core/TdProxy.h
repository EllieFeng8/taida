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

    // =========================
    // 出水閥控制
    // =========================
    Q_PROPERTY(double outValveOpening READ getOutValveOpening WRITE setOutValveOpening NOTIFY outValveOpeningChanged)
    Q_PROPERTY(double outValveP READ getOutValveP WRITE setOutValveP NOTIFY outValvePChanged)
    Q_PROPERTY(double outValveI READ getOutValveI WRITE setOutValveI NOTIFY outValveIChanged)
    Q_PROPERTY(double outValveD READ getOutValveD WRITE setOutValveD NOTIFY outValveDChanged)

    // =========================
    // 回水閥控制
    // =========================
    Q_PROPERTY(double returnValveOpening READ getReturnValveOpening WRITE setReturnValveOpening NOTIFY returnValveOpeningChanged)

    // =========================
    // 馬達頻率控制
    // =========================
    Q_PROPERTY(double motorFrequency READ getMotorFrequency WRITE setMotorFrequency NOTIFY motorFrequencyChanged)
    Q_PROPERTY(double currentWaterFlow READ getCurrentWaterFlow WRITE setCurrentWaterFlow NOTIFY currentWaterFlowChanged)

    // =========================
    // 風扇控制 / 壓差 / PID
    // =========================
    Q_PROPERTY(double pressureDiff READ getPressureDiff WRITE setPressureDiff NOTIFY pressureDiffChanged)
    Q_PROPERTY(double fanPidP READ getFanPidP WRITE setFanPidP NOTIFY fanPidPChanged)
    Q_PROPERTY(double fanPidI READ getFanPidI WRITE setFanPidI NOTIFY fanPidIChanged)
    Q_PROPERTY(double fanPidD READ getFanPidD WRITE setFanPidD NOTIFY fanPidDChanged)

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

    // =========================
    // 系統 / 區塊開關
    // =========================
    Q_PROPERTY(bool systemRunning READ getSystemRunning WRITE setSystemRunning NOTIFY systemRunningChanged)
    Q_PROPERTY(bool outValvePidOn READ getOutValvePidOn WRITE setOutValvePidOn NOTIFY outValvePidOnChanged)
    Q_PROPERTY(bool motorFrequencySwitchOn READ getMotorFrequencySwitchOn WRITE setMotorFrequencySwitchOn NOTIFY motorFrequencySwitchOnChanged)
    Q_PROPERTY(bool fanAllOn READ getFanAllOn WRITE setFanAllOn NOTIFY fanAllOnChanged)
    Q_PROPERTY(bool fanPidMonitorOn READ getFanPidMonitorOn WRITE setFanPidMonitorOn NOTIFY fanPidMonitorOnChanged)

    // =========================
    // 風扇開關
    // =========================
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

    // =========================
    // 回水閥控制
    // =========================
    Q_INVOKABLE double getReturnValveOpening() const { return m_returnValveOpening; }
    Q_INVOKABLE void setReturnValveOpening(double value)
    {
        m_returnValveOpening = value;
        emit returnValveOpeningChanged(m_returnValveOpening);
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

    Q_INVOKABLE double getCurrentWaterFlow() const { return m_currentWaterFlow; }
    Q_INVOKABLE void setCurrentWaterFlow(double value)
    {
        m_currentWaterFlow = value;
        emit currentWaterFlowChanged(m_currentWaterFlow);
    }

    // =========================
    // 風扇控制 / 壓差 / PID
    // =========================
    Q_INVOKABLE double getPressureDiff() const { return m_pressureDiff; }
    Q_INVOKABLE void setPressureDiff(double value)
    {
        m_pressureDiff = value;
        emit pressureDiffChanged(m_pressureDiff);
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

    void outValveOpeningChanged(double value);
    void outValvePChanged(double value);
    void outValveIChanged(double value);
    void outValveDChanged(double value);

    void returnValveOpeningChanged(double value);

    void motorFrequencyChanged(double value);
    void currentWaterFlowChanged(double value);

    void pressureDiffChanged(double value);
    void fanPidPChanged(double value);
    void fanPidIChanged(double value);
    void fanPidDChanged(double value);

    void fan1TargetRpmChanged(double value);
    void fan2TargetRpmChanged(double value);
    void fan3TargetRpmChanged(double value);
    void fan4TargetRpmChanged(double value);
    void fan5TargetRpmChanged(double value);
    void fan6TargetRpmChanged(double value);
    void fan7TargetRpmChanged(double value);
    void fan8TargetRpmChanged(double value);
    void fan9TargetRpmChanged(double value);

    void systemRunningChanged(bool value);
    void outValvePidOnChanged(bool value);
    void motorFrequencySwitchOnChanged(bool value);
    void fanAllOnChanged(bool value);
    void fanPidMonitorOnChanged(bool value);

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
private:
    // =========================
    // 成員變數
    // =========================
    double m_inWaterTemp = 11.0;
    double m_inWaterPressure = 11.0;

    double m_outWaterTemp = 10.0;
    double m_outWaterPressure = 10.0;

    double m_returnWaterTemp = 10.0;
    double m_returnWaterPressure = 10.0;

    double m_condenserLeft1Temp = 10.0;
    double m_condenserRight1Temp = 10.0;
    double m_condenserLeft2Temp = 10.0;
    double m_condenserRight2Temp = 10.0;

    double m_inletAirTemp = 10.0;
    double m_inletAirHumidity = 10.0;

    double m_outletAirTemp = 10.0;

    double m_outValveOpening = 1.0;
    double m_outValveP = 1.5;
    double m_outValveI = 1.0;
    double m_outValveD = 0.2;

    double m_returnValveOpening = 45.0;

    double m_motorFrequency = 50.0;
    double m_currentWaterFlow = 111.0;

    double m_pressureDiff = 600.0;
    double m_fanPidP = 10.0;
    double m_fanPidI = 10.0;
    double m_fanPidD = 10.0;

    double m_fan1TargetRpm = 1800.0;
    double m_fan2TargetRpm = 1800.0;
    double m_fan3TargetRpm = 1800.0;
    double m_fan4TargetRpm = 1800.0;
    double m_fan5TargetRpm = 1800.0;
    double m_fan6TargetRpm = 1800.0;
    double m_fan7TargetRpm = 1800.0;
    double m_fan8TargetRpm = 1800.0;
    double m_fan9TargetRpm = 1800.0;

    // =========================
    // 成員變數
    // =========================
    bool m_systemRunning = true;
    bool m_outValvePidOn = true;
    bool m_motorFrequencySwitchOn = true;
    bool m_fanAllOn = true;
    bool m_fanPidMonitorOn = true;

    bool m_fan1SwitchOn = true;
    bool m_fan2SwitchOn = true;
    bool m_fan3SwitchOn = true;
    bool m_fan4SwitchOn = true;
    bool m_fan5SwitchOn = true;
    bool m_fan6SwitchOn = true;
    bool m_fan7SwitchOn = true;
    bool m_fan8SwitchOn = true;
    bool m_fan9SwitchOn = true;

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
};




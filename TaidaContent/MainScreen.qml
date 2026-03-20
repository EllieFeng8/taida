import QtQuick
import QtQuick.Controls
import Core 1.0


MainScreenUI {
    id: root
    returnValveBtnMouseArea.onClicked: {
        Td.returnValveOpening = returnValveTxtInput.text
        returnValveTxtInput.focus = false
        Td.returnValveValue = returnValveSetTxtInput.text
        returnValveSetTxtInput.focus = false
        console.log("回水:",Td.returnValveOpening,Td.returnValveValue)
    }

    motorFreqSetBtnMouseArea.onClicked: {
        Td.motorFrequency = motorFreqTextInput.text
        motorFreqTextInput.focus = false
        console.log("馬達:",Td.motorFrequency)
    }


    waterValveSwitchMouseArea.onClicked: {
        Td.outValvePidOn = !Td.outValvePidOn
    }
    waterValveSetMouseArea.onClicked: {
        Td.outValveOpening = waterValveOpenTxtInput.text
        Td.outValveP = waterPTxtInpt.text
        Td.outValveI = waterITxtInpt.text
        Td.outValveD = waterDTxtInpt.text
        waterValveOpenTxtInput.focus = false
        waterPTxtInpt.focus = false
        waterITxtInpt.focus = false
        waterDTxtInpt.focus = false
        console.log("出水閥:",Td.outValveOpening,Td.outValveP,Td.outValveI,Td.outValveD)
    }

    fansPIDSetBtnMouseArea.onClicked: {
        Td.fanPidP = fansPTxtInput.text
        Td.fanPidI = fansITxtInput.text
        Td.fanPidD = fansDTxtInput.text
        fansPTxtInput.focus = false
        fansITxtInput.focus = false
        fansDTxtInput.focus = false

    console.log("fans pid:",Td.fanPidP,Td.fanPidI,Td.fanPidD)
    }

    fans1SwitchMouseArea.onClicked: {
        Td.fan1SwitchOn = !Td.fan1SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    fans2SwitchMouseArea.onClicked: {
        Td.fan2SwitchOn = !Td.fan2SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    fans3SwitchMouseArea.onClicked: {
        Td.fan3SwitchOn = !Td.fan3SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    fans4SwitchMouseArea.onClicked: {
        Td.fan4SwitchOn = !Td.fan4SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    fans5SwitchMouseArea.onClicked: {
        Td.fan5SwitchOn = !Td.fan5SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    fans6SwitchMouseArea.onClicked: {
        Td.fan6SwitchOn = !Td.fan6SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    fans7SwitchMouseArea.onClicked: {
        Td.fan7SwitchOn = !Td.fan7SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    fans8SwitchMouseArea.onClicked: {
        Td.fan8SwitchOn = !Td.fan8SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    fans9SwitchMouseArea.onClicked: {
        Td.fan9SwitchOn = !Td.fan9SwitchOn
        if(Td.fanAllOn === true){
            Td.fanAllOn = false
        }
    }
    motorFreqSwitchMouseArea.onClicked: {
        Td.motorFrequencySwitchOn = !Td.motorFrequencySwitchOn
    }
    allFansPIDSwitchMouseArea.onClicked: {
        Td.fanPidMonitorOn = !Td.fanPidMonitorOn
    console.log("Td.fanPidMonitorOn",Td.fanPidMonitorOn)
    }

    allFansSwitchMouseArea.onClicked: {
        Td.fanAllOn = !Td.fanAllOn
    if(Td.fanAllOn === false){
        Td.fan1SwitchOn = false
        Td.fan2SwitchOn = false
        Td.fan3SwitchOn = false
        Td.fan4SwitchOn = false
        Td.fan5SwitchOn = false
        Td.fan6SwitchOn = false
        Td.fan7SwitchOn = false
        Td.fan8SwitchOn = false
        Td.fan9SwitchOn = false
    }else{
        Td.fan1SwitchOn = true
        Td.fan2SwitchOn = true
        Td.fan3SwitchOn = true
        Td.fan4SwitchOn = true
        Td.fan5SwitchOn = true
        Td.fan6SwitchOn = true
        Td.fan7SwitchOn = true
        Td.fan8SwitchOn = true
        Td.fan9SwitchOn = true
    }

    }
    //風扇inputchange
    fans1btnMouseArea.onClicked: {
        if(fans1SetTextInput.text>100 || fans1SetTextInput.text<0) {
            fans1SetTextInput.color = "red"
        }
        else{
            Td.fan1TargetRpm = fans1SetTextInput.text
            fans1SetTextInput.color = "#1e293b"
            Td.fan1TargetRpm = fans1SetTextInput.text
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan1SwitchOn === false){
                Td.fan1SwitchOn = true
            }
            // console.log("11 Td.fan1TargetRpm changed~~~",
            //     Td.fan1TargetRpm,
            //     typeof (Td.fan1TargetRpm));
        }
        fans1SetTextInput.focus = false
    }
    fans2btnMouseArea.onClicked: {
        if(fans2SetTextInput.text>100 || fans2SetTextInput.text<0) {
            fans2SetTextInput.color = "red"
        }
        else{
            Td.fan2TargetRpm = fans2SetTextInput.text
            fans2SetTextInput.color = "#1e293b"
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan2SwitchOn === false){
                Td.fan2SwitchOn = true
            }
            // console.log("11 Td.fan2TargetRpm changed~~~",
            // Td.fan2TargetRpm,
            // typeof (Td.fan2TargetRpm));
        }
        fans2SetTextInput.focus = false
    }
    fans3btnMouseArea.onClicked: {
        if(fans3SetTextInput.text>100 || fans3SetTextInput.text<0) {
            fans3SetTextInput.color = "red"
        }
        else{
            Td.fan3TargetRpm = fans3SetTextInput.text
            fans3SetTextInput.color = "#1e293b"
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan3SwitchOn === false){
                Td.fan3SwitchOn = true
            }
            // console.log("11 Td.fan3TargetRpm changed~~~",
            //     Td.fan3TargetRpm,
            //     typeof (Td.fan3TargetRpm));
        }
        fans3SetTextInput.focus = false
    }
    fans4btnMouseArea.onClicked: {
        if(fans4SetTextInput.text>100 || fans4SetTextInput.text<0) {
            fans4SetTextInput.color = "red"
        }
        else{
            Td.fan4TargetRpm = fans4SetTextInput.text
            fans4SetTextInput.color = "#1e293b"
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan4SwitchOn === false){
                Td.fan4SwitchOn = true
            }
            // console.log("11 Td.fan4TargetRpm changed~~~",
            //     Td.fan4TargetRpm,
            //     typeof (Td.fan4TargetRpm));
        }
        fans4SetTextInput.focus = false
    }
    fans5btnMouseArea.onClicked: {
        if(fans5SetTextInput.text>100 || fans5SetTextInput.text<0) {
            fans5SetTextInput.color = "red"
        }
        else{
            Td.fan5TargetRpm = fans5SetTextInput.text
            fans5SetTextInput.color = "#1e293b"
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan5SwitchOn === false){
                Td.fan5SwitchOn = true
            }
            // console.log("11 Td.fan5TargetRpm changed~~~",
            //     Td.fan5TargetRpm,
            //     typeof (Td.fan5TargetRpm));
        }
        fans5SetTextInput.focus = false
    }
    fans6btnMouseArea.onClicked: {
        if(fans6SetTextInput.text>100 || fans6SetTextInput.text<0) {
            fans6SetTextInput.color = "red"
        }
        else{
            Td.fan6TargetRpm = fans6SetTextInput.text
            fans6SetTextInput.color = "#1e293b"
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan6SwitchOn === false){
                Td.fan6SwitchOn = true
            }
            // console.log("11 Td.fan6TargetRpm changed~~~",
            //     Td.fan6TargetRpm,
            //     typeof (Td.fan6TargetRpm));
        }
        fans6SetTextInput.focus = false
    }
    fans7btnMouseArea.onClicked: {
        if(fans7SetTextInput.text>100 || fans7SetTextInput.text<0) {
            fans7SetTextInput.color = "red"
        }
        else{
            Td.fan7TargetRpm = fans7SetTextInput.text
            fans7SetTextInput.color = "#1e293b"
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan7SwitchOn === false){
                Td.fan7SwitchOn = true
            }
            // console.log("11 Td.fan7TargetRpm changed~~~",
            //     Td.fan7TargetRpm,
            //     typeof (Td.fan7TargetRpm));
        }
        fans7SetTextInput.focus = false
    }
    fans8btnMouseArea.onClicked: {
        if(fans8SetTextInput.text>100 || fans8SetTextInput.text<0) {
            fans8SetTextInput.color = "red"
        }
        else{
            Td.fan8TargetRpm = fans8SetTextInput.text
            fans8SetTextInput.color = "#1e293b"
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan8SwitchOn === false){
                Td.fan8SwitchOn = true
            }
            // console.log("11 Td.fan8TargetRpm changed~~~",
            //     Td.fan8TargetRpm,
            //     typeof (Td.fan8TargetRpm));
        }
        fans8SetTextInput.focus = false
    }
    fans9btnMouseArea.onClicked: {
        if(fans9SetTextInput.text>100 || fans9SetTextInput.text<0) {
            fans9SetTextInput.color = "red"
        }
        else{
            Td.fan9TargetRpm = fans9SetTextInput.text
            fans9SetTextInput.color = "#1e293b"
            if(Td.fanAllOn === true){
                Td.fanAllOn = false
            }
            if(Td.fan9SwitchOn === false){
                Td.fan9SwitchOn = true
            }
            // console.log("11 Td.fan9TargetRpm changed~~~",
            //     Td.fan9TargetRpm,
            //     typeof (Td.fan9TargetRpm));
        }
        fans9SetTextInput.focus = false
    }
    fansallbtnMouseArea.onClicked: {
        if(fansallSetTextInput.text>100 || fansallSetTextInput.text<0) {
            fansallSetTextInput.color = "red"
        }
        else{
            Td.fanAllTargetRpm = fansallSetTextInput.text
            Td.fan1TargetRpm = fansallSetTextInput.text
            Td.fan2TargetRpm = fansallSetTextInput.text
            Td.fan3TargetRpm = fansallSetTextInput.text
            Td.fan4TargetRpm = fansallSetTextInput.text
            Td.fan5TargetRpm = fansallSetTextInput.text
            Td.fan6TargetRpm = fansallSetTextInput.text
            Td.fan7TargetRpm = fansallSetTextInput.text
            Td.fan8TargetRpm = fansallSetTextInput.text
            Td.fan9TargetRpm = fansallSetTextInput.text
            if(Td.fanAllOn === false){
                Td.fanAllOn = true
                Td.fan1SwitchOn = true
                Td.fan2SwitchOn = true
                Td.fan3SwitchOn = true
                Td.fan4SwitchOn = true
                Td.fan5SwitchOn = true
                Td.fan6SwitchOn = true
                Td.fan7SwitchOn = true
                Td.fan8SwitchOn = true
                Td.fan9SwitchOn = true
            }
            fansallSetTextInput.color = "#1e293b"
            console.log("11 Td.fanAllTargetRpm changed~~~",
                Td.fanAllTargetRpm,
                typeof (Td.fanAllTargetRpm));
        }
        fansallSetTextInput.focus = false
    }
    setBtnMouseArea.onClicked: {
        Td.hitSettingBtn();
        connectSet.visible = true
    }

    correctionSwitchMouseArea.onClicked: {
        Td.outValveCorrectionOn = !Td.outValveCorrectionOn
        console.log("Td.outValveCorrectionOn",Td.outValveCorrectionOn)
    }

    correction2SwitchMouseArea.onClicked: {
        Td.fanCorrectionSwitchOn = !Td.fanCorrectionSwitchOn
        console.log("Td.fanCorrectionSwitchOn",Td.fanCorrectionSwitchOn)
    }
    outWaterTargetTempBtnMouseArea.onClicked: {
        if(outWaterTargetTempTxtInput.text>0) {
            Td.outWaterTargetTemp = outWaterTargetTempTxtInput.text
            console.log("11 Td.outWaterTargetTempTxtInput changed~~~",
                Td.outWaterTargetTemp,
                typeof (Td.outWaterTargetTemp));
        }
        outWaterTargetTempTxtInput.focus = false
    }

    targetPressBtnMouseArea.onClicked: {
        if(targetPressTxtInput.text>0) {
            Td.targetPressureDiff = targetPressTxtInput.text
            console.log("11 Td.targetPressureDiff changed~~~",
                Td.targetPressureDiff,
                typeof (Td.targetPressureDiff));
        }
        targetPressTxtInput.focus = false
    }

    ConnectionSettings{
        id:connectSet
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }


}

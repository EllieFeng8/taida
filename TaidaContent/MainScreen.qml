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
        waterValveIsOn = !waterValveIsOn
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
        fans1IsOn = !fans1IsOn

    }
    fans2SwitchMouseArea.onClicked: {
        fans2IsOn = !fans2IsOn
    }
    fans3SwitchMouseArea.onClicked: {
        fans3IsOn = !fans3IsOn
    }
    fans4SwitchMouseArea.onClicked: {
        fans4IsOn = !fans4IsOn
    }
    fans5SwitchMouseArea.onClicked: {
        fans5IsOn = !fans5IsOn
    }
    fans6SwitchMouseArea.onClicked: {
        fans6IsOn = !fans6IsOn
    }
    fans7SwitchMouseArea.onClicked: {
        fans7IsOn = !fans7IsOn
    }
    fans8SwitchMouseArea.onClicked: {
        fans8IsOn = !fans8IsOn
    }
    fans9SwitchMouseArea.onClicked: {
        fans9IsOn = !fans9IsOn
    }
    motorFreqSwitchMouseArea.onClicked: {
        motorFreqIsOn = !motorFreqIsOn
    }
    allFansPIDSwitchMouseArea.onClicked: {
        fansPIDIsOn = !fansPIDIsOn
    console.log("fansPIDIsOn",fansPIDIsOn)
    }

    allFansSwitchMouseArea.onClicked: {
        allFansIsOn = !allFansIsOn
    }
    //風扇inputchange
    fans1btnMouseArea.onClicked: {
        if(fans1SetTextInput.text>0) {
            Td.fan1TargetRpm = fans1SetTextInput.text
            console.log("11 Td.fan1TargetRpm changed~~~",
                Td.fan1TargetRpm,
                typeof (Td.fan1TargetRpm));
        }
        fans1SetTextInput.focus = false
    }
    fans2btnMouseArea.onClicked: {
        if(fans2SetTextInput.text>0) {
            Td.fan2TargetRpm = fans2SetTextInput.text
            console.log("11 Td.fan2TargetRpm changed~~~",
                Td.fan2TargetRpm,
                typeof (Td.fan2TargetRpm));
        }
        fans2SetTextInput.focus = false
    }
    fans3btnMouseArea.onClicked: {
        if(fans3SetTextInput.text>0) {
            Td.fan3TargetRpm = fans3SetTextInput.text
            console.log("11 Td.fan3TargetRpm changed~~~",
                Td.fan3TargetRpm,
                typeof (Td.fan3TargetRpm));
        }
        fans3SetTextInput.focus = false
    }
    fans4btnMouseArea.onClicked: {
        if(fans4SetTextInput.text>0) {
            Td.fan4TargetRpm = fans4SetTextInput.text
            console.log("11 Td.fan4TargetRpm changed~~~",
                Td.fan4TargetRpm,
                typeof (Td.fan4TargetRpm));
        }
        fans4SetTextInput.focus = false
    }
    fans5btnMouseArea.onClicked: {
        if(fans5SetTextInput.text>0) {
            Td.fan5TargetRpm = fans5SetTextInput.text
            console.log("11 Td.fan5TargetRpm changed~~~",
                Td.fan5TargetRpm,
                typeof (Td.fan5TargetRpm));
        }
        fans5SetTextInput.focus = false
    }
    fans6btnMouseArea.onClicked: {
        if(fans6SetTextInput.text>0) {
            Td.fan6TargetRpm = fans6SetTextInput.text
            console.log("11 Td.fan6TargetRpm changed~~~",
                Td.fan6TargetRpm,
                typeof (Td.fan6TargetRpm));
        }
        fans6SetTextInput.focus = false
    }
    fans7btnMouseArea.onClicked: {
        if(fans7SetTextInput.text>0) {
            Td.fan7TargetRpm = fans7SetTextInput.text
            console.log("11 Td.fan7TargetRpm changed~~~",
                Td.fan7TargetRpm,
                typeof (Td.fan7TargetRpm));
        }
        fans7SetTextInput.focus = false
    }
    fans8btnMouseArea.onClicked: {
        if(fans8SetTextInput.text>0) {
            Td.fan8TargetRpm = fans8SetTextInput.text
            console.log("11 Td.fan8TargetRpm changed~~~",
                Td.fan8TargetRpm,
                typeof (Td.fan8TargetRpm));
        }
        fans8SetTextInput.focus = false
    }
    fans9btnMouseArea.onClicked: {
        if(fans9SetTextInput.text>0) {
            Td.fan9TargetRpm = fans9SetTextInput.text
            console.log("11 Td.fan9TargetRpm changed~~~",
                Td.fan9TargetRpm,
                typeof (Td.fan9TargetRpm));
        }
        fans9SetTextInput.focus = false
    }
    fansallbtnMouseArea.onClicked: {
        if(fansallSetTextInput.text>0) {
            Td.fanAllTargetRpm = fansallSetTextInput.text
            console.log("11 Td.fanAllTargetRpm changed~~~",
                Td.fanAllTargetRpm,
                typeof (Td.fanAllTargetRpm));
        }
        fansallSetTextInput.focus = false
    }
    setBtnMouseArea.onClicked: {
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
    outWaterTempBtnMouseArea.onClicked: {
        if(outWaterTempTxtInput.text>0) {
            Td.outWaterTemp = outWaterTempTxtInput.text
            console.log("11 Td.outWaterTempTxtInput changed~~~",
                Td.outWaterTemp,
                typeof (Td.outWaterTemp));
        }
        outWaterTempTxtInput.focus = false
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

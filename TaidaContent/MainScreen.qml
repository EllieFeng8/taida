import QtQuick
import QtQuick.Controls
import Core 1.0


MainScreenUI {
    id: root
    returnValveBtnMouseArea.onClicked: {
        Td.returnValveOpening = returnValveTxtInput.text
    console.log("回水:",Td.returnValveOpening)
    }

    motorFreqSetBtnMouseArea.onClicked: {
        Td.motorFrequency = motorFreqTextInput.text
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

        console.log("出水閥:",Td.outValveOpening,Td.outValveP,Td.outValveI,Td.outValveD)
    }

    fansPIDSetBtnMouseArea.onClicked: {
        Td.fanPidP = fansPTxtInput.text
        Td.fanPidI = fansITxtInput.text
        Td.fanPidD = fansDTxtInput.text
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
        background_fan1.border.color= "#e2e8f0"
    }
    fans2btnMouseArea.onClicked: {
        if(fans2SetTextInput.text>0) {
            Td.fan2TargetRpm = fans2SetTextInput.text
            console.log("11 Td.fan2TargetRpm changed~~~",
                Td.fan2TargetRpm,
                typeof (Td.fan2TargetRpm));
        }
    }
    fans3btnMouseArea.onClicked: {
        if(fans3SetTextInput.text>0) {
            Td.fan3TargetRpm = fans3SetTextInput.text
            console.log("11 Td.fan3TargetRpm changed~~~",
                Td.fan3TargetRpm,
                typeof (Td.fan3TargetRpm));
        }
    }
    fans4btnMouseArea.onClicked: {
        if(fans4SetTextInput.text>0) {
            Td.fan4TargetRpm = fans4SetTextInput.text
            console.log("11 Td.fan4TargetRpm changed~~~",
                Td.fan4TargetRpm,
                typeof (Td.fan4TargetRpm));
        }
    }
    fans5btnMouseArea.onClicked: {
        if(fans5SetTextInput.text>0) {
            Td.fan5TargetRpm = fans5SetTextInput.text
            console.log("11 Td.fan5TargetRpm changed~~~",
                Td.fan5TargetRpm,
                typeof (Td.fan5TargetRpm));
        }
    }
    fans6btnMouseArea.onClicked: {
        if(fans6SetTextInput.text>0) {
            Td.fan6TargetRpm = fans6SetTextInput.text
            console.log("11 Td.fan6TargetRpm changed~~~",
                Td.fan6TargetRpm,
                typeof (Td.fan6TargetRpm));
        }
    }
    fans7btnMouseArea.onClicked: {
        if(fans7SetTextInput.text>0) {
            Td.fan7TargetRpm = fans7SetTextInput.text
            console.log("11 Td.fan7TargetRpm changed~~~",
                Td.fan7TargetRpm,
                typeof (Td.fan7TargetRpm));
        }
    }
    fans8btnMouseArea.onClicked: {
        if(fans8SetTextInput.text>0) {
            Td.fan8TargetRpm = fans8SetTextInput.text
            console.log("11 Td.fan8TargetRpm changed~~~",
                Td.fan8TargetRpm,
                typeof (Td.fan8TargetRpm));
        }
    }
    fans9btnMouseArea.onClicked: {
        if(fans9SetTextInput.text>0) {
            Td.fan9TargetRpm = fans9SetTextInput.text
            console.log("11 Td.fan9TargetRpm changed~~~",
                Td.fan9TargetRpm,
                typeof (Td.fan9TargetRpm));
        }
    }

}

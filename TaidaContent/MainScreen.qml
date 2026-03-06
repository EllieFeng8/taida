import QtQuick
import QtQuick.Controls

MainScreenUI {
    id: root

    waterValveSwitchMouseArea.onClicked: {
        waterValveIsOn = !waterValveIsOn
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
    }

    allFansSwitchMouseArea.onClicked: {
        allFansIsOn = !allFansIsOn
    }

}

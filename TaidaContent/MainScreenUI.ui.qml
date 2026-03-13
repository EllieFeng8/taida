import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import Core 1.0

Rectangle {
    id: body

    height: 1024
    width: 1920

    color: "#f0f4f8"
    property alias _text_14 : _text_14
    property alias fansallSetTextInput : fansallSetTextInput
    property alias fansallbtnMouseArea:fansallbtnMouseArea
    property alias targetPressBtnMouseArea : targetPressBtnMouseArea
    property alias outWaterTempBtnMouseArea : outWaterTempBtnMouseArea
    property alias outWaterTempTxtInput : outWaterTempTxtInput
    property alias correctionSwitchMouseArea: correctionSwitchMouseArea
    property alias correction2SwitchMouseArea: correction2SwitchMouseArea
    property alias targetPressTxtInput: targetPressTxtInput

    property alias motorFreqSetBtnMouseArea:motorFreqSetBtnMouseArea
    property alias setBtnMouseArea: setBtnMouseArea
    property alias motorFreqSwitchMouseArea: motorFreqSwitchMouseArea
    property alias allFansPIDSwitchMouseArea: allFansPIDSwitchMouseArea
    property alias allFansSwitchMouseArea: allFansSwitchMouseArea
    property alias fansPIDSetBtnMouseArea: fansPIDSetBtnMouseArea
    property alias fansDTxtInput: fansDTxtInput
    property alias fansITxtInput: fansITxtInput
    property alias fansPTxtInput: fansPTxtInput
    property alias motorFreqTextInput: motorFreqTextInput
    property alias waterDTxtInpt: waterDTxtInpt
    property alias returnValveBtnMouseArea: returnValveBtnMouseArea
    property alias fans9btnMouseArea: fans9btnMouseArea
    property alias fans8btnMouseArea: fans8btnMouseArea
    property alias fans7btnMouseArea: fans7btnMouseArea
    property alias fans6btnMouseArea: fans6btnMouseArea
    property alias fans5btnMouseArea: fans5btnMouseArea
    property alias fans4btnMouseArea: fans4btnMouseArea
    property alias fans3btnMouseArea: fans3btnMouseArea
    property alias fans2btnMouseArea: fans2btnMouseArea
    property alias fans1btnMouseArea: fans1btnMouseArea
    property alias fans9SwitchMouseArea: fans9SwitchMouseArea
    property alias fans8SwitchMouseArea: fans8SwitchMouseArea
    property alias fans7SwitchMouseArea: fans7SwitchMouseArea
    property alias fans6SwitchMouseArea: fans6SwitchMouseArea
    property alias fans5SwitchMouseArea: fans5SwitchMouseArea
    property alias fans4SwitchMouseArea: fans4SwitchMouseArea
    property alias fans3SwitchMouseArea: fans3SwitchMouseArea
    property alias fans2SwitchMouseArea: fans2SwitchMouseArea
    property alias fans1SwitchMouseArea: fans1SwitchMouseArea
    property alias fans9SetTextInput: fans9SetTextInput
    property alias fans8SetTextInput: fans8SetTextInput
    property alias fans7SetTextInput: fans7SetTextInput
    property alias fans6SetTextInput: fans6SetTextInput
    property alias fans5SetTextInput: fans5SetTextInput
    property alias fans4SetTextInput: fans4SetTextInput
    property alias fans3SetTextInput: fans3SetTextInput
    property alias fans2SetTextInput: fans2SetTextInput
    property alias fans1SetTextInput: fans1SetTextInput
    // property alias returnValveSetTxtInput: returnValveSetTxtInput
    property alias returnValveTxtInput: returnValveTxtInput
    property alias waterPTxtInpt: waterPTxtInpt
    property alias waterITxtInpt: waterITxtInpt
    property alias waterValveOpenTxtInput: waterValveOpenTxtInput
    property alias waterValveSetMouseArea: waterValveSetMouseArea
    property alias waterValveSwitch: waterValveSwitch
    property alias waterValveSwitchMouseArea: waterValveSwitchMouseArea
    property bool waterValveIsOn: Td.outValvePidOn
    property bool waterValveSetBtn: true
    property bool motorFreqIsOn: Td.motorFrequencySwitchOn
    property bool allFansIsOn: Td.fanAllOn
    property bool fansPIDIsOn: Td.fanPidMonitorOn
    property bool fans1IsOn: Td.fan1SwitchOn
    property bool fans2IsOn: Td.fan2SwitchOn
    property bool fans3IsOn: Td.fan3SwitchOn
    property bool fans4IsOn: Td.fan4SwitchOn
    property bool fans5IsOn: Td.fan5SwitchOn
    property bool fans6IsOn: Td.fan6SwitchOn
    property bool fans7IsOn: Td.fan7SwitchOn
    property bool fans8IsOn: Td.fan8SwitchOn
    property bool fans9IsOn: Td.fan9SwitchOn

    property alias background_fan1 : background_fan1
    property alias background_fan2 : background_fan2
    property alias background_fan3 : background_fan3
    property alias background_fan4 : background_fan4
    property alias background_fan5 : background_fan5
    property alias background_fan6 : background_fan6
    property alias background_fan7 : background_fan7
    property alias background_fan8 : background_fan8
    property alias background_fan9 : background_fan9

    property bool correctionIsOn: Td.outValveCorrectionOn
    property bool correction2IsOn: Td.fanCorrectionSwitchOn

    Rectangle {
        id: background

        height: 1024
        width: 1920

        color: "#f0f4f8"

        Image {
            id: nav

            source: Qt.resolvedUrl("assets/nav.png")

            Item {
                id: _margin

                x: 28.23
                y: 24

                height: 55.13
                width: 22.54
            }
            Item {
                id: container

                x: 20.50
                y: 79.13

                height: 864.87
                width: 38

                Rectangle {
                    id: button

                    height: 38
                    width: 38

                    color: "#1a3b82f6"
                    radius: 12

                    Image {
                        source: "assets/Button.png"
                    }
                }
            }

            // Item {
            //     id: button_margin

            //     // x: 19.45
            //     y: 944
            Rectangle {
                id: setDeco
                width: 40
                height: 40

                y: 929
                color: setBtnMouseArea.containsMouse ? "#dae7fe" : "#00ffffff"
                radius: 12
                anchors.horizontalCenter: parent.horizontalCenter

                Image {
                    id: setting
                    scale: 1.4
                    anchors.left: setDeco.left
                    anchors.leftMargin: 10
                    anchors.top: setDeco.top
                    anchors.topMargin: 10
                    // y: 949
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "assets/Container.png"
                    fillMode: Image.PreserveAspectFit
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: setBtnMouseArea.containsMouse ? true : false
                        shadowColor: "#ecf3ff"
                        shadowBlur: 0.8
                    }

                    MouseArea {
                        id: setBtnMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
            // }
        }
        Item {
            id: main

            x: 80

            height: 1024
            width: 1840

            clip: true

            Item {
                id: header

                x: 24
                y: 24

                height: 50
                width: 1792

                Item {
                    id: container_3

                    height: 50
                    width: 144.02

                    Item {
                        id: heading_1

                        height: 32
                        width: 144.02

                        Text {
                            id: element

                            height: 32
                            width: 216.40

                            color: "#1e293b"
                            font.family: "Noto Sans TC"
                            font.letterSpacing: -0.60
                            font.pixelSize: 32
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 32
                            lineHeightMode: Text.FixedHeight
                            text: "數據顯示系統 "
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: container_4

                        y: 34

                        height: 16
                        width: 144.02

                        Text {
                            id: _text

                            height: 16
                            width: 145.02


                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 12
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "即時監控工業冷卻系統狀態"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
                Image {
                    id: background_Border_Shadow

                    x: 1475.82
                    y: 3

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow.png")

                    Rectangle {
                        id: background_1

                        x: 21
                        y: 16

                        height: 10
                        width: 10

                        color: "#22c55e"
                        radius: 9999
                    }
                    Item {
                        id: container_5

                        x: 47
                        y: 13

                        height: 16
                        width: 72.02

                        Text {
                            id: element_1

                            height: 16
                            width: 73.02

                            color: "#1e293b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 12
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "系統運行正常"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: container_6

                        x: 135.02
                        y: 9

                        height: 24
                        width: 5.33

                        Text {
                            id: _text_1

                            height: 24
                            width: 6.33

                            color: "#cbd5e1"
                            font.family: "Inter"
                            font.pixelSize: 16
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 24
                            lineHeightMode: Text.FixedHeight
                            text: "|"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: container_7

                        x: 156.35
                        y: 13

                        height: 16
                        width: 136.83

                        Text {
                            id: _text_2

                            height: 16
                            width: 137.83

                            color: "#1e293b"
                            font.family: "Liberation Mono"
                            font.pixelSize: 12
                            font.weight: Font.Medium
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "2026-03-05 07:56:43"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
            Item {
                id: section

                x: 24
                y: 98

                height: 140
                width: 1792

                Image {
                    id: background_Border_Shadow_1

                    x: -2
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_1.png")

                    Item {
                        id: frame_1

                        x: 17
                        y: 17

                        height: 20
                        width: 136
                        Image {
                            y: 5
                            scale: 1.3
                            source: "assets/Icon.png"
                        }

                        Text {
                            id: element_2

                            x: 25

                            height: 20
                            width: 116

                            color: "#3b82f6"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 24
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 20
                            lineHeightMode: Text.FixedHeight
                            text: "入水數據"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: frame_2

                        x: 17
                        y: 49

                        height: 28
                        width: 208

                        Text {
                            id: element_3

                            y: 6

                            height: 16
                            width: 55

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "溫度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Item {
                            id: paragraph

                            x: 169.39

                            height: 28
                            width: 38.61

                            Text {
                                id: _text_3
                                x: -38
                                y: 0

                                height: 28
                                width: 66

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignRight
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.inWaterTemp
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: _text_4

                                x: 26.86

                                height: 28
                                width: 12.75

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "°C"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                    Item {
                        id: frame_3

                        x: 17
                        y: 89

                        height: 31
                        width: 208

                        Text {
                            id: element_4

                            y: 7.50

                            height: 16
                            width: 47

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "壓力"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Item {
                            id: paragraph_1

                            x: 169.30

                            height: 31
                            width: 38.70

                            Text {
                                id: _text_5
                                x: -48
                                y: 0

                                height: 28
                                width: 76

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignRight
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.inWaterPressure
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: _text_6

                                x: 26.86
                                y: 3

                                height: 28
                                width: 12.84

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "pa"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
                Image {
                    id: background_Border_Shadow_2

                    x: 271.20
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_2.png")

                    Item {
                        id: frame_4

                        x: 17
                        y: 17

                        height: 20
                        width: 155
                        Image {
                            y: 5
                            scale: 1.3
                            source: "assets/Icon1.png"
                        }

                        Text {
                            id: element_5

                            x: 25

                            height: 20
                            width: 133

                            color: "#f97316"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 24
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 20
                            lineHeightMode: Text.FixedHeight
                            text: "出水數據"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: frame_5

                        x: 17
                        y: 49

                        height: 31
                        width: 209

                        Text {
                            id: element_6

                            y: 7.50

                            height: 16
                            width: 53

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "溫度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Item {
                            id: paragraph_2

                            x: 170.39

                            height: 31
                            width: 38.61

                            Text {
                                id: _text_7
                                x: -40
                                y: 0

                                height: 28
                                width: 68

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignRight
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.outWaterTemp
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: _text_8

                                x: 26.86
                                y: 3

                                height: 28
                                width: 12.75

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "°C"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                    Item {
                        id: frame_6

                        x: 17
                        y: 92

                        height: 31
                        width: 209

                        Text {
                            id: element_7

                            y: 7.50

                            height: 16
                            width: 44

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "壓力"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Item {
                            id: paragraph_3

                            x: 170.30

                            height: 31
                            width: 38.70

                            Text {
                                id: _text_9
                                x: -40
                                y: 0

                                height: 28
                                width: 67

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignRight
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.returnWaterPressure
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: _text_10

                                x: 26.86
                                y: 3

                                height: 28
                                width: 12.84

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "pa"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
                Image {
                    id: background_Border_Shadow_3

                    x: 544.39
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_3.png")

                    Item {
                        id: frame_7

                        x: 17
                        y: 17

                        height: 20
                        width: 148
                        Image {
                            y: 5
                            scale: 1.3
                            source: "assets/Icon2.png"
                        }

                        Text {
                            id: element_8

                            x: 25

                            height: 20
                            width: 123

                            color: "#6366f1"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 24
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 20
                            lineHeightMode: Text.FixedHeight
                            text: "回水數據"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: container_8

                        x: 17
                        y: 49

                        height: 31
                        width: 208.28

                        Text {
                            id: element_9

                            y: 7.50

                            height: 16
                            width: 57

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "溫度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Item {
                            id: paragraph_4

                            x: 169.67

                            height: 31
                            width: 38.61

                            Text {
                                id: element_10
                                x: -29
                                y: 0

                                height: 28
                                width: 57

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignRight
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.returnWaterTemp
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: c

                                x: 26.86
                                y: 3

                                height: 28
                                width: 12.75

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "°C"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                    Item {
                        id: container_9

                        x: 17
                        y: 92

                        height: 31
                        width: 208.28

                        Text {
                            id: element_11

                            y: 7.50

                            height: 16
                            width: 52

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "壓力"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Item {
                            id: paragraph_5

                            x: 169.58

                            height: 31
                            width: 38.70

                            Text {
                                id: _text_11
                                x: -21
                                y: 0

                                height: 28
                                width: 49

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignRight
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.returnWaterPressure
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: _text_12

                                x: 26.86
                                y: 3

                                height: 28
                                width: 12.84

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "pa"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
                Image {
                    id: background_Border_Shadow_4

                    x: 817.59
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_4.png")

                    Item {
                        id: container_10

                        x: 17
                        y: 17

                        height: 20
                        width: 181
                        Image {
                            y: 5
                            scale: 1.3
                            source: "assets/Icon3.png"
                        }

                        Text {
                            id: element_12
                            x: 25
                            height: 20
                            width: 182

                            color: "#10b981"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 24
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 20
                            lineHeightMode: Text.FixedHeight
                            text: "冷排溫度監控"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: frame_8

                        x: 17
                        y: 53

                        height: 70
                        width: 393

                        Item {
                            id: frame_9

                            height: 70
                            width: 203

                            Image {
                                id: horizontalBorder

                                source: Qt.resolvedUrl(
                                            "assets/horizontalBorder.png")

                                Text {
                                    id: element_13

                                    y: 2.50

                                    height: 15
                                    width: 80.50

                                    color: "#64748b"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.letterSpacing: 0.50
                                    font.pixelSize: 20
                                    font.weight: Font.Normal
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "左1"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {

                                    height: 28
                                    width: 27.86
                                    x: 106.28
                                    color: "#1e293b"
                                    font.family: "Inter"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: Td.condenserLeft1Temp
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {

                                    x: 133
                                    y: 3

                                    height: 28
                                    width: 12.75

                                    color: "#94a3b8"
                                    font.family: "Inter"
                                    font.pixelSize: 10
                                    font.weight: Font.Normal
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: "°C"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                // }
                            }
                            Image {
                                id: horizontalBorder_1

                                y: 45

                                source: Qt.resolvedUrl(
                                            "assets/horizontalBorder_1.png")

                                Text {
                                    id: element_14

                                    y: 2.50

                                    height: 15
                                    width: 84.50

                                    color: "#64748b"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.letterSpacing: 0.50
                                    font.pixelSize: 20
                                    font.weight: Font.Normal
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "左2"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }

                                Text {

                                    height: 28
                                    width: 27.86
                                    x: 106.28
                                    color: "#1e293b"
                                    font.family: "Inter"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: Td.condenserLeft2Temp
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {

                                    x: 133
                                    y: 3

                                    height: 28
                                    width: 12.75

                                    color: "#94a3b8"
                                    font.family: "Inter"
                                    font.pixelSize: 10
                                    font.weight: Font.Normal
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: "°C"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                // }
                            }
                        }
                        Item {
                            id: frame_10

                            x: 203

                            height: 70
                            width: 173

                            Image {
                                id: horizontalBorder_2

                                source: Qt.resolvedUrl(
                                            "assets/horizontalBorder_2.png")

                                Text {
                                    id: element_15

                                    y: 2.50

                                    height: 15
                                    width: 81.50

                                    color: "#64748b"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.letterSpacing: 0.50
                                    font.pixelSize: 20
                                    font.weight: Font.Normal
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "右1"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }

                                Text {

                                    height: 28
                                    width: 27.86
                                    x: 106.28
                                    color: "#1e293b"
                                    font.family: "Inter"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: Td.condenserRight1Temp
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {

                                    x: 133
                                    y: 3

                                    height: 28
                                    width: 12.75

                                    color: "#94a3b8"
                                    font.family: "Inter"
                                    font.pixelSize: 10
                                    font.weight: Font.Normal
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: "°C"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            Image {
                                id: horizontalBorder_3

                                y: 45

                                source: Qt.resolvedUrl(
                                            "assets/horizontalBorder_3.png")

                                Text {
                                    id: element_16

                                    y: 2.50

                                    height: 15
                                    width: 83.50

                                    color: "#64748b"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.letterSpacing: 0.50
                                    font.pixelSize: 20
                                    font.weight: Font.Normal
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "右2"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {

                                    height: 28
                                    width: 27.86
                                    x: 106.28
                                    color: "#1e293b"
                                    font.family: "Inter"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: Td.condenserRight1Temp
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {

                                    x: 133
                                    y: 3

                                    height: 28
                                    width: 12.75

                                    color: "#94a3b8"
                                    font.family: "Inter"
                                    font.pixelSize: 10
                                    font.weight: Font.Normal
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: "°C"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }
                    }
                }
                Image {
                    id: background_Border_Shadow_5

                    x: 1274.50
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_5.png")

                    Item {
                        id: frame_11

                        x: 17
                        y: 17

                        height: 20
                        width: 210
                        Image {
                            y: 5
                            scale: 1.3
                            source: "assets/Icon4.png"
                        }

                        Text {
                            id: element_17

                            x: 25

                            height: 20
                            width: 183

                            color: "#0ea5e9"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 24
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 20
                            lineHeightMode: Text.FixedHeight
                            text: "入風溫濕度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: frame_12

                        x: 17
                        y: 49

                        height: 31
                        width: 209

                        Text {
                            id: element_18

                            y: 7.50

                            height: 16
                            width: 87

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "溫度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Item {
                            id: paragraph_6

                            x: 158.39

                            height: 31
                            width: 38.61

                            Text {
                                id: element_19

                                height: 28
                                width: 27.86

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.inletAirTemp
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: _text_13

                                x: 26.86
                                y: 3

                                height: 28
                                width: 12.75

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "°C"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                    Item {
                        id: frame_13

                        x: 17
                        y: 92

                        height: 31
                        width: 209

                        Text {
                            id: element_20

                            y: 7.50

                            height: 16
                            width: 47

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "濕度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignTop
                            wrapMode: Text.WordWrap
                        }
                        Item {
                            id: paragraph_7

                            x: 158.45

                            height: 31
                            width: 50.55

                            Text {
                                id: element_21

                                height: 28
                                width: 27.86

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.inletAirHumidity
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: rH

                                x: 26.86
                                y: 3

                                height: 28
                                width: 24.69

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "%RH"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
                Image {
                    id: background_Border_Shadow_6

                    x: 1547.72
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_6.png")

                    Item {
                        id: frame_14

                        x: 17
                        y: 17

                        height: 20
                        width: 183
                        Image {
                            y: 5
                            scale: 1.3
                            source: "assets/Icon4.png"
                        }

                        Text {
                            id: element_22

                            x: 25

                            height: 20
                            width: 157

                            color: "#06b6d4"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 24
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 20
                            lineHeightMode: Text.FixedHeight
                            text: "出風溫度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: frame_15

                        x: 17
                        y: 49

                        height: 31
                        width: 209

                        Text {
                            id: element_23

                            y: 7.50

                            height: 16
                            width: 59

                            color: "#64748b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "溫度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Item {
                            id: paragraph_8

                            x: 170.39

                            height: 31
                            width: 38.61

                            Text {
                                id: element_24

                                height: 28
                                width: 27.86

                                color: "#1e293b"
                                font.family: "Inter"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: Td.outletAirTemp
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                id: c_5

                                x: 26.86
                                y: 3

                                height: 28
                                width: 12.75

                                color: "#94a3b8"
                                font.family: "Inter"
                                font.pixelSize: 10
                                font.weight: Font.Normal
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 28
                                lineHeightMode: Text.FixedHeight
                                text: "°C"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                    Rectangle {
                        id: background_Border111
                        x: 17
                        anchors.top: frame_15.bottom
                        anchors.topMargin: 10
                        height: 38
                        width: 156

                        border.width: outWaterTempTxtInput.focus ? 3 : 1
                        border.color: outWaterTempTxtInput.focus ? "#2563eb" : "#e2e8f0"
                        color: "#f1f5f9"
                        radius: 8

                        Text {
                            id: element_261

                            x: 5
                            y: 11.50

                            height: 15
                            width: 44

                            color: "#94a3b8"
                            font.capitalization: Font.AllUppercase
                            font.family: "Noto Sans TC"
                            font.pixelSize: 16
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 15
                            lineHeightMode: Text.FixedHeight
                            text: "目標溫度"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        TextInput {
                            id: outWaterTempTxtInput
                            x: 92
                            y: 0

                            height: 38
                            width: 48

                            color: "#1e293b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 20
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignRight

                            text: Number(Td.outWaterTemp)
                            verticalAlignment: Text.AlignVCenter
                            validator: DoubleValidator {}
                        }
                        Text {

                            id: c_51
                            anchors.left: outWaterTempTxtInput.right
                            y: 8

                            height: 28
                            width: 12.75

                            color: "#94a3b8"
                            font.family: "Inter"
                            font.pixelSize: 10
                            font.weight: Font.Normal
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 28
                            lineHeightMode: Text.FixedHeight
                            text: "°C"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }

                        Rectangle {
                            id: button_47

                            anchors.left: c_51.right
                            anchors.leftMargin: 15

                            height: 38
                            width: 46

                            color: "#2563eb"
                            radius: 8
                            scale: outWaterTempBtnMouseArea.containsMouse ? 1.02 : 1

                            Text {
                                id: element_41

                                color: "#ffffff"
                                font.family: "Noto Sans TC"
                                font.pixelSize: 16
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignHCenter
                                lineHeight: 16
                                lineHeightMode: Text.FixedHeight
                                text: "OK"
                                anchors.fill: parent
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            layer.enabled: true
                            layer.effect: MultiEffect {
                                shadowEnabled: outWaterTempBtnMouseArea.containsMouse ? true : false
                                shadowColor: "#1d4ed8"
                                shadowBlur: 0.8
                            }
                            MouseArea {
                                id: outWaterTempBtnMouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                            }
                        }
                    }
                }
            }
            Item {
                id: section_1

                x: 24
                y: 262

                height: 260
                width: 1792

                Image {
                    id: background_Border_Shadow_7

                    x: -2
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_7.png")

                    Item {
                        id: frame_16

                        x: 21
                        y: 21

                        height: 24
                        width: 539

                        Item {
                            id: frame_17

                            height: 24
                            width: 166
                            Image {
                                scale: 1.1
                                y: 5
                                source: "assets/Icon6.png"
                            }

                            Text {
                                id: element_25

                                x: 27

                                height: 24
                                width: 137

                                color: "#1e293b"
                                font.family: "Noto Sans TC"
                                font.pixelSize: 24
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 24
                                lineHeightMode: Text.FixedHeight
                                text: "出水閥控制"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        Item {
                            id: correction

                            x: 309.95
                            y: 2

                            height: 20
                            width: 89.05

                            Image {
                                id: correctionSwitch

                                height: 20
                                width: 40
                                scale: correctionSwitchMouseArea.containsMouse ? 1.2 : 1
                                source: correctionIsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: correctionSwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: correctionSwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                            Item {
                                id: _margin_0

                                x: 40
                                y: 0

                                height: 16
                                width: 49.05

                                Text {
                                    id: _text_15

                                    x: 4

                                    height: 16
                                    width: 37.05

                                    color: "red"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 18
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 16
                                    lineHeightMode: Text.FixedHeight
                                    text: correctionIsOn ? "正向" : "反向"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {
                                    id: _text_16

                                    anchors.left: _text_15.right

                                    height: 16
                                    width: 22.05

                                    color: "#2563eb"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 18
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 16
                                    lineHeightMode: Text.FixedHeight
                                    text: "修正"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }

                        Item {
                            id: label

                            x: 449.95
                            y: 2

                            height: 20
                            width: 89.05

                            Image {
                                id: waterValveSwitch

                                height: 20
                                width: 40
                                scale: waterValveSwitchMouseArea.containsMouse ? 1.2 : 1
                                source: waterValveIsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: waterValveSwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: waterValveSwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                            Item {
                                id: _margin_1

                                x: 40
                                y: 2

                                height: 16
                                width: 49.05

                                Text {
                                    id: _text_14

                                    x: 8

                                    height: 16
                                    width: 42.05

                                    color: "#2563eb"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 12
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 16
                                    lineHeightMode: Text.FixedHeight
                                    text: waterValveIsOn ? "PID ON" : "PID OFF"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }
                    }
                    Item {
                        id: frame_18

                        x: 21
                        y: 80

                        height: 88
                        width: 520

                        Item {
                            id: frame_19

                            height: 88
                            width: 237

                            Rectangle {
                                id: background_Border

                                height: 38
                                width: 237

                                border.width: waterValveOpenTxtInput.focus ? 3 : 1
                                border.color: waterValveOpenTxtInput.focus ? "#2563eb" : "#e2e8f0"
                                color: "#f1f5f9"
                                radius: 8
                                RowLayout {
                                    anchors.fill: parent
                                    Layout.fillWidth: true
                                    spacing: 8

                                Text {
                                    id: element_26

                                        // height: 15
                                        Layout.leftMargin: 10
                                        Layout.preferredWidth: 44
                                    color: "#94a3b8"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "開度"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "PV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: Td.outValveOpeningP
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Rectangle {
                                        Layout.preferredWidth: 1
                                        Layout.preferredHeight: 20
                                        color: "#94a3b8"
                                        opacity: 0.5
                                        Layout.leftMargin: 5
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        Layout.preferredWidth: 44
                                        Layout.leftMargin: 10
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "SV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                TextInput {
                                    id: waterValveOpenTxtInput
                                        // x: 92
                                        // y: 0

                                        // height: 38
                                        Layout.leftMargin: -200
                                        Layout.preferredWidth: parent.width

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight

                                    text: Number(Td.outValveOpening)
                                    verticalAlignment: Text.AlignVCenter
                                    validator: DoubleValidator {}
                                    }
                                }
                            }
                            Rectangle {
                                id: background_Border_1

                                y: 50

                                height: 38
                                width: 237

                                border.width: waterPTxtInpt.focus ? 3 : 1
                                border.color: waterPTxtInpt.focus ? "#2563eb" : "#e2e8f0"
                                color: "#f1f5f9"
                                radius: 8
                                RowLayout {
                                    anchors.fill: parent
                                    Layout.fillWidth: true
                                    spacing: 8

                                    Text {
                                        // id: element_26

                                        // height: 15
                                        Layout.leftMargin: 10
                                        Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "D"
                                        textFormat: Text.PlainText
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "PV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: Td.outValvePP
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Rectangle {
                                        Layout.preferredWidth: 1
                                        Layout.preferredHeight: 20
                                        color: "#94a3b8"
                                        opacity: 0.5
                                        Layout.leftMargin: 5
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        Layout.preferredWidth: 44
                                        Layout.leftMargin: 10
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "SV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                TextInput {
                                    id: waterPTxtInpt

                                        Layout.leftMargin: -200
                                        Layout.preferredWidth: parent.width

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight
                                    validator: DoubleValidator {}
                                    text: Number(Td.outValveP)
                                    verticalAlignment: Text.AlignVCenter
                                    }
                                }
                            }
                        }
                        Item {
                            id: frame_20

                            x: 277

                            height: 88
                            width: 237

                            Rectangle {
                                id: background_Border_2

                                height: 38
                                width: 237

                                // border.color: "#e2e8f0"
                                // border.width: 1
                                color: "#f1f5f9"
                                radius: 8

                                border.width: waterITxtInpt.focus ? 3 : 1
                                border.color: waterITxtInpt.focus ? "#2563eb" : "#e2e8f0"

                                RowLayout {
                                    anchors.fill: parent
                                    Layout.fillWidth: true
                                    spacing: 8

                                    Text {
                                        // id: element_26

                                        // height: 15
                                        Layout.leftMargin: 10
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "I"
                                        textFormat: Text.PlainText
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "PV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: Td.outValveIP
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Rectangle {
                                        Layout.preferredWidth: 1
                                        Layout.preferredHeight: 20
                                        color: "#94a3b8"
                                        opacity: 0.5
                                        Layout.leftMargin: 5
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        Layout.preferredWidth: 44
                                        Layout.leftMargin: 10
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "SV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                TextInput {
                                    id: waterITxtInpt

                                        Layout.leftMargin: -200
                                        Layout.preferredWidth: parent.width

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight
                                    selectByMouse: true
                                    validator: DoubleValidator {}
                                     text: Number(Td.outValveI)
                                    verticalAlignment: Text.AlignVCenter
                                    }
                                }
                            }
                            Rectangle {
                                id: background_Border_3

                                y: 50

                                height: 38
                                width: 237

                                border.width: waterDTxtInpt.focus ? 3 : 1
                                border.color: waterDTxtInpt.focus ? "#2563eb" : "#e2e8f0"
                                color: "#f1f5f9"
                                radius: 8
                                RowLayout {
                                    anchors.fill: parent
                                    Layout.fillWidth: true
                                    spacing: 8

                                    Text {
                                        // id: element_26

                                        // height: 15
                                        Layout.leftMargin: 10
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "D"
                                        textFormat: Text.PlainText
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "PV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: Td.outValveDP
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Rectangle {
                                        Layout.preferredWidth: 1
                                        Layout.preferredHeight: 20
                                        color: "#94a3b8"
                                        opacity: 0.5
                                        Layout.leftMargin: 10
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        Layout.preferredWidth: 44
                                        Layout.leftMargin: 10
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "SV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }

                                    TextInput {
                                        id: waterDTxtInpt
                                        Layout.leftMargin: -200
                                        Layout.preferredWidth: parent.width


                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight
                                    validator: DoubleValidator {}
                                    text: Number(Td.outValveD)
                                    verticalAlignment: Text.AlignVCenter
                                    }
                                }
                            }
                        }
                    }
                    Rectangle {
                        id: waterValveSet

                        x: 21
                        y: 203

                        height: 36
                        width: 539.33

                        color: "#2563eb"
                        radius: 8
                        scale: waterValveSetMouseArea.containsMouse ? 1.02 : 1

                        Text {
                            id: element_31

                            x: 218.67
                            y: 10

                            height: 16
                            width: 103

                            color: "#ffffff"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 16
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignHCenter
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "確認出水設置"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: waterValveSetMouseArea.containsMouse ? true : false
                            shadowColor: "#1d4ed8"
                            shadowBlur: 0.8
                        }
                        MouseArea {
                            id: waterValveSetMouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }
                Image {
                    id: background_Border_Shadow_8

                    x: 603.33
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_8.png")

                    Item {
                        id: heading_3

                        x: 21
                        y: 21

                        height: 24
                        width: 163

                        Image {
                            id: container_15

                            y: 3.27

                            source: "assets/Container6.png"
                        }
                        Text {
                            id: element_32

                            x: 22.96

                            height: 24
                            width: 141

                            color: "#1e293b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 24
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 24
                            lineHeightMode: Text.FixedHeight
                            text: "回水閥控制"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Item {
                        id: container_16

                        x: 21
                        y: 65.50

                        height: 113
                        width: 539.33

                        Rectangle {
                            id: background_Border_4

                            height: 44
                            width: 539.33

                            border.width: returnValveTxtInput.focus ? 3 : 1
                            border.color: returnValveTxtInput.focus ? "#2563eb" : "#e2e8f0"
                            color: "#f1f5f9"
                            radius: 8
                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8

                                Text {
                                    // id: element_26

                                    // height: 15
                                    Layout.leftMargin: 10
                                    // Layout.preferredWidth: 60
                                    color: "#94a3b8"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "開度"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {

                                    // id: element_26
                                    // height: 15
                                    Layout.leftMargin: 50
                                    color: "#94a3b8"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 12
                                    font.weight: Font.Medium
                                    // horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "PV"
                                    textFormat: Text.PlainText
                                    // verticalAlignment: Text.AlignVCenter
                                }
                                Text {

                                    // id: element_26
                                    // height: 15
                                    // Layout.preferredWidth: 44
                                    color: "#94a3b8"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Medium
                                    Layout.leftMargin: 20
                                    // horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: Td.returnValveOpeningP
                                    textFormat: Text.PlainText
                                    // verticalAlignment: Text.AlignVCenter
                                }
                                Rectangle {
                                    Layout.preferredWidth: 1
                                    Layout.preferredHeight: 20
                                    color: "#94a3b8"
                                    opacity: 0.5
                                    Layout.leftMargin: 60
                                }
                                Text {

                                    // id: element_26
                                    // height: 15
                                    Layout.preferredWidth: 44
                                    Layout.leftMargin: 50
                                    color: "#94a3b8"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 12
                                    font.weight: Font.Medium
                                    // horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "SV"
                                    textFormat: Text.PlainText
                                    // verticalAlignment: Text.AlignVCenter
                                }
                            TextInput {
                                id: returnValveTxtInput

                                    Layout.leftMargin: -400
                                    Layout.preferredWidth: parent.width
                                font.pixelSize: 20
                                color: "black"
                                font.family: "Noto Sans TC"
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignRight
                                validator: DoubleValidator {}
				verticalAlignment: Text.AlignVCenter
                                text: Number(Td.returnValveOpening)
                                }
                            }
                        }
                        //
                        // Rectangle {
                        //     id: background_Border_5
                        //
                        //     y: 64
                        //
                        //     height: 49
                        //     width: 539.33
                        //
                        //     border.width: returnValveTxtInput.focus ? 3 : 1
                        //     border.color: returnValveSetTxtInput.focus ? "#2563eb" : "#e2e8f0"
                        //     color: "#f1f5f9"
                        //     radius: 8
                        //
                        //     RowLayout {
                        //         anchors.fill: parent
                        //         Layout.fillWidth: true
                        //         spacing: 8
                        //
                        //         Text {
                        //             // id: element_26
                        //
                        //             // height: 15
                        //             Layout.leftMargin: 10
                        //             // Layout.preferredWidth: 60
                        //             color: "#94a3b8"
                        //             font.capitalization: Font.AllUppercase
                        //             font.family: "Noto Sans TC"
                        //             font.pixelSize: 20
                        //             font.weight: Font.Bold
                        //             horizontalAlignment: Text.AlignLeft
                        //             lineHeight: 15
                        //             lineHeightMode: Text.FixedHeight
                        //             text: "設定數值"
                        //             textFormat: Text.PlainText
                        //             verticalAlignment: Text.AlignVCenter
                        //         }
                        //         Text {
                        //
                        //             // id: element_26
                        //             // height: 15
                        //             Layout.leftMargin: 10
                        //             color: "#94a3b8"
                        //             font.capitalization: Font.AllUppercase
                        //             font.family: "Noto Sans TC"
                        //             font.pixelSize: 12
                        //             font.weight: Font.Medium
                        //             // horizontalAlignment: Text.AlignLeft
                        //             lineHeight: 15
                        //             lineHeightMode: Text.FixedHeight
                        //             text: "PV"
                        //             textFormat: Text.PlainText
                        //             // verticalAlignment: Text.AlignVCenter
                        //         }
                        //         Text {
                        //
                        //             // id: element_26
                        //             // height: 15
                        //             // Layout.preferredWidth: 44
                        //             color: "#94a3b8"
                        //             font.capitalization: Font.AllUppercase
                        //             font.family: "Noto Sans TC"
                        //             font.pixelSize: 20
                        //             font.weight: Font.Medium
                        //             Layout.leftMargin: 20
                        //             // horizontalAlignment: Text.AlignLeft
                        //             lineHeight: 15
                        //             lineHeightMode: Text.FixedHeight
                        //             text: "45"
                        //             textFormat: Text.PlainText
                        //             // verticalAlignment: Text.AlignVCenter
                        //         }
                        //         Rectangle {
                        //             Layout.preferredWidth: 1
                        //             Layout.preferredHeight: 20
                        //             color: "#94a3b8"
                        //             opacity: 0.5
                        //             Layout.leftMargin: 60
                        //         }
                        //         Text {
                        //
                        //             // id: element_26
                        //             // height: 15
                        //             Layout.preferredWidth: 44
                        //             Layout.leftMargin: 50
                        //             color: "#94a3b8"
                        //             font.capitalization: Font.AllUppercase
                        //             font.family: "Noto Sans TC"
                        //             font.pixelSize: 12
                        //             font.weight: Font.Medium
                        //             // horizontalAlignment: Text.AlignLeft
                        //             lineHeight: 15
                        //             lineHeightMode: Text.FixedHeight
                        //             text: "SV"
                        //             textFormat: Text.PlainText
                        //             // verticalAlignment: Text.AlignVCenter
                        //         }
                        //
                        //         TextInput {
                        //             id: returnValveSetTxtInput
                        //
                        //             Layout.leftMargin: -400
                        //             Layout.preferredWidth: parent.width
                        //
                        //             color: "#1e293b"
                        //             font.family: "Noto Sans TC"
                        //             font.pixelSize: 20
                        //             font.weight: Font.Bold
                        //             horizontalAlignment: Text.AlignRight
                        //
                        //             text: "45"
                        //             verticalAlignment: Text.AlignVCenter
                        //         }
                        //     }
                        // }
                    }
                    Rectangle {
                        id: button_3

                        x: 21
                        y: 199

                        height: 40
                        width: 539.33

                        border.color: "#2563eb"
                        border.width: 2
                        color: "#2563eb"
                        radius: 8
                        scale: returnValveBtnMouseArea.containsMouse ? 1.02 : 1

                        Text {
                            id: element_37

                            x: 210.67
                            y: 12

                            height: 16
                            width: 119

                            color: "#ffffff"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 16
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignHCenter
                            lineHeight: 16
                            lineHeightMode: Text.FixedHeight
                            text: "確認回水參數"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: returnValveBtnMouseArea.containsMouse ? true : false
                            shadowColor: "#1d4ed8"
                            shadowBlur: 0.8
                        }
                        MouseArea {
                            id: returnValveBtnMouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }
                Image {
                    id: background_Border_Shadow_9

                    x: 1208.67
                    y: -1

                    source: Qt.resolvedUrl(
                                "assets/background_Border_Shadow_9.png")

                    Item {
                        id: container_18

                        x: 21
                        y: 21

                        height: 24
                        width: 539.33

                        Item {
                            id: heading_4

                            height: 24
                            width: 149
                            Image {
                                //id: name
                                scale: 1.2
                                y: 7
                                source: "assets/Icon7.png"
                            }

                            Text {
                                id: element_38

                                height: 24
                                width: 150
                                x: 25
                                color: "#1e293b"
                                font.family: "Noto Sans TC"
                                font.pixelSize: 24
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 24
                                lineHeightMode: Text.FixedHeight
                                text: "混水泵浦控制"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                        }

                        Image {
                            id: motorFreqSwitch
                            x: 499.32
                            y: 2

                            height: 20
                            width: 40
                            scale: motorFreqSwitchMouseArea.containsMouse ? 1.2 : 1
                            source: motorFreqIsOn ? "assets/switchon.png" : "assets/switchoff.png"
                            layer.enabled: true
                            layer.effect: MultiEffect {
                                shadowEnabled: motorFreqSwitchMouseArea.containsMouse ? true : false
                                shadowColor: "#1d4ed8"
                                shadowBlur: 0.8
                            }
                            MouseArea {
                                id: motorFreqSwitchMouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                            }
                        }
                    }
                    Item {
                        id: frame_21

                        x: 21
                        y: 60

                        height: 116
                        width: 539.33

                        clip: true

                        Item {
                            id: container_19

                            height: 52.16
                            width: 539.33

                            Rectangle {
                                id: background_Border_6

                                y: 7.08

                                height: 38
                                width: 461.33

                                border.width: motorFreqTextInput.focus ? 3 : 1
                                border.color: motorFreqTextInput.focus ? "#2563eb" : "#e2e8f0"
                                color: "#f1f5f9"
                                radius: 8
                                RowLayout {
                                    anchors.fill: parent
                                    Layout.fillWidth: true
                                    spacing: 8
                                    clip: true
                                Text {
                                    id: element_39

                                        Layout.leftMargin: 10

                                    color: "#94a3b8"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "頻率"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        Layout.leftMargin: 50
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "PV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        // Layout.preferredWidth: 44
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Medium
                                        Layout.leftMargin: 0
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: Td.motorFrequencyP
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    Rectangle {
                                        Layout.preferredWidth: 1
                                        Layout.preferredHeight: 20
                                        color: "#94a3b8"
                                        opacity: 0.5
                                        Layout.leftMargin: 50
                                    }
                                    Text {

                                        // id: element_26
                                        // height: 15
                                        Layout.preferredWidth: 44
                                        Layout.leftMargin: 30
                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                        // horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "SV"
                                        textFormat: Text.PlainText
                                        // verticalAlignment: Text.AlignVCenter
                                    }
                                    TextInput {
                                        id: motorFreqTextInput
                                        Layout.leftMargin: -400
                                        Layout.preferredWidth: parent.width
                                        color: "#1e293b"
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignRight

                                        text: Number(Td.motorFrequency)
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {

                                        // id: hz
                                        Layout.leftMargin: -20
                                        color: "#94a3b8"
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 10
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                        text: "Hz"
                                        textFormat: Text.PlainText
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                            }
                            Rectangle {
                                id: button_4

                                x: 473.33
                                y: 7.08

                                height: 38
                                width: 66

                                color: "#2563eb"
                                radius: 8
                                scale: motorFreqSetBtnMouseArea.containsMouse ? 1.02 : 1

                                Text {
                                    // id: element_41

                                    x: 16
                                    y: 11

                                    height: 16
                                    width: 35

                                    color: "#ffffff"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 16
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignHCenter
                                    lineHeight: 16
                                    lineHeightMode: Text.FixedHeight
                                    text: "套用"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: motorFreqSetBtnMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: motorFreqSetBtnMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Rectangle {
                            id: background_Border_7

                            y: 62.46

                            height: 53.54
                            width: 539.33

                            border.color: "#dbeafe"
                            border.width: 1
                            color: "#eff6ff"
                            radius: 12

                            Text {
                                id: element_42

                                x: 17
                                y: 19.27

                                height: 15
                                width: 122.50

                                color: "#2563eb"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 0.50
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                text: "當前水流量"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Item {
                                id: paragraph_9

                                x: 442.33
                                y: 8.77

                                height: 36
                                width: 80

                                Text {
                                    id: element_43
                                    x: -27
                                    y: 0

                                    height: 36
                                    width: 70

                                    color: "#3b82f6"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight
                                    lineHeight: 36
                                    lineHeightMode: Text.FixedHeight
                                    text: Td.currentWaterFlow
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {
                                    id: l_min

                                    x: 46
                                    y: 10

                                    height: 16
                                    width: 36

                                    color: "#3b82f6"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 10
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 16
                                    lineHeightMode: Text.FixedHeight
                                    text: "l/min"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignBottom
                                    wrapMode: Text.WordWrap
                                }
                            }
                        }
                    }
                }
            }
            Image {
                id: section_2

                x: 22
                y: 545

                clip: true
                source: Qt.resolvedUrl("assets/section.png")

                Image {
                    id: horizontalBorder_4

                    x: 21
                    y: 21

                    source: Qt.resolvedUrl("assets/horizontalBorder_4.png")

                    Item {
                        id: group_1

                        y: 7

                        height: 24
                        width: 652

                        // Item {
                        //     id: container_20

                        //     x: 249
                        //     y: 2

                        //     height: 20
                        //     width: 403

                        // Item {
                        //     id: label_1

                        //     height: 20
                        //     width: 174

                        //     Text {
                        //         id: element_44

                        //         y: 2

                        //         height: 16
                        //         width: 123

                        //         color: "#1e293b"
                        //         font.family: "Noto Sans TC"
                        //         font.pixelSize: 20
                        //         font.weight: Font.Bold
                        //         horizontalAlignment: Text.AlignLeft
                        //         lineHeight: 16
                        //         lineHeightMode: Text.FixedHeight
                        //         text: "一鍵開啟全部"
                        //         textFormat: Text.PlainText
                        //         verticalAlignment: Text.AlignVCenter
                        //     }
                        //     Item {
                        //         id: container_css_transform

                        //         x: 135.99

                        //         height: 20
                        //         width: 36

                        //         // Image {
                        //         //     id: allFansSwitch
                        //         //     y: 1
                        //         //     height: 20
                        //         //     width: 40
                        //         //     scale: allFansSwitchMouseArea.containsMouse ? 1.2 : 1
                        //         //     source: allFansIsOn ? "assets/switchon.png" : "assets/switchoff.png"
                        //         //     layer.enabled: true
                        //         //     layer.effect: MultiEffect {
                        //         //         shadowEnabled: allFansSwitchMouseArea.containsMouse ? true : false
                        //         //         shadowColor: "#1d4ed8"
                        //         //         shadowBlur: 0.8
                        //         //     }
                        //         //     MouseArea {
                        //         //         id: allFansSwitchMouseArea
                        //         //         anchors.fill: parent
                        //         //         hoverEnabled: true
                        //         //         cursorShape: Qt.PointingHandCursor
                        //         //     }
                        //         // }
                        //     }
                        // }
                        Item {
                            id: label_2

                            x: 149

                            height: 20
                            width: 174

                            Item {
                                id: correction2

                                // x: 309.95
                                // y: 2
                                height: 20
                                width: 89.05

                                Image {
                                    id: correction2Switch

                                    height: 20
                                    width: 40
                                    scale: correction2SwitchMouseArea.containsMouse ? 1.2 : 1
                                    source: correction2IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: correction2SwitchMouseArea.containsMouse ? true : false
                                        shadowColor: "#1d4ed8"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: correction2SwitchMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                                Item {
                                    id: _margin_2

                                    x: 40
                                    y: 0

                                    height: 16
                                    width: 49.05

                                    Text {
                                        id: _text_152

                                        x: 4

                                        height: 16
                                        width: 37.05

                                        color: "red"
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 18
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignLeft
                                        lineHeight: 16
                                        lineHeightMode: Text.FixedHeight
                                        text: correction2IsOn ? "正向" : "反向"
                                        textFormat: Text.PlainText
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    Text {
                                        id: _text_162

                                        anchors.left: _text_152.right

                                        height: 16
                                        width: 22.05

                                        color: "#2563eb"
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 18
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignLeft
                                        lineHeight: 16
                                        lineHeightMode: Text.FixedHeight
                                        text: "修正"
                                        textFormat: Text.PlainText
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                            }

                                Text {
                                    id: pID_
                                anchors.left: allFansPIDSwitch.right
                                anchors.leftMargin: 10
                                    y: 2

                                    height: 16
                                    width: 123

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 16
                                    lineHeightMode: Text.FixedHeight
                                    text: "PID 啟動監控"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }

                                Image {
                                    id: allFansPIDSwitch

                                anchors.left: correction2.right
                                anchors.leftMargin: 65
                                    y: 1
                                    height: 20
                                    width: 40
                                    scale: allFansPIDSwitchMouseArea.containsMouse ? 1.2 : 1
                                    source: fansPIDIsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: allFansPIDSwitchMouseArea.containsMouse ? true : false
                                        shadowColor: "#1d4ed8"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: allFansPIDSwitchMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        // }
                        Text {
                            id: element_45

                            height: 24
                            width: 129

                            color: "#1e293b"
                            font.family: "Noto Sans TC"
                            font.pixelSize: 24
                            font.weight: Font.Bold
                            horizontalAlignment: Text.AlignLeft
                            lineHeight: 24
                            lineHeightMode: Text.FixedHeight
                            text: "風扇控制"
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                        }
                        Rectangle {
                            id: vertical_Divider

                            x: 147.67

                            height: 24
                            width: 0.48

                            color: "#e2e8f0"
                        }
                    }
                    Item {
                        id: group_2

                        x: 1095

                        height: 38
                        width: 611

                        Item {
                            id: container_22

                            x: 29.03

                            height: 38
                            width: 506.97
                            RowLayout {
                            Rectangle {
                                id: fansP

                                height: 42
                                    width: 170

                                border.width: fansPTxtInput.focus ? 3 : 1
                                border.color: fansPTxtInput.focus ? "#2563eb" : "#e2e8f0"
                                color: "#ffffff"
                                radius: 12
                                    RowLayout {
                                        anchors.fill: parent
                                        anchors.rightMargin: 0
                                        // anchors.rightMargin: -45
                                        Layout.fillWidth: true
                                        spacing: 8
                                Text {
                                    id: p_1

                                            // x: 13
                                            // y: 11.50

                                            // height: 15
                                            // width: 7.48
                                            Layout.leftMargin: 10

                                    color: "#94a3b8"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "P"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 30
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.preferredWidth: 44
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 20
                                            font.weight: Font.Medium
                                            // Layout.leftMargin: 20
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: Td.fanPidPP
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            Layout.preferredWidth: 1
                                            Layout.preferredHeight: 20
                                            color: "#94a3b8"
                                            opacity: 0.5
                                            // Layout.leftMargin: 30
                                        }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            Layout.preferredWidth: 44
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                TextInput {
                                    id: fansPTxtInput

                                            // x: 13
                                            // y: 5

                                            // height: 28
                                            Layout.preferredWidth: 149
                                            Layout.leftMargin: -160

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight

                                    text: Number(Td.fanPidP)
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                                }
                            Rectangle {
                                id: fansI

                                height: 42
                                    width: 170
                                    // x: 111.66
                                    // y: -1

                                border.width: fansITxtInput.focus ? 3 : 1
                                border.color: fansITxtInput.focus ? "#2563eb" : "#e2e8f0"
                                color: "#ffffff"
                                radius: 12
                                    RowLayout {
                                        anchors.fill: parent
                                        anchors.rightMargin: 0
                                        // anchors.rightMargin: -45
                                        Layout.fillWidth: true
                                        spacing: 8
                                Text {
                                    id: i_1

                                            // x: 13
                                            // y: 11.50

                                            // height: 15
                                            // width: 3.81
                                            Layout.leftMargin: 10

                                    color: "#94a3b8"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "I"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 30
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.preferredWidth: 44
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 20
                                            font.weight: Font.Medium
                                            // Layout.leftMargin: 20
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: Td.fanPidIP
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            Layout.preferredWidth: 1
                                            Layout.preferredHeight: 20
                                            color: "#94a3b8"
                                            opacity: 0.5
                                            // Layout.leftMargin: 30
                                        }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            Layout.preferredWidth: 44
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                TextInput {
                                    id: fansITxtInput

                                            // x: 9.47
                                            // y: 5

                                            // height: 28
                                            // width: 84.19
                                            Layout.preferredWidth: 149
                                            Layout.leftMargin: -160

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight
                                    text: Number(Td.fanPidI)
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                                }

                            Rectangle {
                                id: fansD

                                height: 42
                                    width: 170
                                    // x: 225.32
                                    // y: -1

                                border.width: fansDTxtInput.focus ? 3 : 1
                                border.color: fansDTxtInput.focus ? "#2563eb" : "#e2e8f0"
                                color: "#ffffff"
                                radius: 12
                                    RowLayout {
                                        anchors.fill: parent
                                        anchors.rightMargin: 0
                                        // anchors.rightMargin: -45
                                        Layout.fillWidth: true
                                        spacing: 8
                                Text {
                                    id: d_1

                                    //x: 13
                                    //y: 11.50

                                    //height: 15
                                    //width: 8.23
                                            Layout.leftMargin: 10
                                    color: "#94a3b8"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "D"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 30
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.preferredWidth: 44
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 20
                                            font.weight: Font.Medium
                                            // Layout.leftMargin: 20
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: Td.fanPidDP
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            Layout.preferredWidth: 1
                                            Layout.preferredHeight: 20
                                            color: "#94a3b8"
                                            opacity: 0.5
                                            // Layout.leftMargin: 30
                                        }
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            Layout.preferredWidth: 44
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                TextInput {
                                    id: fansDTxtInput
                                            Layout.preferredWidth: 149
                                            Layout.leftMargin: -160

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight
                                    text: Number(Td.fanPidD)
                                    verticalAlignment: Text.AlignVCenter
                                        }
                                }
                            }
                            Rectangle {
                                id: button_5

                                x: 340.97

                                height: 38
                                width: 66

                                color: "#2563eb"
                                radius: 8

                                scale: fansPIDSetBtnMouseArea.containsMouse ? 1.02 : 1
                                Text {
                                    id: element_49

                                    x: 16
                                    y: 11

                                    height: 16
                                    width: 35

                                    color: "#ffffff"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 16
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignHCenter
                                    lineHeight: 16
                                    lineHeightMode: Text.FixedHeight
                                    text: "套用"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fansPIDSetBtnMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fansPIDSetBtnMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        }
                        Item {
                            id: container_23

                            y: 5
                            x: -500
                            height: 28
                            width: 154.85

                            Text {
                                id: element_50

                                x: 12
                                y: 6.50

                                height: 15
                                width: 74

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.pixelSize: 20
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                text: "壓差"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Item {
                                id: paragraph_10

                                x: 87

                                height: 28
                                width: 53.09

                                Text {
                                    id: element_51
                                    x: -20
                                    y: 0

                                    height: 28
                                    width: 57

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight
                                    lineHeight: 28
                                    lineHeightMode: Text.FixedHeight
                                    text: Td.pressureDiff
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {
                                    id: pa

                                    x: 39.96
                                    y: 10

                                    height: 15
                                    width: 14.13

                                    color: "#64748b"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 10
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "pa"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                        }
                        Item {
                            x: 0
                            y: 0
                            //id: container_22

                            // x: 206.03
                            anchors.left: container_23.right
                            anchors.leftMargin: 70
                            height: 38
                            width: 69

                            Rectangle {
                                id: targetPress
                                x: -63
                                y: 0

                                height: 42
                                width: 213

                                border.width: targetPressTxtInput.focus ? 3 : 1
                                border.color: targetPressTxtInput.focus ? "#2563eb" : "#e2e8f0"
                                color: "#ffffff"
                                radius: 12
                                Text {
                                    id: targetPress_1

                                    x: 13
                                    y: 11.50

                                    height: 15
                                    width: 7.48

                                    color: "#94a3b8"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "目標壓差"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                TextInput {
                                    id: targetPressTxtInput

                                    x: 13
                                    y: 5

                                    height: 28
                                    width: 181

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignRight

                                    text: Number(Td.targetPressureDiff)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Text {
                                    id: pa1

                                    anchors.left: targetPressTxtInput.right
                                    y: 13

                                    height: 15
                                    width: 18

                                    color: "#64748b"
                                    font.capitalization: Font.AllUppercase
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 10
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 15
                                    lineHeightMode: Text.FixedHeight
                                    text: "pa"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            Rectangle {
                                id: button_7

                                anchors.left: targetPress.right
                                anchors.leftMargin: 10
                                height: 38
                                width: 66

                                color: "#2563eb"
                                radius: 8

                                scale: targetPressBtnMouseArea.containsMouse ? 1.02 : 1
                                Text {
                                    id: element_511

                                    x: 16
                                    y: 11

                                    height: 16
                                    width: 35

                                    color: "#ffffff"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 16
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignHCenter
                                    lineHeight: 16
                                    lineHeightMode: Text.FixedHeight
                                    text: "套用"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: targetPressBtnMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: targetPressBtnMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                    }
                }
                Item {
                    id: container_24

                    x: 21
                    y: 76

                    height: 367
                    width: 1733

                    clip: true

                    Rectangle {
                        id: background_Border_8

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {

                            // id: _margin_2
                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_25

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans1IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_52

                                    height: 20
                                    width: 66
                                    x: 25

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 1"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }

                            Image {
                                id: fans1Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans1SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans1IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans1SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans1SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_23

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan1TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan1TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                            Text {
                                id: target_RPM

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }

                            Rectangle {
                                id: background_fan1

                                y: 22.17

                                Layout.preferredHeight: 75
                                Layout.preferredWidth: parent.width

                                border.width: fans1SetTextInput.focus ? 3 : 1
                                border.color: fans1SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans1SetTextInput

                                    x: 10
                                    // y: -1
                                    // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    text: Number(Td.fan1TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans1btn
                                                x: 91.5
                                                y: 4
                                                scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans1btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans1btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
                            }
                        }
                    }
                    Rectangle {
                        id: background_Border_10

                        x: 347.60

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {
                            id: _margin_3

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_26

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans2IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_54

                                    height: 20
                                    width: 66
                                    x: 25

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 2"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }

                            Image {
                                id: fans2Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans2SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans2IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans2SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans2SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_24

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan2TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan2TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        Text {
                                id: target_RPM_1

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Rectangle {
                                id: background_fan2

                                y: 22.17

                                Layout.preferredHeight: 75
                                Layout.preferredWidth: parent.width

                                border.width: fans2SetTextInput.focus ? 3 : 1
                                border.color: fans2SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans2SetTextInput

                                    x: 10
                                    // y: -1
                                    // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    text: Number(Td.fan2TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans2btn
                                    x: 91.5
                                    y: 4
                                    scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans2btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans2btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
                    Rectangle {
                        id: background_Border_12

                        x: 695.20

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {
                            id: _margin_4

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_27

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans3IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_56

                                    height: 20
                                    width: 66
                                    x: 25
                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 3"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }

                            Image {
                                id: fans3Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans3SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans3IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans3SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans3SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_25

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan3TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan3TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        Text {
                                id: target_RPM_2

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Rectangle {
                                id: background_fan3

                                y: 22.17

                                Layout.preferredHeight: 75
                                Layout.preferredWidth: parent.width

                                border.width: fans3SetTextInput.focus ? 3 : 1
                                border.color: fans3SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans3SetTextInput

                                    x: 10
                                    // y: -1
                                    // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    text: Number(Td.fan3TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans3btn
                                    x: 91.5
                                    y: 4
                                    scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans3btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans3btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
                            }
                        }
                    }
                    Rectangle {
                        id: background_Border_14

                        x: 1042.80

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {
                            id: _margin_5

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_28

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans4IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_58

                                    height: 20
                                    width: 66
                                    x: 25

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 4"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }

                            Image {
                                id: fans4Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans4SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans4IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans4SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans4SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_26

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan4TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan4TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        Text {
                                id: target_RPM_3

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Rectangle {
                                id: background_fan4

                                y: 22.17

                                Layout.preferredHeight: 75
                                Layout.preferredWidth: parent.width

                                border.width: fans4SetTextInput.focus ? 3 : 1
                                border.color: fans4SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans4SetTextInput

                                    x: 10
                                    // y: -1
                                    // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft

                                    text: Number(Td.fan4TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans4btn
                                    x: 91.5
                                    y: 4
                                    scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans4btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans4btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
        	}
        	}
        }
                    Rectangle {
                        id: background_Border_16

                        x: 1390.40

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {
                            id: _margin_6

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_29

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans5IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_60

                                    height: 20
                                    width: 66
                                    x: 25
                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 5"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            Image {
                                id: fans5Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans5SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans5IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans5SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans5SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_27

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan5TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan5TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        Text {
                                id: target_RPM_4

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Rectangle {
                                id: background_fan5

                                y: 22.17

                                            Layout.preferredHeight: 75
                                            Layout.preferredWidth: parent.width

                                border.width: fans5SetTextInput.focus ? 3 : 1
                                border.color: fans5SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans5SetTextInput

                                                x: 10
                                                // y: -1
                                                // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    text: Number(Td.fan5TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans5btn
                                                x: 91.5
                                                y: 4
                                                scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans5btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans5btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
                            }
                        }
                    }
                    Rectangle {
                        id: background_Border_18

                        y: 186

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {
                            id: _margin_7

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_30

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans6IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_62

                                    height: 20
                                    width: 66
                                    x: 25

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 6"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            Image {
                                id: fans6Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans6SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans6IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans6SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans6SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_28

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan6TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan6TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        Text {
                                id: target_RPM_5

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Rectangle {
                                id: background_fan6

                                y: 22.17

                                Layout.preferredHeight: 75
                                Layout.preferredWidth: parent.width

                                border.width: fans6SetTextInput.focus ? 3 : 1
                                border.color: fans6SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans6SetTextInput

                                    x: 10
                                    // y: -1
                                    // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    text: Number(Td.fan6TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans6btn
                                                x: 91.5
                                                y: 4
                                                scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans6btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans6btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
                            }
                        }
                    }
                    Rectangle {
                        id: background_Border_20

                        x: 347.60
                        y: 186

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {
                            id: _margin_8

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_31

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans7IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_64

                                    height: 20
                                    width: 66
                                    x: 25
                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 7"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            Image {
                                id: fans7Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans7SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans7IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans7SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans7SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_29

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan7TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan7TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        Text {
                                id: target_RPM_6

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Rectangle {
                                id: background_fan7

                                y: 22.17

                                            Layout.preferredHeight: 75
                                            Layout.preferredWidth: parent.width

                                border.width: fans7SetTextInput.focus ? 3 : 1
                                border.color: fans7SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans7SetTextInput

                                                x: 10
                                                // y: -1
                                                // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    text: Number(Td.fan7TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans7btn
                                                x: 91.5
                                                y: 4
                                                scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans7btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans7btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
                            }
                        }
                    }
                    Rectangle {
                        id: background_Border_22

                        x: 695.20
                        y: 186

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {
                            id: _margin_9

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_32

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans8IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_66

                                    height: 20
                                    width: 66
                                    x: 25

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 8"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            Image {
                                id: fans8Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans8SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans8IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans8SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans8SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_30

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan8TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan8TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        Text {
                                id: target_RPM_7

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Rectangle {
                                id: background_fan8

                                y: 22.17

                                Layout.preferredHeight: 75
                                Layout.preferredWidth: parent.width

                                border.width: fans8SetTextInput.focus ? 3 : 1
                                border.color: fans8SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans8SetTextInput

                                    x: 10
                                    // y: -1
                                    // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    text: Number(Td.fan8TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans8btn
                                                x: 91.5
                                                y: 4
                                                scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans8btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans8btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
                            }
                        }
                    }
                    Rectangle {
                        id: background_Border_24

                        x: 1042.80
                        y: 186

                        height: 170
                        width: 337

                        border.color: "#e2e8f0"
                        border.width: 1
                        color: "#f1f5f9"
                        radius: 12

                        Item {
                            id: _margin_10

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_33

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: fans9IsOn ?"assets/Icon12.png" : "assets/Icon11.png"
                                }

                                Text {
                                    id: element_68

                                    height: 20
                                    width: 66
                                    x: 25

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "風扇 9"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            Image {
                                id: fans9Switch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: fans9SwitchMouseArea.containsMouse ? 1.2 : 1
                                source: fans9IsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: fans9SwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: fans9SwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_31

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan9TargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fan9TargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        Text {
                                id: target_RPM_8

                                height: 14.96
                                width: 305

                                color: "#94a3b8"
                                font.capitalization: Font.AllUppercase
                                font.family: "Noto Sans TC"
                                font.letterSpacing: 1
                                font.pixelSize: 10
                                font.weight: Font.Bold
                                horizontalAlignment: Text.AlignLeft
                                lineHeight: 15
                                lineHeightMode: Text.FixedHeight
                                            text: "SV"
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                            }
                            Rectangle {
                                id: background_fan9

                                y: 22.17

                                            Layout.preferredHeight: 75
                                            Layout.preferredWidth: parent.width

                                border.width: fans9SetTextInput.focus ? 3 : 1
                                border.color: fans9SetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                clip: true
                                color: "#ffffff"
                                radius: 8

                                TextInput {
                                    id: fans9SetTextInput

                                    x: 10
                                    // y: -1
                                    // Layout.leftMargin: 10
                                    height: 67
                                    width: 244

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    text: Number(Td.fan9TargetRpm)
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Image {
                                    id: fans9btn
                                    x: 91.5
                                    y: 4
                                    scale: 1
                                    source: "assets/checkbtn.png"
                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        shadowEnabled: fans9btnMouseArea.containsMouse ? true : false
                                        shadowColor: "#caced2"
                                        shadowBlur: 0.8
                                    }
                                    MouseArea {
                                        id: fans9btnMouseArea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        cursorShape: Qt.PointingHandCursor
                                    }
                                }
                            }
                        }
                    }
        }
    }
}
                    Rectangle {
                        id: background_Border_255

                        x: 1390.40
                        y: 186

                        height: 170
                        width: 337

                        border.color: "#0e74fc"
                        border.width: 3
                        color: "#d3e4f4"
                        radius: 12

                        Item {
                            id: _margin_101

                            x: 17
                            y: 14

                            height: 32
                            width: 303

                            Item {
                                id: container_331

                                height: 20
                                width: 65
                                Image {
                                    y: 5
                                    scale: 1.2
                                    source: "assets/Icon12.png"
                                }

                                Text {
                                    id: element_681

                                    height: 20
                                    width: 66
                                    x: 25

                                    color: "#1e293b"
                                    font.family: "Noto Sans TC"
                                    font.pixelSize: 20
                                    font.weight: Font.Bold
                                    horizontalAlignment: Text.AlignLeft
                                    lineHeight: 20
                                    lineHeightMode: Text.FixedHeight
                                    text: "一鍵開啟全部"
                                    textFormat: Text.PlainText
                                    verticalAlignment: Text.AlignVCenter
                                }
                            }
                            Image {
                                id: fansallSwitch
                                x: 273
                                y: 1
                                height: 20
                                width: 40
                                scale: allFansSwitchMouseArea.containsMouse ? 1.2 : 1
                                source: allFansIsOn ? "assets/switchon.png" : "assets/switchoff.png"
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    shadowEnabled: allFansSwitchMouseArea.containsMouse ? true : false
                                    shadowColor: "#1d4ed8"
                                    shadowBlur: 0.8
                                }
                                MouseArea {
                                    id: allFansSwitchMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                }
                            }
                        }
                        Item {
                            id: frame_311

                            x: 17
                            y: 62

                            height: 91
                            width: 303

                            RowLayout {
                                anchors.fill: parent
                                Layout.fillWidth: true
                                spacing: 8
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                        anchors.fill: parent
                                        // spacing: 8
                                        Text {

                                            // id: element_26
                                            // height: 15
                                            // Layout.leftMargin: 50
                                            color: "#94a3b8"
                                            font.capitalization: Font.AllUppercase
                                            font.family: "Noto Sans TC"
                                            font.pixelSize: 12
                                            font.weight: Font.Medium
                                            // horizontalAlignment: Text.AlignLeft
                                            lineHeight: 15
                                            lineHeightMode: Text.FixedHeight
                                            text: "PV"
                                            textFormat: Text.PlainText
                                            // verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            Layout.topMargin: -5
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fanAllTargetRpmPercent
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "%"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }

                                        Rectangle {
                                            border.width: 1
                                            border.color: "#e2e8f0"
                                            color: "#ffffff"
                                            Layout.topMargin: -5
                                            Layout.preferredWidth: parent.width * 1
                                            Layout.preferredHeight: parent.height * 0.4
                                            radius: 8

                                            Text {
                                                x: 8
                                                width: 16
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: Td.fanAllTargetRpmP
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                            }
                                            Text {
                                                x: 0
                                                width: 144
                                                height: 21
                                                color: "#94a3b8"
                                                font.capitalization: Font.AllUppercase
                                                font.family: "Noto Sans TC"
                                                font.pixelSize: 14
                                                font.weight: Font.Medium
                                                // horizontalAlignment: Text.AlignLeft
                                                lineHeight: 15
                                                lineHeightMode: Text.FixedHeight
                                                text: "RPM"
                                                textFormat: Text.PlainText
                                                anchors.verticalCenter: parent.verticalCenter //文字垂直置中
                                                horizontalAlignment: Text.AlignRight
                                            }
                                        }
                                    }
                                }
                                Item {
                                    Layout.preferredWidth: parent.width * 0.5
                                    Layout.fillHeight: true
                                    ColumnLayout {
                                    anchors.fill: parent
                                    Text {
                                        id: target_RPM_81

                                        height: 14.96
                                        width: 305

                                        color: "#94a3b8"
                                        font.capitalization: Font.AllUppercase
                                        font.family: "Noto Sans TC"
                                        font.letterSpacing: 1
                                        font.pixelSize: 10
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignLeft
                                        lineHeight: 15
                                        lineHeightMode: Text.FixedHeight
                                                    text: "SV"
                                        textFormat: Text.PlainText
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    Rectangle {
                                    id: background_Border_251

                                    y: 22.17

                                    Layout.preferredHeight: 75
                                    Layout.preferredWidth: parent.width

                                    border.width: fansallSetTextInput.focus ? 3 : 1
                                    border.color: fansallSetTextInput.focus ? "#2563eb" : "#e2e8f0"
                                    clip: true
                                    color: "#ffffff"
                                    radius: 8

                                    TextInput {
                                        id: fansallSetTextInput

                                        x: 10
                                        // y: -1
                                        // Layout.leftMargin: 10
                                        height: 67
                                        width: 244

                                        color: "#1e293b"
                                        font.family: "Noto Sans TC"
                                        font.pixelSize: 20
                                        font.weight: Font.Bold
                                        horizontalAlignment: Text.AlignLeft
                                        text: Number(Td.fanAllTargetRpm)
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    Image {
                                        id: fansallbtn
                                                    x: 91.5
                                                    y: 4
                                                    scale: 1
                                        source: "assets/checkbtn.png"
                                        layer.enabled: true
                                        layer.effect: MultiEffect {
                                            shadowEnabled: fansallbtnMouseArea.containsMouse ? true : false
                                            shadowColor: "#caced2"
                                            shadowBlur: 0.8
                                        }
                                        MouseArea {
                                            id: fansallbtnMouseArea
                                            anchors.fill: parent
                                            hoverEnabled: true
                                            cursorShape: Qt.PointingHandCursor
                                        }
                                    }
                                }
                            }
                            }
                        }
                    }
                }
            }
        }
        }
    }
}

import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Studio.DesignEffects
import Core 1.0

Rectangle {
    id: root
    height: 1024
    width: 1920
    color:"#c7eaeaea"
    MouseArea {
            anchors.fill: parent
    }

    property alias ipTxtInput : ipTxtInput
    // property alias dnsTxtInput : dnsTxtInput
    // property alias gateTxtInput : gateTxtInput
    // property alias subTxtInput : subTxtInput

    Rectangle{
    id: connectionSettings
    width:448
    height:749
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    color: "#FFFFFF"
    radius: 12
    layer.enabled: true
    layer.effect: MultiEffect {
        shadowEnabled: true
        shadowColor: "#E2E8F0"
        shadowBlur: 0.8
    }

    Image {
        x:24
        y:22
        source: "assets/Overlay.png"
    }
    Text {
        id: _text_1

        x: 74
        y:20

        height: 28
        width: 78

        color: "#0F172A"
        font.family: "Noto Sans TC"
        font.pixelSize: 26
        horizontalAlignment: Text.AlignLeft
        lineHeight: 16
        lineHeightMode: Text.FixedHeight
        font.styleName: "DemiLight"
        text: "連線設定"
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignVCenter
    }
    Item{
        id:_ipItem
        x:24
        anchors.top:_text_1.bottom
        anchors.topMargin: 48
        width:237
        height:74

        Image {
            id:_ip

            scale: 1
            source: "assets/connect4.png"
        }
        Text {
            id: _text_2

            anchors.left: _ip.right
            anchors.leftMargin: 10
            anchors.top:_ip.top
            anchors.topMargin: 0

            height: 20
            width: 78

            color: "#0F172A"
            font.family: "Noto Sans TC"
            font.pixelSize: 26
            horizontalAlignment: Text.AlignLeft
            lineHeight: 16
            lineHeightMode: Text.FixedHeight
            font.styleName: "DemiLight"
            text: "IP地址"
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
        }
        Rectangle {
            id: ipInput

            height: 48
            width: 399
            anchors.left: _ip.left
            anchors.top: _ip.bottom
            anchors.topMargin: 10

            border.width: ipTxtInput.focus ? 3 : 1
            border.color: ipTxtInput.focus ? "#2563eb" : "#e2e8f0"
            color: "#f1f5f9"
            radius: 8


            Text {
                id: ipTxtInput
                 x: 10
                // y: 0

                height: 38
                width: 237

                color: "#94a3b8"
                font.family: "Noto Sans TC"
                font.pixelSize: 20
                font.weight: Font.Bold
                horizontalAlignment: Text.AlignLeft

                text: Td.ipAddress//"192.168.00.00" //Number(Td.outValveOpening)
                verticalAlignment: Text.AlignVCenter
            }
        }


    }

    Item{
        id:_subItem
        x:24
        anchors.top:_ipItem.bottom
        anchors.topMargin: 40
        width:237
        height:74

        Image {
            id:_sub

            scale: 1
            source: "assets/connect3.png"
        }
        Text {
            id: _text_3

            anchors.left: _sub.right
            anchors.leftMargin: 10
            anchors.top:_sub.top
            anchors.topMargin: 0

            height: 20
            width: 78

            color: "#0F172A"
            font.family: "Noto Sans TC"
            font.pixelSize: 26
            horizontalAlignment: Text.AlignLeft
            lineHeight: 16
            lineHeightMode: Text.FixedHeight
            font.styleName: "DemiLight"
                text: "擷取頻率"
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
        }
        Rectangle {
            id: subInput

            height: 48
            width: 399
            anchors.left: _sub.left
            anchors.top: _sub.bottom
            anchors.topMargin: 20

            border.width: subTxtInput.focus ? 3 : 1
            border.color: subTxtInput.focus ? "#2563eb" : "#e2e8f0"
            color: "#f1f5f9"
            radius: 8


            TextInput {
                id: subTxtInput
                 x: 10
                // y: 0

                height: 38
                width: 237

                color: "#1e293b"
                font.family: "Noto Sans TC"
                font.pixelSize: 20
                font.weight: Font.Bold
                horizontalAlignment: Text.AlignLeft

                text: Number(Td.captureFreq)//"255.255.00.00" //Number(Td.outValveOpening)
                verticalAlignment: Text.AlignVCenter
                validator: DoubleValidator {}
            }


        }


    }


        Item{
            id:_gateItem
            x:24
            anchors.top:_subItem.bottom
            anchors.topMargin: 40
            width:237
            height:74

            Image {
                id:_gate

                scale: 1
                source: "assets/Container11.png"
            }
            Text {
                id: _text_4

                anchors.left: _gate.right
                anchors.leftMargin: 10
                anchors.top:_gate.top
                anchors.topMargin: 0

                height: 20
                width: 78

                color: "#0F172A"
                font.family: "Noto Sans TC"
                font.pixelSize: 26
                horizontalAlignment: Text.AlignLeft
                lineHeight: 16
                lineHeightMode: Text.FixedHeight
                font.styleName: "DemiLight"
                text: "模式選擇"
                textFormat: Text.PlainText
                verticalAlignment: Text.AlignVCenter
            }
            Rectangle {
                id: modeR

                height: 48
                width: 399
                anchors.top: _text_4.bottom
                anchors.topMargin: 20
                // anchors.topMargin: 20

                border.width: 1
                border.color:"#e2e8f0"
                color: "#f1f5f9"
                radius: 8

                Row {
                    id: row
                    // height: 48
                    // width: 399
                    spacing:80
                    anchors.fill: parent
                    anchors.leftMargin: 30
                    // anchors.centerIn: parent
                    RadioButton {
                        id: radioButton
                        //x: 0
                        // anchors.left: _text_4.left
                        // anchors.topMargin: 10
                        checked: Td.modeSelect === 0 ? true : false
                        font.family: "Noto Sans TC"
                        font.bold: false
                        font.pointSize: 12
                        icon.color: "#ff4940"
                        text: "連動"
                        onClicked: {
                            Td.modeSelect = 0;
                            console.log("Td.modeSelect",Td.modeSelect)
                        }

                    }

                    RadioButton {
                        id: radioButton2
                        checked: Td.modeSelect === 1 ? true : false

                        font.family: "Noto Sans TC"
                        font.bold: false
                        font.pointSize: 12
                        icon.color: "#ff4940"
                        text: "單機"
                        onClicked: {
                            Td.modeSelect = 1;
                            console.log("Td.modeSelect",Td.modeSelect)
                        }

                    }
                }

            }
            Rectangle {
                id: confirmBtn

               y: 340

                anchors.right: modeR.right

                height: 48
                width: 96

                color: "#2563eb"
                radius: 8
                scale: confirmBtnMouseArea.containsMouse ? 1.02 : 1

                Text {
                    x: 16
                    y: 11

                    anchors.verticalCenter: parent.verticalCenter//文字垂直置中
                    anchors.horizontalCenter: parent.horizontalCenter//文字水平置中

                    color: "#ffffff"
                    font.family: "Noto Sans TC"
                    font.pixelSize: confirmBtnMouseArea.containsMouse ? 20 : 18
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
                    shadowEnabled: confirmBtnMouseArea.containsMouse ? true : false
                    shadowColor: "#1d4ed8"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: confirmBtnMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        Td.captureFreq = subTxtInput.text
                    console.log("Td.captureFreq",Td.captureFreq)
                        root.visible=false
                    }
                }
            }

            Rectangle {
                id: cancelBtn

                anchors.top: confirmBtn.top
                anchors.right: confirmBtn.left
                anchors.rightMargin: 10

                height: 48
                width: 96

                color: "#aec6c6c6"
                radius: 8
                scale: cancelBtnMouseArea.containsMouse ? 1.02 : 1

                Text {
                    x: 16
                    y: 11

                    anchors.verticalCenter: parent.verticalCenter//文字垂直置中
                    anchors.horizontalCenter: parent.horizontalCenter//文字水平置中

                    color: "#ffffff"
                    font.family: "Noto Sans TC"
                    font.pixelSize: cancelBtnMouseArea.containsMouse ? 20 : 18
                    font.weight: Font.Bold
                    horizontalAlignment: Text.AlignHCenter
                    lineHeight: 16
                    lineHeightMode: Text.FixedHeight
                    text: "取消"
                    textFormat: Text.PlainText
                    verticalAlignment: Text.AlignVCenter
                }
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: cancelBtnMouseArea.containsMouse ? true : false
                    shadowColor: "#f1f5f9"
                    shadowBlur: 0.8
                }
                MouseArea {
                    id: cancelBtnMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        root.visible=false
                    }
                }
            }
        }

    }
}

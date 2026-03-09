import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Studio.DesignEffects
import Core 1.0

Rectangle {
    id: root
    height: 1024
    width: 1920
    color:"#8dfefcfc"
    MouseArea {
            anchors.fill: parent
    }

    property alias ipTxtInput : ipTxtInput
    property alias dnsTxtInput : dnsTxtInput
    property alias gateTxtInput : gateTxtInput
    property alias subTxtInput : subTxtInput

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


            TextInput {
                id: ipTxtInput
                 x: 10
                // y: 0

                height: 38
                width: 237

                color: "#1e293b"
                font.family: "Noto Sans TC"
                font.pixelSize: 20
                font.weight: Font.Bold
                horizontalAlignment: Text.AlignLeft

                text: Td.ipAddress//"192.168.00.00" //Number(Td.outValveOpening)
                verticalAlignment: Text.AlignVCenter
                validator: DoubleValidator {}
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
            text: "子網遮罩"
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

                text: Td.subnetMask//"255.255.00.00" //Number(Td.outValveOpening)
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
            text: "預設閘道"
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
        }
        Rectangle {
            id: gateInput

            height: 48
            width: 399
            anchors.left: _gate.left
            anchors.top: _gate.bottom
            anchors.topMargin: 20

            border.width: gateTxtInput.focus ? 3 : 1
            border.color: gateTxtInput.focus ? "#2563eb" : "#e2e8f0"
            color: "#f1f5f9"
            radius: 8


            TextInput {
                id: gateTxtInput
                 x: 10
                // y: 0

                height: 38
                width: 237

                color: "#1e293b"
                font.family: "Noto Sans TC"
                font.pixelSize: 20
                font.weight: Font.Bold
                horizontalAlignment: Text.AlignLeft

                text: Td.defaultGateway//"8.8.8.8" //Number(Td.outValveOpening)
                verticalAlignment: Text.AlignVCenter
                validator: DoubleValidator {}
            }
        }


    }

    Item{
        id:_dnsItem
        x:24
        anchors.top:_gateItem.bottom
        anchors.topMargin: 40
        width:237
        height:74

        Image {
            id:_dns

            scale: 1
            source: "assets/connect1.png"
        }
        Text {
            id: _text_5

            anchors.left: _dns.right
            anchors.leftMargin: 10
            anchors.top:_dns.top
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
            text: "DNS伺服器"
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
        }
        Rectangle {
            id: dnsInput

            height: 48
            width: 399
            anchors.left: _dns.left
            anchors.top: _dns.bottom
            anchors.topMargin: 20

            border.width: dnsTxtInput.focus ? 3 : 1
            border.color: dnsTxtInput.focus ? "#2563eb" : "#e2e8f0"
            color: "#f1f5f9"
            radius: 8


            TextInput {
                id: dnsTxtInput
                 x: 10
                // y: 0

                height: 38
                width: 237

                color: "#1e293b"
                font.family: "Noto Sans TC"
                font.pixelSize: 20
                font.weight: Font.Bold
                horizontalAlignment: Text.AlignLeft

                text: Td.dnsServer//"8.8.8.8" //Number(Td.outValveOpening)
                verticalAlignment: Text.AlignVCenter
                validator: DoubleValidator {}
            }
        }


    }


    Rectangle {
        //id: dnsInput
            id:notionRec

        height: 88
        width: 399
        x:24
        y:570
        anchors.topMargin: 20

        border.width:  1
        border.color: "#DBEAFE"
        color: "#EFF6FF"
        radius: 8
        Image {
            id:_notion
            x:10
            y:10
            scale: 0.7
            source: "assets/Icon13.png"
        }
        Text {
            // id: _text_5

            anchors.left: _notion.right
            anchors.leftMargin: 10
            anchors.top:_notion.top
            anchors.topMargin: -7

            height: 65
            width: 340

            color: "#1D4ED8"
            font.family: "Noto Sans TC"
            font.pixelSize: 18
            horizontalAlignment: Text.AlignLeft
            lineHeight: 25
            lineHeightMode: Text.FixedHeight
            wrapMode: Text.Wrap
            font.styleName: "DemiLight"
            text: "請確保您的設備與網路參數相符。更改設定後可能需要重新啟動連線模組以生效"
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
        }
    }
    Rectangle {
        id: cancelBtn
        anchors.left: notionRec.right
        anchors.leftMargin: -200
        anchors.top:notionRec.top
        anchors.topMargin: 120


        height: 38
        width: 66

        color: cancelBtnMouseArea.containsMouse ? "#EFF6FF" : "#002563eb"
        radius: 8
        scale: cancelBtnMouseArea.containsMouse ? 1.02 : 1
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: cancelBtnMouseArea.containsMouse ? true : false
            shadowColor: "#DBEAFE"
            shadowBlur: 0.8
        }

        Text {
            id: element_41

            x: 16
            y: 11

            height: 16
            width: 35

            color: "#475569"
            font.family: "Noto Sans TC"
            font.pixelSize: 20

            horizontalAlignment: Text.AlignHCenter
            lineHeight: 16
            lineHeightMode: Text.FixedHeight
            font.styleName: "Light"
            text: "取消"
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: cancelBtnMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: root.visible=false
        }
    }
    Rectangle {
        id: confirmBtn

        anchors.left: cancelBtn.right
        anchors.leftMargin: 20
        anchors.top:cancelBtn.top
        anchors.topMargin: -10


        height: 50
        width: 96

        color: "#2563eb"
        radius: 8
        scale: confirmBtnMouseArea.containsMouse ? 1.02 : 1

        Text {
            //id: element_41

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
                Td.ipAddress = ipTxtInput.text
                Td.subnetMask = subTxtInput.text
                Td.defaultGateway = gateTxtInput.text
                Td.dnsServer = dnsTxtInput.text
                console.log(
                    "ip,sub,gate,dns",
                        Td.ipAddress,
                        Td.subnetMask,
                        Td.defaultGateway,
                        Td.dnsServer
                )
                root.visible=false

            }

        }
    }
}
}

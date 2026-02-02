import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    id: control

    property string btnModelData: ""

    text: btnModelData

    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.columnSpan: btnModelData === "=" ? 2 : 1

    contentItem: Item {
        Text {
            anchors.centerIn: parent
            color: "#000000"
            text: control.text
            font.pixelSize: 22
            font.bold: true
            visible: control.text !== "del"
        }
        Image {
            anchors.centerIn: parent
            width: 28; height: 28
            source: "../resource/images/backspace.svg"
            visible: control.text === "del"
            fillMode: Image.PreserveAspectFit
        }
    }

    background: Rectangle {
        radius: 10
        color: {
            if (control.pressed) return "#D0D0D0"
            if (["del", "AC"].includes(control.text)) return "#FFE0B2"
            if (["/", "*", "-", "+", "=", "+-"].includes(control.text)) return "#BBDEFB"
            return "#E0E0E0"
        }
        border.color: "transparent"
        border.width: 1
    }

}

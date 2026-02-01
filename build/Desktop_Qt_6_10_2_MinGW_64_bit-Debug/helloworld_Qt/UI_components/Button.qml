import QtQuick 2.15
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    id: control
    // Định nghĩa property để nhận dữ liệu từ vòng lặp
    property string btnText: ""
    text: btnText

    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.columnSpan: btnText === "=" ? 2 : 1

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
            source: "resource/images/backspace.svg" // Đảm bảo đường dẫn ảnh đúng
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
    }
}

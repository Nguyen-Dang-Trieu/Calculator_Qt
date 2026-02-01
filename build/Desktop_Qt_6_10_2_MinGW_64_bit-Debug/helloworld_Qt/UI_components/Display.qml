import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property var calc
    signal clicked()

    Layout.fillWidth: true
    Layout.preferredHeight: 160

    color: "#FFFFFF"
    radius: 12
    border.color: "#E0E0E0"
    border.width: 1

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 8

        Text {
            width: parent.width
            text: root.calc.history
            color: "#757575"
            font.pixelSize: 18
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideRight
        }

        Text {
            width: parent.width
            text: root.calc.display
            color: "#000000"
            font.pixelSize: 52
            font.bold: true
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideRight
            fontSizeMode: Text.Fit
        }

        Text {
            text: "Tap to view history"
            color: "#BDBDBD"
            font.pixelSize: 11
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

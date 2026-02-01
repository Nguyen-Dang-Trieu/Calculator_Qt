import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.company.calculator 1.0

Popup {
    id: historyPanel

    property alias historyModel: historyList.model
    property Calculator calc

    width: parent.width * 0.9
    height: parent.height * 0.7
    anchors.centerIn: parent
    modal: true
    background: Rectangle { color: "#FFFFFF"; radius: 15; border.color: "#BBDEFB"; border.width: 2 }

    contentItem: ColumnLayout {
        spacing: 15

        Text {
            text: "History"
            color: "#000000"
            font.pixelSize: 24
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 10
        }

        ListView {
            id: historyList
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 8

            delegate: Rectangle {
                width: historyList.width
                height: 50
                color: "#F5F5F5"
                radius: 8
                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 15
                    text: modelData // Dữ liệu để hiển thị
                    color: "#333333"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        Button {
            text: "Clear History"
            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                calc.clearHistory()
                historyList.model = []
            }

            background: Rectangle {
                implicitWidth: 160
                implicitHeight: 40
                color: "#FFCDD2"
                radius: 20
            }

            contentItem: Text {
                text: "Clear History"
                color: "#000000"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            text: "Close"
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 10
            onClicked: historyPanel.close()
            background: Rectangle { implicitWidth: 100; implicitHeight: 40; color: "#BBDEFB"; radius: 20 }
            contentItem: Text { text: "Close"; color: "#000000"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; font.bold: true }
        }
    }
}

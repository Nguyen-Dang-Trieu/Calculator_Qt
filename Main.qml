import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.company.calculator 1.0
import "UI_components"

Window {
    width: 360
    height: 640
    visible: true
    title: "Calculator Pro"

    Calculator { id: calc }

    Rectangle {
        anchors.fill: parent
        color: "#F5F5F5"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 12

            // DISPLAY
            Display {
                calc: calc

                onClicked: {
                    historyPopup.historyModel = calc.getHistoryList()
                    historyPopup.open()
                }
            }

            // KEYBOARD
            GridLayout {
                id: keyboardGrid
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 4
                rowSpacing: 10
                columnSpacing: 10

                Repeater {
                    model: ["del", "AC", "+-", "/", "7", "8", "9", "*", "4", "5", "6", "-", "1", "2", "3", "+", "0", ".", "="]

                    CalcButton {
                        btnModelData: modelData
                        onClicked: calc.handleInput(modelData)
                    }
                }
            }
        }
    }

    // Popup
    HistoryPanel {
        id: historyPopup
        calc: calc
    }
}

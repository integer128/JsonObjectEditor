import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: "Json Object Editor"

    FileDialog {
        id: fileDialog
        title: "Выберите JSON файл"
        folder: shortcuts.home
        selectMultiple: false
        nameFilters: ["JSON (*.json)"]

        onAccepted: {
            jsonmodel.openJson(fileDialog.fileUrl)
        }

        onRejected: {
            console.log("Canceled")
        }
    }

    header: ToolBar {
        id: header_tb

        Label {
            id: header_lbl
            anchors.centerIn: parent
            text: jsonmodel._message
        }
    }

    footer: ToolBar {
        id: footer_tb

        RowLayout {
            anchors.fill: parent

            Button {
                id: open_btn
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width / 4
                Layout.alignment: Qt.AlignLeft
                text: "Открыть"
                flat: true

                onClicked: {
                    fileDialog.open()
                }
            }

            Button {
                id: save_btn
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width / 4
                Layout.alignment: Qt.AlignRight
                text: "Сохранить"
                flat: true

                onClicked: {
                    jsonmodel.saveJson();
                }
            }
        }
    }

    JsonView {
        id: jsonView
    }

    Component.onCompleted: {
        jsonmodel._message = "Откройте файл"
    }
}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.0
//Si no importamos labs.plataform el menubar no es nativo (en MS no esta operativo)
import Qt.labs.platform 1.1

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MenuBar {
        id: menuBar

        Menu {
            id: fileMenu
            title: qsTr("File")
            // ...
        }

        Menu {
            id: editMenu
            title: qsTr("&Edit")
            // ...
        }

        Menu {
            id: viewMenu
            title: qsTr("&View")
            // ...
        }

        Menu {
            id: helpMenu
            title: qsTr("&Help")
            // ...
        }
    }

    ToolBar {
        id: toolBar
        position: ToolBar.Header
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Row {
            id: rowLayout
            anchors.fill: parent
            spacing: 30

            ToolButton {
                id: toolButton
                x: 201
                y: 0
                text: qsTr("Tool Button")
            }

            ToolButton {
                id: toolButton1
                x: 396
                y: 0
                text: qsTr("Tool Button")
            }
        }
    }

    Frame {
        id: pane
        contentHeight: 300
        contentWidth: 400
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Login {
            anchors.fill: parent
        }
    }
}

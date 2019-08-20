﻿import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import MainClass 1.0

Item {
    id: applicationWindow
    visible: true

    ToolBar {
        id: toolBar
        position: ToolBar.Header
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        Row {
            id: rowLayout
            anchors.fill: parent
            spacing: 10

            ToolButton {
                id: toolButton
                text: qsTr("Tool Button")
            }

            ToolButton {
                id: toolButton1
                text: qsTr("Tool Button")
            }
        }
    }
    Frame {
        id: pane
        contentHeight: 400
        contentWidth: 800
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3

Item {
    id: window
    visible: true
    width: loginWindow.width
    height: loginWindow.height
    property alias textError: textError
    property alias textInputPassword: textInputPassword
    property alias textInputUsename: textInputUsename
    property alias buttonCancelar: buttonCancelar
    property alias buttonAceptar: buttonAceptar

    GroupBox {
        id: groupBox
        anchors.rightMargin: 15
        anchors.leftMargin: 15
        anchors.bottomMargin: 15
        anchors.topMargin: 15
        anchors.fill: parent
        padding: 15
        title: qsTr("Credenciales")

        GridLayout {
            id: gridLayout
            rows: 3
            columns: 3
            flow: GridLayout.LeftToRight
            columnSpacing: 15
            rowSpacing: 15
            anchors.topMargin: 15
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            Label {
                id: labelUsername
                text: qsTr("Usuario:")
                Layout.minimumWidth: 100
                Layout.preferredHeight: 25
            }
            TextField {
                id: textInputUsename
                //overwriteMode: true
                selectByMouse: true
                renderType: Text.NativeRendering
                Layout.columnSpan: 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                maximumLength: 25
            }
            Label {
                id: labelPassword
                text: qsTr("Password:")
                Layout.fillWidth: true
            }

            TextField {
                id: textInputPassword
                //overwriteMode: true
                selectByMouse: true
                Layout.columnSpan: 2
                Layout.fillHeight: true
                Layout.fillWidth: true
                maximumLength: 25
                echoMode: TextInput.Password
            }
            Item {
                Layout.fillWidth: true
            }

            Button {
                id: buttonAceptar
                text: qsTr("Aceptar")
            }

            Button {
                id: buttonCancelar
                text: qsTr("Cancelar")
            }
        }
        Text {
            id: textError
            height: 60
            color: "#ef2929"
            anchors.topMargin: 15
            anchors.top: gridLayout.bottom
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: gridLayout.horizontalCenter
        }
    }
}

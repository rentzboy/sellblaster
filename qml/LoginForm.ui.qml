import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
//QML type: LoginDialog
import LoginClass 1.0
import "components"

Window {
    id: root
    visible: true
    maximumHeight: 300
    minimumHeight: 300
    maximumWidth: 420
    minimumWidth: 420
    title: qsTr("Hello World")

    LoginDialog {
        id: loginclass
    }
    Background {

        GroupBox {
            id: groupBox
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.bottomMargin: 15
            anchors.topMargin: 15
            anchors.fill: parent
            title: qsTr("Credenciales")

            GridLayout {
                id: gridLayout
                rows: 2
                flow: GridLayout.TopToBottom
                rowSpacing: 10
                columnSpacing: 0
                anchors.topMargin: 10
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 15
                anchors.right: parent.right
                anchors.rightMargin: 200

                Label {
                    id: labelUsername
                    text: qsTr("Usuario:")
                    topPadding: 6
                    Layout.minimumWidth: 120
                    Layout.preferredHeight: 30
                }
                Label {
                    id: labelPassword
                    text: qsTr("Password:")
                    topPadding: 6
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30
                }
                TextInputField {
                    id: textInputUsename
                    Layout.minimumWidth: 200
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    maximumLength: 15
                    text: loginclass.username
                    onEditingFinished: loginclass.username = textInputUsename.text
                }
                TextInputField {
                    id: textInputPassword
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    maximumLength: 15
                    text: loginclass.password
                    echoMode: TextInput.Password
                    onEditingFinished: loginclass.password = textInputPassword.text
                }
            }

            Row {
                id: rowButtons
                spacing: 20
                anchors.top: gridLayout.bottom
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 15

                Button {
                    id: buttonAceptar
                    text: qsTr("Aceptar")
                    Material.background: Material.Orange
                    font.capitalization: Font.Capitalize
                    onClicked: loginclass.onAceptarClicked()
                }
                Button {
                    id: buttonCancelar
                    text: qsTr("Cancelar")
                    //Material.background: Material.Teal
                    font.capitalization: Font.Capitalize
                    onClicked: loginclass.onCancelarClicked()
                }
            }

            Text {
                id: textError
                height: 30
                color: "#ef2929"
                text: loginclass.errorMsg
                visible: loginclass.errorVisible
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: rowButtons.bottom
                anchors.topMargin: 15
            }
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


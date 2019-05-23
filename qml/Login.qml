import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import LoginClass 1.0

Window {
    id: loginWindow
    visible: true
    maximumHeight: 300
    minimumHeight: 300
    maximumWidth: 400
    minimumWidth: 400
    title: qsTr("Acceso Sellblaster")

    BackgroundZ1 {
    }

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }

    LoginForm {
        id: form

        textInputUsename.text: LoginDialog.userName

        textInputUsename.onEditingFinished: LoginDialog.onUserNameUpdated(
                                                textInputUsename.text)
        textInputPassword.onEditingFinished: LoginDialog.onPasswordUpdated(
                                                 textInputPassword.text)

        buttonCancelar.onClicked: LoginDialog.onCancelarClicked()
        buttonAceptar.onClicked: LoginDialog.onAceptarClicked()

        textError.text: LoginDialog.errorMsg
        textError.visible: LoginDialog.errorVisible
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
//QML type: LoginDialog
import LoginClass 1.0
import "components"

//singleton Settings 1.0 Settings.qml

//pragma Singleton
Window {
    id: window
    visible: true
    maximumHeight: 300
    minimumHeight: 300
    maximumWidth: 420
    minimumWidth: 420
    title: qsTr("Acceso Sellblaster")

    LoginDialog {
        //es nuestro objeto C++ (pending pasarlo a Singleton)
        id: loginclass
    }
    LoginForm {
        id: form
        signal onUsernameUpdated(string value)
        signal onPasswordChanged(string value)

        textInputUsename.text: loginclass.username

        textInputUsename.onEditingFinished: loginclass.onUsernameUpdated(
                                                textInputUsename.text)

        textInputPassword.onEditingFinished: passwordChanged(
                                                 textInputPassword.text)

        buttonCancelar.onClicked: loginclass.onCancelarClicked()
        buttonAceptar.onClicked: loginclass.onAceptarClicked()

        textError.text: loginclass.errorMsg
        textError.visible: loginclass.errorVisible
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import "ui"
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

    LoginForm {
        id: form

        textInputUsename.text: LoginType.userName
        textInputPassword.text: "aaaaaa"
        textError.text: LoginType.errorMsg
        textError.visible: LoginType.errorVisible

        textInputUsename.onEditingFinished: LoginType.userName = textInputUsename.text
        textInputPassword.onEditingFinished: LoginType.password = textInputPassword.text

        buttonCancelar.onClicked: LoginType.onCancelarClicked()
        buttonAceptar.onClicked: LoginType.onAceptarClicked()

        Keys.onPressed: {
            if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return)
                LoginType.onAceptarClicked()
            if (event.key === Qt.Key_Escape)
                LoginType.onCancelarClicked()
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


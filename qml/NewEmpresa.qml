import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"

Window {
    id: loginWindow
    visible: true
    minimumWidth: 1150
    minimumHeight: 600
    title: qsTr("Nueva empresa")
    BackgroundZ1 {
    }

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }

    NewEmpresaForm {
        id: form
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

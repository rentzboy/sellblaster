import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.0
//Si no importamos labs.plataform el menubar no es nativo (en MS no esta operativo)
import Qt.labs.platform 1.1
import "components"

Item {
    id: newProveedorFormWindow
    visible: true

    Pane {
        id: pane
        clip: true
        anchors.fill: parent

        TabBar {
            id: bar
            width: parent.width
            clip: true
            anchors.top: parent.top
            anchors.topMargin: 0

            TabButton {
                text: qsTr("Empresa")
                clip: true
                display: AbstractButton.TextOnly
                width: 150
            }
            TabButton {
                text: qsTr("Contactos")
                display: AbstractButton.TextOnly
                width: 150
            }
            TabButton {
                text: qsTr("Productos")
                display: AbstractButton.TextOnly
                width: 150
            }
            TabButton {
                text: qsTr("Certificaciones")
                display: AbstractButton.TextOnly
                width: 200
            }
        }

        StackLayout {
            //Solo muestra 1 childItem, que corresponde con el currentIndex
            width: parent.width
            height: parent.height - bar.height
            anchors.top: bar.bottom
            anchors.topMargin: 0
            anchors.bottomMargin: 0
            currentIndex: bar.currentIndex

            EmpresaTab {
                id: empresa
                Layout.fillHeight: parent
                Layout.fillWidth: parent
            }
            ContactosTab {
                id: contactos
                Layout.fillHeight: parent
                Layout.fillWidth: parent
            }
            Item {
                id: productos
                Layout.fillHeight: parent
                Layout.fillWidth: parent
            }
            Item {
                id: certificaciones
                Layout.fillHeight: parent
                Layout.fillWidth: parent
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

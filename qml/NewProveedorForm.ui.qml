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
    property alias bar: bar
    property int comboBoxAreaCurrentIndex: comboBoxAreaCurrentIndex
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

            TabButton {
                text: qsTr("Empresa")
                objectName: "empresa"
                clip: true
                display: AbstractButton.TextOnly
                width: 150
            }
            TabButton {
                text: qsTr("Contactos")
                objectName: "contactos"
                display: AbstractButton.TextOnly
                width: 150
            }
            TabButton {
                text: qsTr("Productos")
                objectName: "productos"
                display: AbstractButton.TextOnly
                width: 150
            }
            TabButton {
                text: qsTr("Certificaciones")
                objectName: "certificaciones"
                display: AbstractButton.TextOnly
                width: 200
            }
        }

        StackLayout {
            id: stackLayout
            //Solo muestra 1 childItem, que corresponde con el currentIndex
            width: parent.width
            height: parent.height - bar.height
            anchors.top: bar.bottom
            currentIndex: bar.currentIndex

            EmpresaTab {
                id: empresa
                Layout.fillHeight: parent
                Layout.fillWidth: parent
            }
            ContactosTab {
                id: contactos
                width: 2
                Layout.fillHeight: parent
                Layout.fillWidth: parent
            }
            ProductosTab {
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

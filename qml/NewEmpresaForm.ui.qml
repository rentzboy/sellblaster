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
    id: applicationWindow
    visible: true
    width: loginWindow.width
    height: loginWindow.height
    anchors.fill: parent
    anchors.rightMargin: 15
    anchors.leftMargin: 15
    anchors.bottomMargin: 15
    anchors.topMargin: 15

    Pane {
        id: pane
        anchors.fill: parent

        TabBar {
            id: bar
            width: parent.width
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
            height: parent.height
            anchors.top: bar.bottom
            anchors.topMargin: 0
            currentIndex: bar.currentIndex

            EmpresaTab {
                id: empresa
                width: parent.width
                Rectangle {
                    color: "#00000000"
                    anchors.fill: parent
                    border.color: "#bcb1b1"
                }
            }
            Item {
                id: contactos
                Rectangle {
                    anchors.fill: parent
                    border.color: "#bcb1b1"
                }
            }
            Item {
                id: productos
                Rectangle {
                    anchors.fill: parent
                    border.color: "#bcb1b1"
                }
                Item {
                    id: certificaciones
                    Rectangle {
                        anchors.fill: parent
                        border.color: "#bcb1b1"
                    }
                }
            }
        }
    }
}

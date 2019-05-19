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

Window {
    id: applicationWindow
    visible: true
    minimumWidth: 1150
    minimumHeight: 600
    title: qsTr("Nueva empresa")
    Background {
        anchors.fill: parent
        color: "#efefef"
        border.color: "#c3c3c3"
    }

    Pane {
        id: pane
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.fill: parent
        background: Background {
            anchors.fill: parent
            color: "#efefef"
        }

        TabBar {
            id: bar
            width: parent.width
            anchors.top: parent.top
            anchors.topMargin: 0
            background: Background {
                anchors.fill: parent
                color: "#efefef"
            }

            TabButton {
                text: qsTr("Empresa")
                display: AbstractButton.TextOnly
                width: 150
                Rectangle {
                    color: "#00000000"
                    anchors.fill: parent
                    border.color: "#c3c3c3"
                }
            }
            TabButton {
                text: qsTr("Discover")
                display: AbstractButton.TextOnly
                width: 150
                Rectangle {
                    color: "#00000000"
                    anchors.fill: parent
                    border.color: "#c3c3c3"
                }
            }
            TabButton {
                text: qsTr("Activity")
                display: AbstractButton.TextOnly
                width: 150
                Rectangle {
                    color: "#00000000"
                    anchors.fill: parent
                    border.color: "#c3c3c3"
                }
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
            }
            Item {
                id: discoverTab
                Background {
                    anchors.fill: parent
                    border.color: "#bcb1b1"
                }
            }
            Item {
                id: activityTab
                Background {
                    anchors.fill: parent
                    border.color: "#bcb1b1"
                }
            }
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


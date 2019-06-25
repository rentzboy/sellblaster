import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
//Si no importamos labs.plataform el menubar no es nativo (en MS no esta operativo)
import Qt.labs.platform 1.1
import "components"
import MainClass 1.0

//import MainClass 1.0
ApplicationWindow {
    id: window
    visible: true
    //minimumHeight y minimumWidth tienen que ser > que los minH y minW de los popups
    minimumHeight: 800
    minimumWidth: 1500
    title: qsTr("Sellblaster - Copia registrada")

    onHeightChanged: function updateHeightProperty() {
        MainWindow.windowSize.height = height
        console.log("HeightChanged: " + MainWindow.windowSize.height)
    }

    onWidthChanged: function updateWidthProperty() {
        MainWindow.windowSize.width = width
        console.log("WidthChanged: " + MainWindow.windowSize.width)
    }

    onXChanged: function updateX() {
        MainWindow.windowPosition.x = x
    }

    onYChanged: function updateY() {
        MainWindow.windowPosition.y = y
    }

    onClosing: function closeApp() {
        //PENDING -guardar antes de salir-
        console.log("Recuperando los datos de la pantalla onClosing")
        console.log(MainWindow.windowSize.width)
        console.log(MainWindow.windowSize.height)
        MainWindow.onClosingHandler()
    }

    Component.onCompleted: function setWindowSize() {
        //OJO: Hasta que no se carga el componente no se pueden recuperar los valores
        x = MainWindow.windowPosition.x
        y = MainWindow.windowPosition.y
        width = MainWindow.windowSize.width
        height = MainWindow.windowSize.height
        console.log(MainWindow.windowSize.width)
        console.log(MainWindow.windowSize.height)
        console.log("Modelo screen: " + Screen.model)
        console.log("Numero serie screen: " + Screen.serialNumber)
    }

    //FUNCTIONS

    //SIGNALS
    //SLOTS
    function onCloseQmlInstance() {
        close()
    }
    MainWindowForm {
        id: form
        anchors.fill: parent

        MenuBar {
            id: menuBar

            Menu {
                id: fileMenu
                title: qsTr("Empresa")
                MenuItem {
                    id: newProveedor
                    text: "Añadir proveedor"
                    shortcut: "Ctrl+A"
                    onTriggered: MainWindow.onAnadirProveedor()
                }

                MenuItem {
                    id: salirApp
                    text: "Salir"
                    shortcut: StandardKey.Quit
                    onTriggered: Qt.quit()
                }
            }

            Menu {
                id: editMenu
                title: qsTr("&Edit")
                // ...
            }

            Menu {
                id: viewMenu
                title: qsTr("&View")
                // ...
            }

            Menu {
                id: helpMenu
                title: qsTr("&Help")
                // ...
            }
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


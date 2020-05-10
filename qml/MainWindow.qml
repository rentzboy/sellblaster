import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
//Si no importamos labs.plataform el menubar no es nativo (en MS no esta operativo)
import Qt.labs.platform 1.1
import "components"
import MainClass 1.0

//minimumHeight y minimumWidth tienen que ser > que los minH y minW de los popups
ApplicationWindow {
    id: window
    visible: true
    minimumHeight: 800
    minimumWidth: 1500
    title: qsTr("Sellblaster - Copia registrada")

    MenuBar {
        id: menuBar

        Menu {
            id: fileMenu
            title: qsTr("Empresa")
            MenuItem {
                id: newProveedor
                text: "Añadir proveedor"
                shortcut: "Ctrl+A"
                onTriggered: MainWindowType.onAnadirProveedor()
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

    onHeightChanged: function updateHeightProperty() {
        MainWindowType.windowSize.height = height
        //console.log("HeightChanged: " + MainWindowType.windowSize.height)
    }

    onWidthChanged: function updateWidthProperty() {
        MainWindowType.windowSize.width = width
        //console.log("WidthChanged: " + MainWindowType.windowSize.width)
    }

    onXChanged: function updateX() {
        MainWindowType.windowPosition.x = x
    }

    onYChanged: function updateY() {
        MainWindowType.windowPosition.y = y
    }

    onClosing: function closeApp() {
        //PENDING -preguntar si cerrar sin guardar antes de salir-
        console.log("Recuperando los datos de la pantalla onClosing")
        //console.log(MainWindowType.windowSize.width)
        //console.log(MainWindowType.windowSize.height)
        close.accepted = false //no sirve de nada, se cierra igual al final del {}
        MainWindowType.onClosingHandler()
        console.log("Good night Qt !!")
    }

    Component.onCompleted: function setWindowSize() {
        //OJO: Hasta que no se carga el componente no se pueden recuperar los valores
        x = MainWindowType.windowPosition.x
        y = MainWindowType.windowPosition.y
        width = MainWindowType.windowSize.width
        height = MainWindowType.windowSize.height
        //console.log(MainWindowType.windowSize.width)
        //console.log(MainWindowType.windowSize.height)
        //console.log("Modelo screen: " + Screen.model)
        //console.log("Numero serie screen: " + Screen.serialNumber)
    }

    //FUNCTIONS
    //SIGNALS
    //SLOTS
    function onCloseQmlInstance() {
        //No se utiliza
        console.log("Se ha llamado a onCloseQmlInstance desde MainWindow.qml")
        close()
    }

    MainWindowForm {
        id: form
        anchors.fill: parent
        toolButtonStocklist.onClicked: MainWindowType.close()
        toolButtonProveedores.onClicked: MainWindowType.close()
        toolButtonClientes.onClicked: MainWindowType.close()

        Keys.onPressed: {
            //Crtl+P -Añadir nuevo proveedor ===> OJO: NO ESTÁ FUNCIONANDO
            if (event.key === Qt.Key_P && event.modifiers === Qt.ControlModifier) {
                console.log("Key logger: Crtl+P")
                MainWindowType.onAnadirProveedor()
            }
        }
    }
}






/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

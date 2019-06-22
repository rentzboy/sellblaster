import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import MainClass 1.0

Window {
    id: newProveedorWindow
    visible: true
    minimumWidth: 1400 //menor que MainWindow
    minimumHeight: 600 //menow que MainWindow
    title: qsTr("Nuevo proveedor")

    BackgroundZ1 {
    }

    Component.onCompleted: function setWindowPosition() {
        if (MainWindow.windowSize.width > minimumWidth)
            x = ((MainWindow.windowSize.width - minimumWidth) / 2) + MainWindow.windowPosition.x
        else
            x = 0
        if (MainWindow.windowSize.height > minimumHeight)
            y = ((MainWindow.windowSize.height - minimumHeight) / 2) + MainWindow.windowPosition.y
        else
            y = 0
    }

    //SLOTS
    function onCloseQmlInstance() {
        console.log("Se ha llamado a la función: onCloseQmlInstance.")
        close()
    }

    NewProveedorForm {
        id: form
        anchors.fill: parent
        anchors.rightMargin: 15
        anchors.leftMargin: 15
        anchors.bottomMargin: 15
        anchors.topMargin: 15
        focus: true

        Keys.onPressed: {
            if (event.key === Qt.Key_PageUp) {
                if (bar.currentIndex === 0) {
                    event.accepted = true
                } else {
                    bar.currentIndex--
                    event.accepted = true
                }
            } else if (event.key === Qt.Key_PageDown) {
                if (bar.currentIndex === bar.count) {
                    event.accepted = true
                } else {
                    bar.currentIndex++
                    event.accepted = true
                }
            }
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


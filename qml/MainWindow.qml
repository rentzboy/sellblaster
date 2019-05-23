import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import "components"
import MainClass 1.0

//import MainClass 1.0
ApplicationWindow {
    id: window
    visible: true
    minimumHeight: MainWindow.windowSize.height
    minimumWidth: MainWindow.windowSize.width
    title: qsTr("Sellblaster - Copia registrada")
    //visibility: 4 //QWindow::Maximized => peta todo !!

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }

    MainWindowForm {
        id: form
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


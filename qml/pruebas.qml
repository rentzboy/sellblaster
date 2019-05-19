import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import "components"

ApplicationWindow {
    id: window
    Material.theme: Material.System
    Material.accent: Material.Purple
    visible: true
    height: 500
    width: 1200

    EmpresaTab {
        anchors.fill: parent
        Layout.minimumWidth: 1150
        Layout.minimumHeight: 500
    }
}

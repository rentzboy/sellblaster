import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3

TextField {
    id: textInputField
    text: qsTr("")
    bottomPadding: 6
    topPadding: 6
    leftPadding: 6
    rightPadding: 6
    overwriteMode: true
    placeholderText: ""
    background: Rectangle {
        id: backgroundTextField
        color: "white"
        radius: 7
        border.color: "#d9d9cf"
        border.width: 2
        anchors.fill: parent
    }
}

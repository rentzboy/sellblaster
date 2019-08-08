import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import "../../components"

GridLayout {
    id: gridTextFieldChapa
    property alias comboBoxFormatoChapa: comboBoxFormatoChapa
    property alias comboBoxFormatoChapaToogleAll: comboBoxFormatoChapa.toogleAllValues
    property alias textFieldEspesorMinChapa: textFieldEspesorMinChapa
    property alias textFieldEspesorMaxChapa: textFieldEspesorMaxChapa

    Layout.topMargin: 10
    columnSpacing: 15
    rowSpacing: 15
    columns: 9
    clip: true
    visible: false

    Label {
        id: labelFormatoChapa
        text: qsTr("Formato:")
        Layout.minimumWidth: 135
    }
    ComboBox11 {
        id: comboBoxFormatoChapa
        objectName: "formatoChapa"
        width: comboBoxTipo.width
        property bool toogleAllValues: false
    }
    SpacerH_20 {
    }

    Label {
        id: labelEspesorMinChapa
        text: qsTr("Espesor min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldEspesorMinChapa
        objectName: "espesorMin"
        width: comboBoxTipo.width
        validator: IntValidator {
            bottom: 00
            top: 99
        }
    }
    SpacerH_20 {
    }

    Label {
        id: labelEspesorMaxChapa
        text: qsTr("Espesor max:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldEspesorMaxChapa
        objectName: "espesorMax"
        width: comboBoxTipo.width
        validator: IntValidator {
            bottom: 00
            top: 999
        }
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }
}




/*##^## Designer {
    D{i:0;height:600;width:1000}
}
 ##^##*/

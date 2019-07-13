import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.0
import "components"

GridLayout {
    id: gridTextFieldChapa
    property alias comboBoxTipoChapa: comboBoxTipoChapa
    property alias textFieldEspesorMinChapa: textFieldEspesorMinChapa
    property alias textFieldEspesorMaxChapa: textFieldEspesorMaxChapa
    property alias gridTextFieldChapa: gridTextFieldChapa

    Layout.topMargin: 10
    columnSpacing: 15
    rowSpacing: 15
    columns: 9
    clip: true
    visible: false

    Label {
        id: labelTipoChapa
        text: qsTr("Tipo:")
        Layout.minimumWidth: 135
    }
    ComboBox1 {
        id: comboBoxTipoChapa
        objectName: "tipoChapa"
        width: comboBoxTipo.width
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
        objectName: "espesorMinChapa"
        width: comboBoxTipo.width
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
        objectName: "espesorMaxChapa"
        width: comboBoxTipo.width
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }
}

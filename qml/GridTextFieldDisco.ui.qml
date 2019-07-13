import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.0
import "components"

GridLayout {
    id: gridTextFieldDisco
    property alias textFieldDiametroMinDisco: textFieldDiametroMinDisco
    property alias textFieldDiametroMaxDisco: textFieldDiametroMaxDisco
    property alias textFieldEspesorMinDisco: textFieldEspesorMinDisco
    property alias textFieldEspesorMaxDisco: textFieldEspesorMaxDisco
    property alias gridTextFieldDisco: gridTextFieldDisco

    Layout.topMargin: 10
    columnSpacing: 15
    rowSpacing: 15
    columns: 6
    clip: true
    visible: false

    Label {
        id: labelDiametroMinDisco
        text: qsTr("⌀ min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldDiametroMinDisco
        objectName: "diametroMinDisco"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        x: comboBoxTipo.x
    }
    SpacerH_20 {
    }
    Label {
        id: labelDiametroMaxDisco
        text: qsTr("⌀ max:")
        Layout.minimumWidth: 135
        x: labelMaterial.x
    }
    TextField1 {
        id: textFieldDiametroMaxDisco
        objectName: "diametroMaxDisco"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
    }

    SpacerH_20 {
        Layout.fillWidth: true
    }

    Label {
        id: labelEspesorMinDisco
        text: qsTr("Espesor min:")
    }
    TextField1 {
        id: textFieldEspesorMinDisco
        objectName: "espesorMinDisco"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        x: comboBoxTipo.x
    }
    SpacerH_20 {
    }
    Label {
        id: labelEspesorMaxDisco
        text: qsTr("Espesor max:")
        x: labelMaterial.x
    }
    TextField1 {
        id: textFieldEspesorMaxDisco
        objectName: "espesorMaxDisco"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }
}


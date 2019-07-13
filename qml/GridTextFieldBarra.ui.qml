import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.0
import "components"

GridLayout {
    id: gridTextFieldBarra
    property alias textFieldDiametroMinBarra: textFieldDiametroMinBarra
    property alias textFieldDiametroMaxBarra: textFieldDiametroMaxBarra
    property alias textFieldLargoMinBarra: textFieldLargoMinBarra
    property alias textFieldLargoMaxBarra: textFieldLargoMaxBarra
    property alias gridTextFieldBarra: gridTextFieldBarra

    Layout.topMargin: 10
    columnSpacing: 15
    rowSpacing: 15
    columns: 6
    clip: true
    visible: false

    Label {
        id: labelDiametroMinBarra
        text: qsTr("⌀ min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldDiametroMinBarra
        objectName: "diametroMinBarra"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        x: comboBoxTipo.x
    }
    SpacerH_20 {
    }
    Label {
        id: labelDiametroMaxBarra
        text: qsTr("⌀ max:")
        Layout.minimumWidth: 135
        x: labelMaterial.x
    }
    TextField1 {
        id: textFieldDiametroMaxBarra
        objectName: "diametroMaxBarra"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        x: comboBoxMaterial.x
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }

    Label {
        id: labelLargoMinBarra
        text: qsTr("Largo min:")
    }
    TextField1 {
        id: textFieldLargoMinBarra
        objectName: "largoMinBarra"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        x: comboBoxTipo.x
    }
    SpacerH_20 {
    }
    Label {
        id: labelLargoMaxBarra
        text: qsTr("Largo max:")
        x: labelMaterial.x
    }
    TextField1 {
        id: textFieldLargoMaxBarra
        objectName: "largoMaxBarra"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        x: comboBoxMaterial.x
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }
}


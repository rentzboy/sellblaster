import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import SupplierClass 1.0
import "../../components"

GridLayout {
    id: gridTextFieldBobina
    property alias comboBoxAnchoBobina: comboBoxAnchoBobina
    property alias textFieldEspesorMinBobina: textFieldEspesorMinBobina
    property alias textFieldEspesorMaxBobina: textFieldEspesorMaxBobina
    property alias comboBoxDiametroIntBobina: comboBoxDiametroIntBobina

    Layout.topMargin: 10
    Layout.fillWidth: true
    columnSpacing: 15
    rowSpacing: 15
    columns: 9
    clip: true
    visible: false

    Label {
        id: labelAnchoBobina
        text: qsTr("Ancho:")
        Layout.minimumWidth: 135
    }
    ComboBox11 {
        id: comboBoxAnchoBobina
        objectName: "anchoBobina"
        width: comboBoxTipo.width
    }
    SpacerH_20 {
    }
    Label {
        id: labelEspesorMinBobina
        text: qsTr("Espesor min:")
        Layout.minimumWidth: 135
        x: labelMaterial.x
    }
    TextField1 {
        id: textFieldEspesorMinBobina
        objectName: "espesorMinBobina"
        x: comboBoxMaterial.x
        width: comboBoxTipo.width
    }
    SpacerH_20 {
    }
    Label {
        id: labelEspesorMaxBobina
        text: qsTr("Espesor max:")
        Layout.minimumWidth: 135
        x: labelSerie.x
    }
    TextField1 {
        id: textFieldEspesorMaxBobina
        objectName: "espesorMaxBobina"
        x: comboBoxSerie.x
        width: comboBoxTipo.width
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }

    Label {
        id: labelDiametroIntBobina
        text: qsTr("ID:")
    }
    ComboBox1 {
        id: comboBoxDiametroIntBobina
        objectName: "diametroIntBobina"
        width: comboBoxTipo.width
    }
    SpacerH_20 {
    }
}

/*##^## Designer {
    D{i:0;height:600;width:1000}
}
 ##^##*/

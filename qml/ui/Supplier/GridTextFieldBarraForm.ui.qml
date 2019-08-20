import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import "../../components"

GridLayout {
    id: gridTextFieldBarra
    property alias textFieldDiametroMinBarra: textFieldDiametroMinBarra
    property alias textFieldDiametroMaxBarra: textFieldDiametroMaxBarra
    property alias textFieldLargoMinBarra: textFieldLargoMinBarra
    property alias textFieldLargoMaxBarra: textFieldLargoMaxBarra

    Label {
        id: labelDiametroMinBarra
        text: qsTr("⌀ min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldDiametroMinBarra
        objectName: "diametroMin"
        supplierTab: "producto"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        x: comboBoxTipo.x
        validator: IntValidator {
            bottom: 00
            top: 999
        }
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
        objectName: "diametroMax"
        supplierTab: "producto"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        x: comboBoxMaterial.x
        validator: IntValidator {
            bottom: 00
            top: 999
        }
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
        objectName: "largoMin"
        supplierTab: "producto"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        validator: IntValidator {
            bottom: 00
            top: 9999
        }
    }
    SpacerH_20 {
    }
    Label {
        id: labelLargoMaxBarra
        text: qsTr("Largo max:")
    }
    TextField1 {
        id: textFieldLargoMaxBarra
        objectName: "largoMax"
        supplierTab: "producto"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        validator: IntValidator {
            bottom: 00
            top: 9999
        }
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

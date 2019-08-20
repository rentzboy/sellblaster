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
    property alias comboBoxAnchoBobinaToogleAll: comboBoxAnchoBobina.toogleAllValues
    property alias textFieldEspesorMinBobina: textFieldEspesorMinBobina
    property alias textFieldEspesorMaxBobina: textFieldEspesorMaxBobina
    property alias comboBoxDiametroIntBobina: comboBoxDiametroIntBobina
    property alias comboBoxDiametroIntToogleAll: comboBoxDiametroIntBobina.toogleAllValues

    Label {
        id: labelAnchoBobina
        text: qsTr("Ancho:")
        Layout.minimumWidth: 135
    }
    ComboBox11 {
        id: comboBoxAnchoBobina
        objectName: "anchoBobina"
        supplierTab: "producto"
        toogleAllValues: false
    }
    SpacerH_20 {
    }
    Label {
        id: labelEspesorMinBobina
        text: qsTr("Espesor min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldEspesorMinBobina
        objectName: "espesorMin"
        supplierTab: "producto"
        Layout.minimumWidth: 150
        validator: DoubleValidator {
            bottom: 00
            top: 99
            decimals: 2
        }
    }
    SpacerH_20 {
    }
    Label {
        id: labelEspesorMaxBobina
        text: qsTr("Espesor max:")
    }
    TextField1 {
        id: textFieldEspesorMaxBobina
        objectName: "espesorMax"
        supplierTab: "producto"
        Layout.minimumWidth: 150
        validator: DoubleValidator {
            bottom: 00
            top: 999
            decimals: 2
        }
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }

    Label {
        id: labelDiametroIntBobina
        text: qsTr("ID:")
    }
    ComboBox11 {
        id: comboBoxDiametroIntBobina
        objectName: "diametroIntBobina"
        supplierTab: "producto"
        toogleAllValues: false
    }
    SpacerH_20 {
    }
}




/*##^## Designer {
    D{i:0;height:600;width:1000}
}
 ##^##*/

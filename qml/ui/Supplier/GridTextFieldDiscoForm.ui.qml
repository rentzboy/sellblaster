import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import "../../components"

GridLayout {
    id: gridTextFieldDisco
    property alias textFieldDiametroMinDisco: textFieldDiametroMinDisco
    property alias textFieldDiametroMaxDisco: textFieldDiametroMaxDisco
    property alias textFieldEspesorMinDisco: textFieldEspesorMinDisco
    property alias textFieldEspesorMaxDisco: textFieldEspesorMaxDisco

    Label {
        id: labelDiametroMinDisco
        text: qsTr("⌀ min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldDiametroMinDisco
        objectName: "diametroMin"
        supplierTab: "producto"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        validator: RegExpValidator {
            regExp: /\d\d\d/
        }
    }
    SpacerH_20 {
    }
    Label {
        id: labelDiametroMaxDisco
        text: qsTr("⌀ max:")
        Layout.minimumWidth: 135
        //x: labelMaterial.x
    }
    TextField1 {
        id: textFieldDiametroMaxDisco
        objectName: "diametroMax"
        supplierTab: "producto"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        validator: RegExpValidator {
            regExp: /\d\d\d\d/
        }
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
        objectName: "espesorMin"
        supplierTab: "producto"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        validator: DoubleValidator {
            bottom: 00
            top: 99
        }
    }
    SpacerH_20 {
    }
    Label {
        id: labelEspesorMaxDisco
        text: qsTr("Espesor max:")
    }
    TextField1 {
        id: textFieldEspesorMaxDisco
        objectName: "espesorMax"
        supplierTab: "producto"
        Layout.preferredWidth: comboBoxTipo.width
        Layout.fillWidth: false
        validator: DoubleValidator {
            bottom: 00
            top: 999
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

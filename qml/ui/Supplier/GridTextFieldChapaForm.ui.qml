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

    Label {
        id: labelFormatoChapa
        text: qsTr("Formato:")
        Layout.minimumWidth: 135
    }
    ComboBox11 {
        id: comboBoxFormatoChapa
        objectName: "formatoChapa"
        supplierTab: "producto"
        toogleAllValues: false
        Layout.minimumWidth: 150
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
        supplierTab: "producto"
        Layout.minimumWidth: 150
        validator: RegExpValidator {
            regExp: /\d{0,2}[.]\d{0,3}|\d{0,2}/
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
        supplierTab: "producto"
        Layout.minimumWidth: 150
        validator: RegExpValidator {
            regExp: /\d{0,3}[.]\d{0,3}|\d{0,3}/
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

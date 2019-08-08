import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import "../../components"

GridLayout {
    id: gridTextFieldTubo
    property alias textFieldDiametroIntMinTubo: textFieldDiametroIntMinTubo
    property alias textFieldDiametroExtMinTubo: textFieldDiametroExtMinTubo
    property alias textFieldLargoMinTubo: textFieldLargoMinTubo
    property alias textFieldDiametroIntMaxTubo: textFieldDiametroIntMaxTubo
    property alias textFieldDiametroExtMaxTubo: textFieldDiametroExtMaxTubo
    property alias textFieldLargoMaxTubo: textFieldLargoMaxTubo

    Layout.topMargin: 10
    columnSpacing: 15
    rowSpacing: 15
    columns: 9
    clip: true
    visible: false

    Label {
        id: labelDiametroIntMinTubo
        text: qsTr("⌀ int min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldDiametroIntMinTubo
        objectName: "diametroIntMin"
        validator: IntValidator {
            bottom: 00
            top: 999
        }
    }
    SpacerH_20 {
    }
    Label {
        id: labelDiametroExtMinTubo
        text: qsTr("⌀ ext min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldDiametroExtMinTubo
        objectName: "diametroExtMin"
        validator: IntValidator {
            bottom: 00
            top: 999
        }
    }
    SpacerH_20 {
    }
    Label {
        id: labelLargoMinTubo
        text: qsTr("Largo min:")
        Layout.minimumWidth: 135
    }
    TextField1 {
        id: textFieldLargoMinTubo
        objectName: "largoMin"
        validator: IntValidator {
            bottom: 00
            top: 9999
        }
    }
    SpacerH_20 {
        Layout.fillWidth: true
    }

    Label {
        id: labelDiametroIntMaxTubo
        text: qsTr("⌀ int max:")
    }
    TextField1 {
        id: textFieldDiametroIntMaxTubo
        objectName: "diametroIntMax"
        validator: IntValidator {
            bottom: 00
            top: 999
        }
    }
    SpacerH_20 {
    }
    Label {
        id: labelDiametroExtMaxTubo
        text: qsTr("⌀ ext max:")
    }
    TextField1 {
        id: textFieldDiametroExtMaxTubo
        objectName: "diametroExtMax"
        validator: IntValidator {
            bottom: 00
            top: 9999
        }
    }
    SpacerH_20 {
    }
    Label {
        id: labelLargoMaxTubo
        text: qsTr("Largo max:")
    }
    TextField1 {
        id: textFieldLargoMaxTubo
        objectName: "largoMax"
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

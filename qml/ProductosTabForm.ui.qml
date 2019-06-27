import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.0
import "components"

Item {
    id: productosTab
    property alias buttonAceptar: buttonAceptar
    property alias buttonCancelar: buttonCancelar
    property alias buttonGuardar: buttonGuardar
    property alias comboBoxFormato: comboBoxFormato
    property alias comboBoxMaterial: comboBoxMaterial
    property alias comboBoxTratamiento: comboBoxTratamiento
    property alias comboBoxAleacion: comboBoxAleacion
    property alias comboBoxTemple: comboBoxTemple
    property alias textFieldEspesorMin: textFieldEspesorMin
    property alias textFieldLargoMin: textFieldLargoMin
    property alias comboBoxAcabado: comboBoxAcabado
    property alias textFieldEspesorMax: textFieldEspesorMax
    property alias textFieldAnchoMin: textFieldAnchoMin
    property alias textFieldAnchoMax: textFieldAnchoMax
    property alias textFieldLargoMax: textFieldLargoMax
    visible: true
    Rectangle {
        clip: true
        anchors.fill: parent
        border.color: "#bcb1b1"
    }

    GridLayout {
        columnSpacing: 15
        rowSpacing: 15
        rows: 3
        columns: 1
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 15

        RowLayout {
            //Row1: buttons
            id: row
            spacing: 15
            Button {
                id: buttonAceptar
                text: qsTr("Aceptar")
            }
            Button {
                id: buttonCancelar
                text: qsTr("Cancelar")
            }
            Button {
                id: buttonGuardar
                text: qsTr("Guardar")
            }
        }

        GroupBox {
            //Row 2: Datos generales
            id: groupBox1
            Layout.fillHeight: true
            Layout.fillWidth: true //que se adapte al tamaño de la ventana
            topPadding: 60 //asi se muetran los bordes Ok
            bottomPadding: 20 //asi se muetran los bordes Ok
            clip: true
            padding: 15
            title: qsTr("Datos generales")

            GridLayout {
                id: grid
                columnSpacing: 15
                rowSpacing: 15
                anchors.fill: parent
                rows: 4
                columns: 9
                clip: true

                Label {
                    id: labelFormato
                    text: qsTr("Formato:")
                    Layout.minimumWidth: 120 //Para alinearlo con Datos financieros
                }
                ComboBox1 {
                    id: comboBoxFormato
                    objectName: "formato"
                    Layout.fillWidth: true
                    Layout.minimumWidth: 150 //Solo hay que indicarlo en los elementos de la row #1
                    Layout.preferredHeight: textFieldEspesorMin.height
                }
                Item {
                    id: spacer1
                    width: 20
                }

                Label {
                    id: labelMaterial
                    text: qsTr("Material:")
                }
                ComboBox1 {
                    id: comboBoxMaterial
                    objectName: "material"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                    Layout.preferredHeight: textFieldEspesorMin.height
                }
                Item {
                    id: spacer2
                    width: 20
                }

                Label {
                    id: labelTratamiento
                    text: qsTr("Tratamiento:")
                }
                ComboBox1 {
                    id: comboBoxTratamiento
                    objectName: "tratamiento"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                    Layout.preferredHeight: textFieldEspesorMin.height
                }
                Item {
                    id: spacer3
                    width: 20
                    Layout.fillWidth: true
                }

                Label {
                    id: labelAleacion
                    text: qsTr("Aleación:")
                }
                ComboBox1 {
                    id: comboBoxAleacion
                    objectName: "aleacion"
                    Layout.fillWidth: true
                    Layout.preferredHeight: textFieldEspesorMin.height
                }
                Item {
                    id: spacer4
                    width: 20
                }

                Label {
                    id: labelTemple
                    text: qsTr("Temple:")
                }
                ComboBox1 {
                    id: comboBoxTemple
                    objectName: "temple"
                    width: 150
                    Layout.fillWidth: true
                    Layout.preferredHeight: textFieldEspesorMin.height
                }
                Item {
                    id: spacer5
                    width: 20
                }

                Label {
                    id: labelAcabado
                    text: qsTr("Acabado:")
                }
                ComboBox1 {
                    id: comboBoxAcabado
                    objectName: "acabado"
                    width: 150
                    Layout.fillWidth: true
                    Layout.preferredHeight: textFieldEspesorMin.height
                }
                Item {
                    id: spacer6
                    width: 20
                    Layout.fillWidth: true
                }

                Label {
                    id: labelEspesorMin
                    text: qsTr("Espesor min:")
                }
                TextField1 {
                    id: textFieldEspesorMin
                    objectName: "espesorMin"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer7
                    width: 20
                }

                Label {
                    id: labelLargoMin
                    text: qsTr("Largo min:")
                }
                TextField1 {
                    id: textFieldLargoMin
                    objectName: "largoMin"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer8
                    width: 20
                }

                Label {
                    id: labelAnchoMin
                    text: qsTr("Ancho min:")
                }
                TextField1 {
                    id: textFieldAnchoMin
                    objectName: "anchoMin"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer9
                    width: 20
                }

                Label {
                    id: labelEspesorMax
                    text: qsTr("Espesor max:")
                }
                TextField1 {
                    id: textFieldEspesorMax
                    objectName: "espesorMax"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer10
                    width: 20
                }

                Label {
                    id: labelLargoMax
                    text: qsTr("Largo max:")
                }
                TextField1 {
                    id: textFieldLargoMax
                    objectName: "largoMax"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer11
                    width: 20
                }

                Label {
                    id: labelAnchoMax
                    text: qsTr("Ancho max:")
                }
                TextField1 {
                    id: textFieldAnchoMax
                    objectName: "anchoMax"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer12
                    width: 20
                }
            }
        }

        GroupBox {
            //Row 3: Datos financieros
            id: groupBox2
            Layout.fillHeight: true
            Layout.fillWidth: true //que se adapte al tamaño de la ventana
            topPadding: 60 //asi se muetran los bordes Ok
            bottomPadding: 20 //asi se muetran los bordes Ok
            clip: true
            padding: 15
            title: qsTr("Datos financieros")

            GridLayout {
                //Datos financieros
                id: grid2
                columnSpacing: 15
                rowSpacing: 15
                anchors.fill: parent
                rows: 2
                columns: 9
                clip: true

                Label {
                    id: labelPago
                    text: qsTr("Forma pago:")
                    Layout.minimumWidth: 120
                }
                TextField1 {
                    id: textFieldPago
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer20
                    width: 20
                    Layout.fillWidth: true
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:1000}
}
 ##^##*/

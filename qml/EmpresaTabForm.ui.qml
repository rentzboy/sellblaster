import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.0
import "components"

Item {
    id: empresaTab
    property alias textFieldEmpresa: textFieldEmpresa
    property alias textFieldHolding: textFieldHolding
    property alias comboBoxActividad: comboBoxActividad
    property alias textFieldWeb: textFieldWeb
    property alias textFieldPanjiba: textFieldPanjiba
    property alias textFieldMaps: textFieldMaps
    property alias comboBoxPais: comboBoxPais
    property alias textFieldCiudad: textFieldCiudad
    property alias textFieldPostcode: textFieldPostcode
    property alias textFieldMoq: textFieldMoq
    property alias textFieldNotasEmpresa: textFieldNotasEmpresa
    property alias comboBoxFormaPago: comboBoxFormaPago
    property alias aceptarButton: aceptarButton
    property alias cancelarButton: cancelarButton
    property alias guardarButton: guardarButton

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
                id: aceptarButton
                text: qsTr("Aceptar")
            }
            Button {
                id: cancelarButton
                text: qsTr("Cancelar")
            }
            Button {
                id: guardarButton
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
                rows: 3
                columns: 9
                clip: true

                Label {
                    id: labelEmpresa
                    text: qsTr("Empresa:")
                    Layout.minimumWidth: 120 //Para alinearlo con Datos financieros
                }
                TextField {
                    id: textFieldEmpresa
                    Layout.minimumWidth: 150 //Solo hay que indicarlo en los elementos de la row #1
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer1
                    width: 20
                }

                Label {
                    id: labelHolding
                    text: qsTr("Holding:")
                }
                TextField {
                    id: textFieldHolding
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer2
                    width: 5
                }

                Label {
                    id: labelActividad
                    text: qsTr("Actividad:")
                }
                ComboBox {
                    id: comboBoxActividad
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Item {
                    id: spacer3
                    width: 20
                    Layout.fillWidth: true
                }

                Label {
                    id: labelWeb
                    text: qsTr("Web:")
                }
                TextField {
                    id: textFieldWeb
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer4
                    width: 20
                }

                Label {
                    id: labelPanjiba
                    text: qsTr("Panjiba:")
                }
                TextField {
                    id: textFieldPanjiba
                    width: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer5
                    width: 5
                }

                Label {
                    id: labelMaps
                    text: qsTr("G.Maps:")
                }
                TextField {
                    id: textFieldMaps
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer6
                    width: 20
                    Layout.fillWidth: true
                }

                Label {
                    id: labelPais
                    text: qsTr("Pais:")
                }
                ComboBox {
                    id: comboBoxPais
                    Layout.fillWidth: true
                    Layout.preferredHeight: textFieldEmpresa.height
                }
                Item {
                    id: spacer7
                    width: 20
                }

                Label {
                    id: labelCiudad
                    text: qsTr("Ciudad:")
                }
                TextField {
                    id: textFieldCiudad
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer8
                    width: 5
                }

                Label {
                    id: labelPostcode
                    text: qsTr("Postcode:")
                }
                TextField {
                    id: textFieldPostcode
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer9
                    width: 20
                    Layout.fillWidth: true
                }
                Label {
                    id: labelMoq
                    text: qsTr("MOQ:")
                }
                TextField {
                    id: textFieldMoq
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer10
                    width: 20
                }

                Label {
                    id: labelNotas
                    text: qsTr("Notas:")
                }
                TextArea {
                    id: textFieldNotasEmpresa
                    wrapMode: Text.WordWrap
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.columnSpan: 4
                }

                Item {
                    id: spacer11
                    width: 5
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
                ComboBox {
                    id: comboBoxFormaPago
                    Layout.preferredHeight: textFieldEmpresa.height
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                }
                Item {
                    id: spacer20
                    width: 5
                    Layout.fillWidth: true
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

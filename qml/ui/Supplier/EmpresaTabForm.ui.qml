import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import "../../components"

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
    property alias textAreaNotasEmpresa: textAreaNotasEmpresa
    property alias comboBoxFormaPago: comboBoxFormaPago
    property alias buttonAceptar: buttonAceptar
    property alias buttonCancelar: buttonCancelar
    property alias buttonGuardar: buttonGuardar

    visible: true
    Rectangle {
        clip: true
        anchors.fill: parent
        border.color: "#bcb1b1"
    }

    ColumnLayout {
        spacing: 15
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 15

        RowLayout {
            id: rowButtons
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

        RowLayout {
            id: rowDatosGenerales
            Layout.fillWidth: true

            GroupBox {
                //Row 2: Datos generales
                id: groupBox1
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
                    columns: 9
                    clip: true

                    Label {
                        id: labelEmpresa
                        text: qsTr("Empresa:")
                        Layout.minimumWidth: 130 //Para alinearlo con Datos financieros
                    }
                    TextField1 {
                        id: textFieldEmpresa
                        objectName: "empresa"
                        supplierTab: "empresa"
                        Layout.fillWidth: true
                        maximumLength: 100
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelHolding
                        text: qsTr("Holding:")
                    }
                    TextField1 {
                        id: textFieldHolding
                        objectName: "holding"
                        supplierTab: "empresa"
                        maximumLength: 100
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelActividad
                        text: qsTr("Actividad:")
                    }
                    ComboBox1 {
                        id: comboBoxActividad
                        objectName: "actividad"
                        supplierTab: "empresa"
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }

                    Label {
                        id: labelWeb
                        text: qsTr("Web:")
                    }
                    TextField1 {
                        id: textFieldWeb
                        objectName: "web"
                        supplierTab: "empresa"
                        inputMethodHints: Qt.ImhUrlCharactersOnly
                        maximumLength: 100
                    }
                    SpacerH_20 {
                    }

                    Label {
                        id: labelPanjiba
                        text: qsTr("Panjiba:")
                    }
                    TextField1 {
                        id: textFieldPanjiba
                        objectName: "panjiba"
                        supplierTab: "empresa"
                        inputMethodHints: Qt.ImhUrlCharactersOnly
                        maximumLength: 200
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelMaps
                        text: qsTr("G.Maps:")
                    }
                    TextField1 {
                        id: textFieldMaps
                        objectName: "maps"
                        supplierTab: "empresa"
                        inputMethodHints: Qt.ImhUrlCharactersOnly
                        maximumLength: 200
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }

                    Label {
                        id: labelPais
                        text: qsTr("Pais:")
                    }
                    ComboBox1 {
                        id: comboBoxPais
                        objectName: "pais"
                        supplierTab: "empresa"
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelCiudad
                        text: qsTr("Ciudad:")
                    }
                    TextField1 {
                        id: textFieldCiudad
                        objectName: "ciudad"
                        supplierTab: "empresa"
                        maximumLength: 100
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelPostcode
                        text: qsTr("Postcode:")
                    }
                    TextField1 {
                        id: textFieldPostcode
                        objectName: "postcode"
                        supplierTab: "empresa"
                        validator: IntValidator {
                            bottom: 00001
                            top: 99999
                        } //mucho mejor
                        inputMethodHints: Qt.ImhDigitsOnly
                        //maximumLength: 5
                        //inputMask: "99999"
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }
                    Label {
                        id: labelMoq
                        text: qsTr("MOQ:")
                    }
                    TextField1 {
                        id: textFieldMoq
                        objectName: "moq"
                        supplierTab: "empresa"
                        validator: IntValidator {
                            bottom: 00
                            top: 99
                        }
                        //inputMethodHints: Qt.ImhDigitsOnly
                        //inputMask: "00"
                    }
                    SpacerH_20 {
                    }

                    Label {
                        id: labelNotas
                        text: qsTr("Notas:")
                    }
                    TextArea1 {
                        id: textAreaNotasEmpresa
                        objectName: "notasEmpresa"
                        supplierTab: "empresa"
                        wrapMode: Text.WordWrap
                        Layout.fillHeight: false
                        Layout.columnSpan: 4
                        KeyNavigation.tab: comboBoxFormaPago
                        KeyNavigation.priority: KeyNavigation.BeforeItem
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }
                }
            }
        }

        RowLayout {
            id: rowDatosFinancieros
            Layout.fillWidth: true

            GroupBox {
                id: groupBoxDatosFinancieros
                topPadding: 60 //asi se muetran los bordes Ok
                bottomPadding: 20 //asi se muetran los bordes Ok
                Layout.fillWidth: true
                clip: true
                padding: 15
                title: qsTr("Datos financieros")

                GridLayout {
                    //Datos financieros
                    id: grid2
                    columnSpacing: 15
                    rowSpacing: 15
                    anchors.fill: parent
                    columns: 3
                    clip: true

                    Label {
                        id: labelPago
                        text: qsTr("Forma pago:")
                        Layout.minimumWidth: 130
                    }
                    ComboBox1 {
                        id: comboBoxFormaPago
                        objectName: "formaPago"
                        supplierTab: "empresa"
                    }
                    Item {
                        width: 5
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:1000}
}
 ##^##*/

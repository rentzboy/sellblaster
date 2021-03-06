import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import "../../components"

Item {
    id: productosTab
    property alias buttonAceptar: buttonAceptar
    property alias buttonCancelar: buttonCancelar
    property alias buttonGuardar: buttonGuardar
    property alias comboBoxTipo: comboBoxTipo
    property alias comboBoxMaterial: comboBoxMaterial
    property alias comboBoxSerie: comboBoxSerie
    property alias comboBoxAleacion: comboBoxAleacion
    property alias comboBoxTemple: comboBoxTemple
    property alias comboBoxAcabado: comboBoxAcabado
    property alias gridTextFieldBobina: gridTextFieldBobina
    property alias gridTextFieldChapa: gridTextFieldChapa
    property alias gridTextFieldBarra: gridTextFieldBarra
    property alias gridTextFieldTubo: gridTextFieldTubo
    property alias gridTextFieldDisco: gridTextFieldDisco
    property alias radioButtonAisi: radioButtonAisi
    property alias radioButtonWerkstoff: radioButtonWerkstoff
    property alias comboBoxSerieToogleAll: comboBoxSerie.toogleAllValues
    property alias comboBoxAleacionToogleAll: comboBoxAleacion.toogleAllValues
    property alias comboBoxTempleToogleAll: comboBoxTemple.toogleAllValues
    property alias comboBoxAcabadoToogleAll: comboBoxAcabado.toogleAllValues

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
            Layout.rightMargin: 20
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
            Pane {
                Layout.fillWidth: true
            }
            RadioButton {
                id: radioButtonWerkstoff
                objectName: "werkstoff"
                text: qsTr("Werkstoff")
                checked: true
            }
            RadioButton {
                id: radioButtonAisi
                objectName: "aisi"
                text: qsTr("AISI")
            }
        }
        RowLayout {
            id: rowProductos
            Layout.fillWidth: true

            GroupBox {
                id: groupBoxProductos
                Layout.fillWidth: true //que se adapte al tamaño de la ventana
                topPadding: 60 //asi se muetran los bordes Ok
                bottomPadding: 20 //asi se muetran los bordes Ok
                clip: true
                padding: 15
                title: qsTr("Datos productos")

                ColumnLayout {
                    id: columnProductos
                    Layout.fillWidth: true
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top

                    GridLayout {
                        id: gridComboBoxes
                        Layout.fillWidth: true
                        columnSpacing: 15
                        rowSpacing: 15
                        columns: 9
                        clip: true
                        visible: true

                        Label {
                            id: labelTipo
                            text: qsTr("Tipo:")
                            Layout.minimumWidth: 135
                        }
                        ComboBox1 {
                            id: comboBoxTipo
                            objectName: "tipo"
                            supplierTab: "producto"
                        }
                        SpacerH_20 {
                        }

                        Label {
                            id: labelMaterial
                            text: qsTr("Material:")
                            Layout.minimumWidth: 135
                        }
                        ComboBox1 {
                            id: comboBoxMaterial
                            objectName: "material"
                            supplierTab: "producto"
                        }
                        SpacerH_20 {
                        }

                        Label {
                            id: labelSerie
                            text: qsTr("Serie:")
                            Layout.minimumWidth: 135
                        }
                        ComboBox11 {
                            id: comboBoxSerie
                            objectName: "serie"
                            supplierTab: "producto"
                            toogleAllValues: false
                        }
                        SpacerH_20 {
                            Layout.fillWidth: true
                        }

                        Label {
                            id: labelAleacion
                            text: qsTr("Aleación:")
                        }
                        ComboBox11 {
                            id: comboBoxAleacion
                            objectName: "aleacion"
                            supplierTab: "producto"
                            toogleAllValues: false
                        }
                        SpacerH_20 {
                        }

                        Label {
                            id: labelTemple
                            text: qsTr("Temple:")
                        }
                        ComboBox11 {
                            id: comboBoxTemple
                            objectName: "temple"
                            supplierTab: "producto"
                            toogleAllValues: false
                        }
                        SpacerH_20 {
                        }

                        Label {
                            id: labelAcabado
                            text: qsTr("Acabado:")
                        }
                        ComboBox11 {
                            id: comboBoxAcabado
                            objectName: "acabado"
                            supplierTab: "producto"
                            toogleAllValues: false
                        }
                        SpacerH_20 {
                            Layout.fillWidth: true
                        }
                    }

                    GridTextFieldBobinaForm {
                        id: gridTextFieldBobina
                        Layout.fillWidth: true
                        Layout.topMargin: 10
                        columnSpacing: 15
                        rowSpacing: 15
                        columns: 9
                        clip: true
                    }
                    GridTextFieldChapaForm {
                        id: gridTextFieldChapa
                        Layout.fillWidth: true
                        Layout.topMargin: 10
                        columnSpacing: 15
                        rowSpacing: 15
                        columns: 9
                        clip: true
                    }

                    GridTextFieldBarraForm {
                        id: gridTextFieldBarra
                        Layout.fillWidth: true
                        Layout.topMargin: 10
                        columnSpacing: 15
                        rowSpacing: 15
                        columns: 6
                        clip: true
                    }

                    GridTextFieldTuboForm {
                        id: gridTextFieldTubo
                        Layout.fillWidth: true
                        Layout.topMargin: 10
                        columnSpacing: 15
                        rowSpacing: 15
                        columns: 9
                        clip: true
                    }

                    GridTextFieldDiscoForm {
                        id: gridTextFieldDisco
                        Layout.fillWidth: true
                        Layout.topMargin: 10
                        columnSpacing: 15
                        rowSpacing: 15
                        columns: 6
                        clip: true
                    }
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:1200}
}
 ##^##*/

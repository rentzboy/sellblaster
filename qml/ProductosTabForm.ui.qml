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
    property alias comboBoxSerie: comboBoxSerie
    property alias comboBoxAleacion: comboBoxAleacion
    property alias comboBoxTemple: comboBoxTemple
    property alias comboBoxAcabado: comboBoxAcabado
    property alias gridTextFieldBobina: gridTextFieldBobina
    property alias gridTextFieldChapa: gridTextFieldChapa
    property alias gridTextFieldBarra: gridTextFieldBarra
    property alias gridTextFieldTubo: gridTextFieldTubo
    property alias gridTextFieldDisco: gridTextFieldDisco

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
            id: rowProductos
            Layout.fillWidth: true

            GroupBox {
                id: groupBoxProductos
                Layout.fillWidth: true //que se adapte al tamaño de la ventana
                topPadding: 60 //asi se muetran los bordes Ok
                bottomPadding: 20 //asi se muetran los bordes Ok
                clip: true
                padding: 15
                title: qsTr("Productos")

                ColumnLayout {
                    id: columnProductos
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
                            id: labelFormato
                            text: qsTr("Formato:")
                            Layout.minimumWidth: 135
                        }
                        ComboBox1 {
                            id: comboBoxFormato
                            objectName: "formato"
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
                        }
                        SpacerH_20 {
                        }

                        Label {
                            id: labelSerie
                            text: qsTr("Serie:")
                            Layout.minimumWidth: 135
                        }
                        ComboBox1 {
                            id: comboBoxSerie
                            objectName: "serie"
                        }
                        SpacerH_20 {
                            Layout.fillWidth: true
                        }

                        Label {
                            id: labelAleacion
                            text: qsTr("Aleación:")
                        }
                        ComboBox1 {
                            id: comboBoxAleacion
                            objectName: "aleacion"
                        }
                        SpacerH_20 {
                        }

                        Label {
                            id: labelTemple
                            text: qsTr("Temple:")
                        }
                        ComboBox1 {
                            id: comboBoxTemple
                            objectName: "temple"
                        }
                        SpacerH_20 {
                        }

                        Label {
                            id: labelAcabado
                            text: qsTr("Acabado:")
                        }
                        ComboBox1 {
                            id: comboBoxAcabado
                            objectName: "acabado"
                        }
                        SpacerH_20 {
                            Layout.fillWidth: true
                        }
                    }

                    GridTextFieldBobina {
                        id: gridTextFieldBobina
                    }

                    GridTextFieldChapa {
                        id: gridTextFieldChapa
                    }

                    GridTextFieldBarra {
                        id: gridTextFieldBarra
                    }

                    GridTextFieldTubo {
                        id: gridTextFieldTubo
                    }

                    GridTextFieldDisco {
                        id: gridTextFieldDisco
                    }
                }
            }
        }
        RowLayout {
            id: rowServicios
            Layout.fillWidth: true

            GroupBox {
                //Row 3: Datos financieros
                id: groupBox2
                Layout.fillWidth: true //que se adapte al tamaño de la ventana
                topPadding: 60 //asi se muetran los bordes Ok
                bottomPadding: 20 //asi se muetran los bordes Ok
                clip: true
                padding: 15
                title: qsTr("Servicios")
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:1000}
}
 ##^##*/

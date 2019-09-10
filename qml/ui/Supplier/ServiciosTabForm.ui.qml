import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import "../../components"

Item {
    id: servicioTab

    property alias buttonAceptar: buttonAceptar
    property alias buttonCancelar: buttonCancelar
    property alias buttonGuardar: buttonGuardar
    property alias textFieldEspesorMin1: textFieldEspesorMin1
    property alias textFieldEspesorMin2: textFieldEspesorMin2
    property alias textFieldEspesorMin3: textFieldEspesorMin3
    property alias textFieldEspesorMax1: textFieldEspesorMax1
    property alias textFieldEspesorMax2: textFieldEspesorMax2
    property alias textFieldEspesorMax3: textFieldEspesorMax3
    property alias textFieldAnchoMin1: textFieldAnchoMin1
    property alias textFieldAnchoMin2: textFieldAnchoMin2
    property alias textFieldAnchoMin3: textFieldAnchoMin3
    property alias textFieldAnchoMax1: textFieldAnchoMax1
    property alias textFieldAnchoMax2: textFieldAnchoMax2
    property alias textFieldAnchoMax3: textFieldAnchoMax3
    property alias comboBoxServicios: comboBoxServicios
    property alias comboBoxServiciosToogleAll: comboBoxServicios.toogleAllValues
    property alias textFieldCatalogo: textFieldCatalogo

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
            id: rowServicios
            Layout.fillWidth: true

            GroupBox {
                id: groupBoxServicios
                topPadding: 60 //asi se muetran los bordes Ok
                bottomPadding: 20 //asi se muetran los bordes Ok
                Layout.fillWidth: true
                clip: true
                padding: 15
                title: qsTr("Datos servicios")

                GridLayout {
                    //Servicios
                    id: grid2
                    columnSpacing: 15
                    rowSpacing: 15
                    anchors.fill: parent
                    columns: 6
                    clip: true

                    Label {
                        id: labelServicios
                        text: qsTr("Servicios:")
                        Layout.minimumWidth: labelEspesorMin1.width
                    }
                    ComboBox11 {
                        id: comboBoxServicios
                        Layout.fillWidth: false
                        objectName: "servicio"
                        supplierTab: "servicio"
                        toogleAllValues: false
                        Layout.minimumWidth: spacerEspesorMax.x - textFieldEspesorMin1.x
                                             - grid2.columnSpacing
                        Layout.maximumWidth: spacerEspesorMax.x - textFieldEspesorMin1.x
                                             - grid2.columnSpacing
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }
                    Label {
                        id: labelServiciosCatalogo
                        text: qsTr("Catalogo:")
                        x: labelAnchoMin1.x
                        Layout.minimumWidth: labelAnchoMin1.width
                    }
                    TextField1 {
                        id: textFieldCatalogo
                        objectName: "catalogo"
                        supplierTab: "servicio"
                        Layout.minimumWidth: anchoMaxSpacer.x - textFieldAnchoMin1.x
                                             - grid2.columnSpacing
                        Layout.maximumWidth: anchoMaxSpacer.x - textFieldAnchoMin1.x
                                             - grid2.columnSpacing
                        maximumLength: 150
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }
                }
            }
        }

        RowLayout {
            id: rowDatosSlitting
            Layout.fillWidth: true

            GroupBox {
                //Row 2: Datos generales
                id: groupBox1
                Layout.fillWidth: true //que se adapte al tamaño de la ventana
                topPadding: 60 //asi se muetran los bordes Ok
                bottomPadding: 20 //asi se muetran los bordes Ok
                clip: true
                padding: 15
                title: qsTr("Datos slitting")

                GridLayout {
                    id: grid
                    columnSpacing: 15
                    rowSpacing: 15
                    anchors.fill: parent
                    columns: 12
                    clip: true

                    Label {
                        id: labelEspesorMin1
                        text: qsTr("Espesor Min:")
                    }
                    TextField1 {
                        id: textFieldEspesorMin1
                        objectName: "espesorMin1"
                        supplierTab: "servicio"
                        validator: RegExpValidator {
                            regExp: /\d{0,2}[.]\d{0,3}|\d{0,2}/
                        }
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelEspesorMax1
                        text: qsTr("Espesor Max:")
                    }
                    TextField1 {
                        id: textFieldEspesorMax1
                        objectName: "espesorMax1"
                        supplierTab: "servicio"
                        Layout.fillWidth: true
                        validator: RegExpValidator {
                            regExp: /\d{0,2}[.]\d{0,3}|\d{0,2}/
                        }
                    }
                    SpacerH_20 {
                        id: spacerEspesorMax
                    }
                    Label {
                        id: labelAnchoMin1
                        text: qsTr("Ancho min:")
                    }
                    TextField1 {
                        id: textFieldAnchoMin1
                        objectName: "anchoMin1"
                        supplierTab: "servicio"
                        validator: RegExpValidator {
                            regExp: /\d{0,3}/
                        }
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelAnchoMax1
                        text: qsTr("Ancho max:")
                    }
                    TextField1 {
                        id: textFieldAnchoMax1
                        objectName: "anchoMax1"
                        supplierTab: "servicio"
                        validator: RegExpValidator {
                            regExp: /\d{0,4}/
                        }
                    }
                    SpacerH_20 {
                        id: anchoMaxSpacer
                        Layout.fillWidth: true
                    }

                    Label {
                        id: labelEspesorMin2
                        text: qsTr("Espesor min:")
                    }
                    TextField1 {
                        id: textFieldEspesorMin2
                        objectName: "espesorMin2"
                        supplierTab: "servicio"
                        Layout.fillWidth: true
                        validator: RegExpValidator {
                            regExp: /\d{0,2}[.]\d{0,3}|\d{0,2}/
                        }
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelEspesorMax2
                        text: qsTr("Espesor max:")
                    }
                    TextField1 {
                        id: textFieldEspesorMax2
                        objectName: "espesorMax2"
                        supplierTab: "servicio"
                        Layout.fillWidth: true
                        validator: RegExpValidator {
                            regExp: /\d{0,2}[.]\d{0,3}|\d{0,2}/
                        }
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelAnchoMin2
                        text: qsTr("Ancho min:")
                    }
                    TextField1 {
                        id: textFieldAnchoMin2
                        objectName: "anchoMin2"
                        supplierTab: "servicio"
                        validator: RegExpValidator {
                            regExp: /\d{0,3}/
                        }
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelAnchoMax2
                        text: qsTr("Ancho max:")
                    }
                    TextField1 {
                        id: textFieldAnchoMax2
                        objectName: "anchoMax2"
                        supplierTab: "servicio"
                        validator: RegExpValidator {
                            regExp: /\d{0,4}/
                        }
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }

                    Label {
                        id: labelEspesorMin3
                        text: qsTr("Espesor min:")
                    }
                    TextField1 {
                        id: textFieldEspesorMin3
                        objectName: "espesorMin3"
                        supplierTab: "servicio"
                        Layout.fillWidth: true
                        validator: RegExpValidator {
                            regExp: /\d{0,2}[.]\d{0,3}|\d{0,2}/
                        }
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelEspesorMax3
                        text: qsTr("Espesor max:")
                    }
                    TextField1 {
                        id: textFieldEspesorMax3
                        objectName: "espesorMax3"
                        supplierTab: "servicio"
                        Layout.fillWidth: true
                        validator: RegExpValidator {
                            regExp: /\d{0,2}[.]\d{0,3}|\d{0,2}/
                        }
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelAnchoMin3
                        text: qsTr("Ancho min:")
                    }
                    TextField1 {
                        id: textFieldAnchoMin3
                        objectName: "anchoMin3"
                        supplierTab: "servicio"
                        validator: RegExpValidator {
                            regExp: /\d{0,3}/
                        }
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelAnchoMax3
                        text: qsTr("Ancho max:")
                    }
                    TextField1 {
                        id: textFieldAnchoMax3
                        objectName: "anchoMax3"
                        supplierTab: "servicio"
                        validator: RegExpValidator {
                            regExp: /\d{0,4}/
                        }
                    }
                    SpacerH_20 {
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

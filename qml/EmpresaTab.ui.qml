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
    visible: true

    Background {
        anchors.fill: parent
        color: "#fcfcfc"
    }

    GridLayout {
        columnSpacing: 15
        rowSpacing: 15
        rows: 3
        columns: 1
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20

        RowLayout {
            id: row
            spacing: 15
            Button {
                id: buttonAceptar
                text: qsTr("Aceptar")
                Material.background: Material.Orange
                font.capitalization: Font.Capitalize
            }
            Button {
                id: buttonCancelar
                text: qsTr("Cancelar")
                //Material.background: Material.Teal
                font.capitalization: Font.Capitalize
            }
            Button {
                id: buttonGuardar
                text: qsTr("Guardar")
                //Material.background: Material.Teal
                font.capitalization: Font.Capitalize
            }
        }

        GroupBox {
            id: groupBox1
            Layout.fillWidth: true
            clip: true
            padding: 15
            title: qsTr("Datos generales")
            background: Background {
                anchors.fill: parent
                border.color: "#ececec"
                color: "#f9f9f9"
            }

            GridLayout {
                id: grid
                columnSpacing: 10
                rowSpacing: 10
                anchors.fill: parent
                rows: 3
                columns: 9
                clip: true

                Label {
                    id: labelEmpresa
                    text: qsTr("Empresa:")
                    Layout.minimumWidth: 120
                }
                TextField {
                    id: textFieldEmpresa
                    width: 200
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
                    width: 200
                }
                Item {
                    id: spacer2
                    width: 20
                }

                Label {
                    id: labelActividad
                    text: qsTr("Actividad:")
                }
                ComboBox {
                    id: comboBoxActividad
                    implicitWidth: 200
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
                }
                Item {
                    id: spacer5
                    width: 20
                }

                Label {
                    id: labelMaps
                    text: qsTr("G.Maps:")
                }
                TextField {
                    id: textFieldMaps
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
                    implicitWidth: 200
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
                }
                Item {
                    id: spacer8
                    width: 20
                }

                Label {
                    id: labelPostcode
                    text: qsTr("Postcode:")
                }
                TextField {
                    id: textFieldPostcode
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
                    id: textFieldNotas
                    wrapMode: Text.WordWrap
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.rowSpan: 2
                    Layout.columnSpan: 4
                    background: Rectangle {
                    }
                }

                Item {
                    id: spacer11
                    width: 20
                    Layout.fillWidth: true
                }
            }
        }

        GroupBox {
            id: groupBox2
            Layout.fillWidth: true
            clip: true
            padding: 15
            title: qsTr("Datos financieros")
            background: Background {
                anchors.fill: parent
                border.color: "#ececec"
                color: "#f9f9f9"
            }

            GridLayout {
                id: grid2
                columnSpacing: 10
                rowSpacing: 10
                anchors.fill: parent
                rows: 2
                columns: 9
                clip: true

                Label {
                    id: labelPago
                    text: qsTr("Forma pago:")
                    Layout.minimumWidth: 120
                }
                TextField {
                    id: textFieldPago
                    width: 200
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
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

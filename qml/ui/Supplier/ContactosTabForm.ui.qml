import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.12
import "../../components"

Item {
    id: contactosTab
    property alias buttonAceptar: buttonAceptar
    property alias buttonCancelar: buttonCancelar
    property alias buttonGuardar: buttonGuardar
    property alias textFieldNombre: textFieldNombre
    property alias textFieldApellido: textFieldApellido
    property alias textFieldEmail: textFieldEmail
    property alias textFieldTelefono: textFieldTelefono
    property alias textFieldMovil: textFieldMovil
    property alias textAreaNotasContacto: textAreaNotasContacto
    property alias comboBoxArea: comboBoxArea
    property alias comboBoxPuesto: comboBoxPuesto
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
            //Row1: buttons
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
            id: rowContactos
            Layout.fillWidth: true

            GroupBox {
                //Row 2: Datos generales
                id: groupBox1
                Layout.fillWidth: true
                topPadding: 60 //asi se muetran los bordes Ok
                bottomPadding: 20 //asi se muetran los bordes Ok
                clip: true
                padding: 15
                title: qsTr("Contacto")

                GridLayout {
                    id: grid
                    columnSpacing: 15
                    rowSpacing: 15
                    anchors.fill: parent
                    rows: 3
                    columns: 9
                    clip: true

                    Label {
                        id: labelNombre
                        text: qsTr("Nombre:")
                        Layout.minimumWidth: 100 //Para alinearlo con Datos financieros
                    }
                    TextField1 {
                        id: textFieldNombre
                        objectName: "nombre"
                        supplierTab: "contacto"
                        maximumLength: 100
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelApellido
                        text: qsTr("Apellido:")
                    }
                    TextField1 {
                        id: textFieldApellido
                        objectName: "apellido"
                        supplierTab: "contacto"
                        maximumLength: 100
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelEmail
                        text: qsTr("Email:")
                    }
                    TextField1 {
                        id: textFieldEmail
                        objectName: "email"
                        supplierTab: "contacto"
                        inputMethodHints: Qt.ImhEmailCharactersOnly
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }

                    Label {
                        id: labelTelefono
                        text: qsTr("Telefono:")
                    }
                    TextField1 {
                        id: textFieldTelefono
                        objectName: "telefono"
                        supplierTab: "contacto"
                        inputMethodHints: Qt.ImhDialableCharactersOnly
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelMovil
                        text: qsTr("Movil:")
                    }
                    TextField1 {
                        id: textFieldMovil
                        objectName: "movil"
                        supplierTab: "contacto"
                        inputMethodHints: Qt.ImhDialableCharactersOnly
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelNotas
                        text: qsTr("Notas:")
                    }
                    TextArea1 {
                        id: textAreaNotasContacto
                        objectName: "notasContacto"
                        supplierTab: "contacto"
                        wrapMode: Text.WordWrap
                        Layout.fillHeight: false
                        KeyNavigation.tab: comboBoxArea
                        KeyNavigation.priority: KeyNavigation.BeforeItem
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }

                    Label {
                        id: labelArea
                        text: qsTr("Area:")
                    }
                    ComboBox1 {
                        id: comboBoxArea
                        objectName: "area"
                        supplierTab: "contacto"
                    }
                    SpacerH_20 {
                    }
                    Label {
                        id: labelPuesto
                        text: qsTr("Puesto:")
                    }
                    ComboBox1 {
                        id: comboBoxPuesto
                        objectName: "puesto"
                        supplierTab: "contacto"
                    }
                    SpacerH_20 {
                        Layout.fillWidth: true
                    }
                }
            }
        }

        RowLayout {
            id: rowContactos2
            Layout.fillWidth: true

            GroupBox {
                //Row 3: Datos financieros
                id: groupBox2
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
                        id: labelGarbage
                        text: qsTr("Garbage:")
                        Layout.minimumWidth: 100
                    }
                    TextField1 {
                        id: textFieldGarbage
                        objectName: "garbage"
                        supplierTab: "contacto"
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

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs.qml 1.0
import QtQuick.Controls.Material 2.0
import "components"

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
                rows: 3
                columns: 9
                clip: true

                Label {
                    id: labelNombre
                    text: qsTr("Nombre:")
                    Layout.minimumWidth: 120 //Para alinearlo con Datos financieros
                }
                TextField1 {
                    id: textFieldNombre
                    objectName: "nombre"
                    Layout.minimumWidth: 150 //Solo hay que indicarlo en los elementos de la row #1
                    Layout.fillWidth: true
                    maximumLength: 100
                }
                Item {
                    id: spacer1
                    width: 20
                }

                Label {
                    id: labelApellido
                    text: qsTr("Apellido:")
                }
                TextField1 {
                    id: textFieldApellido
                    objectName: "apellido"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                    maximumLength: 100
                }
                Item {
                    id: spacer2
                    width: 20
                }

                Label {
                    id: labelEmail
                    text: qsTr("Email:")
                }
                TextField1 {
                    id: textFieldEmail
                    objectName: "email"
                    Layout.minimumWidth: 150
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhEmailCharactersOnly
                }
                Item {
                    id: spacer3
                    width: 20
                    Layout.fillWidth: true
                }

                Label {
                    id: labelTelefono
                    text: qsTr("Telefono:")
                }
                TextField1 {
                    id: textFieldTelefono
                    objectName: "telefono"
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhDialableCharactersOnly
                }
                Item {
                    id: spacer4
                    width: 20
                }

                Label {
                    id: labelMovil
                    text: qsTr("Movil:")
                }
                TextField1 {
                    id: textFieldMovil
                    objectName: "movil"
                    width: 150
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhDialableCharactersOnly
                }
                Item {
                    id: spacer5
                    width: 20
                }

                Label {
                    id: labelNotas
                    text: qsTr("Notas:")
                }
                TextArea1 {
                    id: textAreaNotasContacto
                    objectName: "notasContacto"
                    wrapMode: Text.WordWrap
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    KeyNavigation.tab: comboBoxArea
                    KeyNavigation.priority: KeyNavigation.BeforeItem
                }
                Item {
                    id: spacer6
                    width: 20
                    Layout.fillWidth: true
                }

                Label {
                    id: labelArea
                    text: qsTr("Area:")
                }
                ComboBox1 {
                    id: comboBoxArea
                    objectName: "area"
                    Layout.fillWidth: true
                    Layout.preferredHeight: textFieldNombre.height
                }
                Item {
                    id: spacer7
                    width: 20
                }

                Label {
                    id: labelPuesto
                    text: qsTr("Puesto:")
                }
                ComboBox1 {
                    id: comboBoxPuesto
                    objectName: "puesto"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Item {
                    id: spacer8
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
                    id: labelGarbage
                    text: qsTr("Garbage:")
                    Layout.minimumWidth: 120
                }
                TextField1 {
                    id: textFieldGarbage
                    objectName: "garbage"
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

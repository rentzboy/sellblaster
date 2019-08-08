import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import MainClass 1.0
import SupplierClass 1.0

Window {
    id: newProveedorWindow
    visible: true
    minimumWidth: 1400 //menor que MainWindow
    minimumHeight: 600 //menow que MainWindow
    title: qsTr("Nuevo proveedor")

    BackgroundZ1 {
    }

    onClosing: onCloseQmlInstance()

    //QML handler for C++ signal
    Connections {
        target: SupplierType
        onCloseQmlInstance: onCloseQmlInstance()
    }

    //JS
    function onCloseQmlInstance() {
        console.log("Se ha llamado a onCloseQmlInstance() desde NewProveedor.qml")
        SupplierType.onCancelarButton()
    }

    Component.onCompleted: function setWindowPosition() {
        if (MainWindowType.windowSize.width > minimumWidth)
            x = ((MainWindowType.windowSize.width - minimumWidth) / 2)
                    + MainWindowType.windowPosition.x
        else
            x = 0
        if (MainWindowType.windowSize.height > minimumHeight)
            y = ((MainWindowType.windowSize.height - minimumHeight) / 2)
                    + MainWindowType.windowPosition.y
        else
            y = 0
    }

    NewProveedorForm {
        id: form
        anchors.fill: parent
        anchors.margins: 15
        focus: true
        bar.onCurrentIndexChanged: onBarIndexChanged(bar.currentItem.objectName)

        //Initial values
        property int contactosTabCounter: 1
        property int productosTabCounter: 1

        //Para cargar los comboBoxes 1 sola vez para cada pestaña
        function onBarIndexChanged(tab) {
            console.log("Se ha llamado a la función onBarIndexChanged(" + tab + ")")
            if (tab === "empresa") {

                //Se llama desde el constructor
            } else if (contactosTabCounter === 1 && tab === "contactos") {
                SupplierType.fillComboBoxesFromDb(tab)
                contactosTabCounter--
            } else if (productosTabCounter === 1 && tab === "productos") {
                SupplierType.fillComboBoxesFromDb(tab)
                productosTabCounter--
            }
        }

        Keys.onPressed: {
            //Select / Unselect all checkBoxes
            if(event.key === Qt.Key_F12) {
                if(productosTab.comboBoxSerie.activeFocus) {
                SupplierType.toogleAllValues("serie")
                event.accepted = true
                }
                else if(productosTab.comboBoxAleacion.activeFocus) {
                    SupplierType.toogleAllValues("aleacion")
                    event.accepted = true
                    }
                else if(productosTab.comboBoxTemple.activeFocus) {
                    SupplierType.toogleAllValues("temple")
                    event.accepted = true
                    }
                else if(productosTab.comboBoxAcabado.activeFocus) {
                    SupplierType.toogleAllValues("acabado")
                    event.accepted = true
                    }
                else if(productosTab.gridTextFieldBobina.comboBoxAnchoBobina.activeFocus) {
                    SupplierType.toogleAllValues("anchoBobina")
                    event.accepted = true
                    }
                else if(productosTab.gridTextFieldBobina.comboBoxDiametroIntBobina.activeFocus) {
                    SupplierType.toogleAllValues("diametroIntBobina")
                    event.accepted = true
                    }
                else if(productosTab.gridTextFieldChapa.comboBoxFormatoChapa.activeFocus) {
                    SupplierType.toogleAllValues("formatoChapa")
                    event.accepted = true
                    }
            }
            //Moverse entre las pestañas Empresa / Contactos / Productos / ....
            if (event.key === Qt.Key_PageUp) {
                if (bar.currentIndex === 0) {
                    event.accepted = true
                } else {
                    bar.currentIndex--
                    event.accepted = true
                }
            } else if (event.key === Qt.Key_PageDown) {
                if (bar.currentIndex === bar.count) {
                    event.accepted = true
                } else {
                    bar.currentIndex++
                    event.accepted = true
                }
            } else if (event.key === Qt.Key_Return
                       && event.modifiers === Qt.ControlModifier) {
                console.log("Key logger: Crtl+Enter")
                SupplierType.onAceptarButton(bar.currentItem.objectName)
            } else if (event.key === Qt.Key_G
                       && event.modifiers === Qt.ControlModifier) {
                console.log("Key logger: Crtl+G")
                SupplierType.onGuardarButton(bar.currentItem.objectName)
            } else if (event.key === Qt.Key_Escape) {
                console.log("Key logger: Crtl+Esc")
                SupplierType.onCancelarButton()
            }
        }
    }
}




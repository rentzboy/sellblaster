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
    minimumHeight: 550 //menor que MainWindow
    title: qsTr("Nuevo proveedor")
    //flags: Qt.Window | Qt.Popup --> no se muestra  (en cambio desde Gammaray si funciona)

    BackgroundZ1 {
    }
    //Calling QML method from C++ signal using standard syntax (onSignalName)
    //No se puede conectar directamente un signal de C++ a un handler en QML para los C++ Singleton (Bug)
    Connections {
        target: SupplierType
        onClosingQmlInstance: function () {
            console.log("onClosingQmlInstance ..........")
            close () //call destroy() ???
        }
    }

    /* Component.onCompleted: function setWindowPosition() {
      >>> NO SE PUEDE ACTIVAR pues utiliza el qml-singleton MainWindowType,
      por lo que destruiría nuestra instancia de MainWindowType, al delete el engine
      que ha cargado este archivo (NewProveedor.qml), y nos hace falta en MainWindow.qml !!!

        //set window position
        //console.log("Call to ---> setWindowPosition()")
        if (MainWindowType.windowSize.width > minimumWidth) {
            x = ((MainWindowType.windowSize.width - minimumWidth) / 2)
                    + MainWindowType.windowPosition.x
        }
        else {
            x = 0
        }
        if (MainWindowType.windowSize.height > minimumHeight) {
            y = ((MainWindowType.windowSize.height - minimumHeight) / 2)
                    + MainWindowType.windowPosition.y
        }
        else {
            y = 0
        }
    } */

    //JS

    NewProveedorForm {
        id: form
        anchors.fill: parent
        anchors.margins: 15
        focus: true
        bar.onCurrentIndexChanged: onBarIndexChanged(bar.currentItem.objectName)

        //Initial values
        property int contactosTabCounter: 1
        property int productosTabCounter: 1
        property int serviciosTabCounter: 1

        function onBarIndexChanged(tab) {
            //Para cargar los comboBoxes 1 sola vez para cada pestaña
            console.log("Se ha llamado a la función onBarIndexChanged(" + tab + ")")
            if (tab === "empresa") {
                //Se llama desde el constructor
            } else if (contactosTabCounter === 1 && tab === "contacto") {
                SupplierType.fillComboBoxesFromDb(tab)
                contactosTabCounter--
            } else if (productosTabCounter === 1 && tab === "producto") {
                productosTab.state = "reset" //Sino muestra state=bobina
                SupplierType.fillComboBoxesFromDb(tab)
                productosTabCounter--
            } else if (serviciosTabCounter === 1 && tab === "servicio") {
                SupplierType.fillComboBoxesFromDb(tab)
                serviciosTabCounter--
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
                //console.log("Key logger: Crtl+Enter")
                SupplierType.onAceptarButton(bar.currentItem.objectName)
                console.log("Key logger: " + bar.currentItem.objectName)
            } else if (event.key === Qt.Key_G
                       && event.modifiers === Qt.ControlModifier) {
                //console.log("Key logger: Crtl+G")
                SupplierType.onGuardarButton(bar.currentItem.objectName)
            } else if (event.key === Qt.Key_Escape) {
                //console.log("Key logger: Esc")
                SupplierType.onCancelarButton()
            }
        }
    }
}




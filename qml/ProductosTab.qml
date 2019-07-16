import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0
import "../js/supplier.js" as Supplier

ProductosTabForm {
    id: form
    objectName: "ProductosTabForm"

    //States
    states: [
        State {
            name: "bobina"
            PropertyChanges {
                target: gridTextFieldChapa
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldBobina
                visible: true
            }
            PropertyChanges {
                target: gridTextFieldBarra
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldTubo
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldDisco
                visible: false
            }
        },
        State {
            name: "chapa"
            PropertyChanges {
                target: gridTextFieldChapa
                visible: true
            }
            PropertyChanges {
                target: gridTextFieldBobina
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldBarra
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldTubo
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldDisco
                visible: false
            }
        },
        State {
            name: "barra"
            PropertyChanges {
                target: gridTextFieldChapa
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldBobina
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldBarra
                visible: true
            }
            PropertyChanges {
                target: gridTextFieldTubo
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldDisco
                visible: false
            }
        },
        State {
            name: "tubo"
            PropertyChanges {
                target: gridTextFieldChapa
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldBobina
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldBarra
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldTubo
                visible: true
            }
            PropertyChanges {
                target: gridTextFieldDisco
                visible: false
            }
        },
        State {
            name: "disco"
            PropertyChanges {
                target: gridTextFieldChapa
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldBobina
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldBarra
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldTubo
                visible: false
            }
            PropertyChanges {
                target: gridTextFieldDisco
                visible: true
            }
        }
    ]

    //TextFields

    //ComboBoxes
    comboBoxTipo.onDisplayTextChanged: onTipoComboBoxChanged()

    comboBoxTipo.model: SupplierType.tipoList
    comboBoxMaterial.model: SupplierType.materialList
    comboBoxSerie.model: SupplierType.serieList
    comboBoxAleacion.model: SupplierType.aleacionList
    comboBoxTemple.model: SupplierType.templeList
    comboBoxAcabado.model: SupplierType.acabadoList

    //Buttons
    buttonAceptar.onClicked: SupplierType.onAceptarButton("productos")
    buttonCancelar.onClicked: SupplierType.onCancelarButton()
    buttonGuardar.onClicked: SupplierType.onGuardarButton("productos")

    //JS
    function onTipoComboBoxChanged() {
        console.log("currentText: " + comboBoxTipo.displayText
                    + ", currentIndex: " + comboBoxTipo.currentIndex)

        //Customization
        switch (comboBoxTipo.displayText) {
        case "Bobina":
            state = "bobina"
            break
        case "Chapa":
            state = "chapa"
            break
        case "Barra":
            state = "barra"
            break
        case "Tubo":
            state = "tubo"
            break
        case "Plancha":
            state = "chapa"
            break
        case "Disco":
            state = "disco"
            break
        case "Pletina":
            state = "pletina"
            break
        default:

        }
    }

    //SLOTS
    function onClearProductosFields(tab) {
        //hay que definirla para cada pestaña; se llama desde C++
        console.log("Se ha llamado a la función onClearProductosFields(" + tab + ")")
        //PENDING -no se que campos borrar todavía-
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:1000}D{i:18;autoSize:true;height:480;width:1000}
}
 ##^##*/


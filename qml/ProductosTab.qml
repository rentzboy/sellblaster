import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import SupplierClass 1.0
import "components"
import "../js/supplier.js" as Supplier

ProductosTabForm {
    id: form
    objectName: "ProductosTabForm"
    property int counter: 0

    //TextFields

    //RadioButtons
    radioButtonAisi.onClicked: onRadioButtonClicked(radioButtonAisi.objectName)
    radioButtonWerkstoff.onClicked: onRadioButtonClicked(radioButtonWerkstoff.objectName)

    //ComboBoxes
    comboBoxTipo.onDisplayTextChanged: onTipoComboBoxChanged()

    comboBoxSerieToogleAll: SupplierType.toogleValue.serie
    comboBoxAleacionToogleAll: SupplierType.toogleValue.aleacion
    comboBoxTempleToogleAll: SupplierType.toogleValue.temple
    comboBoxAcabadoToogleAll: SupplierType.toogleValue.acabado
    gridTextFieldBobina.comboBoxAnchoBobinaToogleAll: SupplierType.toogleValue.anchoBobina
    gridTextFieldBobina.comboBoxDiametroIntToogleAll: SupplierType.toogleValue.diametroIntBobina
    gridTextFieldChapa.comboBoxFormatoChapaToogleAll: SupplierType.toogleValue.formatoChapa

    comboBoxTipo.model: SupplierType.tipoList
    comboBoxMaterial.model: SupplierType.materialList
    comboBoxSerie.model: SupplierType.serieList
    comboBoxAleacion.model: SupplierType.aleacionList
    comboBoxTemple.model: SupplierType.templeList
    comboBoxAcabado.model: SupplierType.acabadoList

    gridTextFieldBobina.comboBoxAnchoBobina.model: SupplierType.formatoList //comparten el mismo
    gridTextFieldChapa.comboBoxFormatoChapa.model: SupplierType.formatoList //comparten el mismo
    gridTextFieldBobina.comboBoxDiametroIntBobina.model: SupplierType.idBobinaList

    //Buttons
    buttonAceptar.onClicked: SupplierType.onAceptarButton("productos")
    buttonCancelar.onClicked: SupplierType.onCancelarButton()
    buttonGuardar.onClicked: SupplierType.onGuardarButton("productos")

    //States
    states: [
        State {
            name: "reset"
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
                visible: false
            }
        },
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

    //JS
    function onTipoComboBoxChanged() {
        //console.log("currentText: " + comboBoxTipo.displayText + ", currentIndex: " + comboBoxTipo.currentIndex)

        //Para que se muestre el state=reset al cargar la 1era vez ProductosTab
        counter++
        if(counter === 2) {
            state = "reset"
            return
        }

        //Customization
        switch (comboBoxTipo.displayText) {
        case "Inicio":
            state = "reset"
            break
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
    function onRadioButtonClicked(objectName) {
        //console.log("onRadioButtonClicked: (" + objectName + ")")
        SupplierType.onRelatedFieldUpdated(objectName);
    }

    //SLOTS
    function onClearFormFields(tab) {
        //hay que definirla para cada pestaña; se llama desde C++
        console.log("Se ha llamado a la función onClearProductosFields(" + tab + ")")
        //PENDING -no se que campos borrar todavía-
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

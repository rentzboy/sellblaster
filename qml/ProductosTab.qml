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
    gridTextFieldBobina.textFieldEspesorMinBobina.text: SupplierType.productoTabField.espesorMin
    gridTextFieldBobina.textFieldEspesorMaxBobina.text: SupplierType.productoTabField.espesorMax
    gridTextFieldChapa.textFieldEspesorMinChapa.text: SupplierType.productoTabField.espesorMin
    gridTextFieldChapa.textFieldEspesorMaxChapa.text: SupplierType.productoTabField.espesorMax
    gridTextFieldBarra.textFieldDiametroMinBarra.text: SupplierType.productoTabField.diametroMin
    gridTextFieldBarra.textFieldDiametroMaxBarra.text: SupplierType.productoTabField.diametroMax
    gridTextFieldBarra.textFieldLargoMinBarra.text: SupplierType.productoTabField.largoMin
    gridTextFieldBarra.textFieldLargoMaxBarra.text: SupplierType.productoTabField.largoMax
    gridTextFieldTubo.textFieldDiametroIntMinTubo.text: SupplierType.productoTabField.diametroIntMin
    gridTextFieldTubo.textFieldDiametroIntMaxTubo.text: SupplierType.productoTabField.diametroIntMax
    gridTextFieldTubo.textFieldDiametroExtMinTubo.text: SupplierType.productoTabField.diametroExtMin
    gridTextFieldTubo.textFieldDiametroExtMaxTubo.text: SupplierType.productoTabField.diametroExtMax
    gridTextFieldTubo.textFieldLargoMinTubo.text: SupplierType.productoTabField.largoMin
    gridTextFieldTubo.textFieldLargoMaxTubo.text: SupplierType.productoTabField.largoMax
    gridTextFieldDisco.textFieldEspesorMinDisco.text: SupplierType.productoTabField.espesorMin
    gridTextFieldDisco.textFieldEspesorMaxDisco.text: SupplierType.productoTabField.espesorMax
    gridTextFieldDisco.textFieldDiametroMinDisco.text: SupplierType.productoTabField.diametroMin
    gridTextFieldDisco.textFieldDiametroMaxDisco.text: SupplierType.productoTabField.diametroMax

    //RadioButtons
    radioButtonAisi.onClicked: Supplier.onRadioButtonClicked(radioButtonAisi.objectName)
    radioButtonWerkstoff.onClicked: Supplier.onRadioButtonClicked(radioButtonWerkstoff.objectName)

    //ComboBoxes
    comboBoxTipo.onCurrentTextChanged: Supplier.onTipoComboBoxChanged(comboBoxTipo.currentText) //Update States

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
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

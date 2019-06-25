import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0
import "supplier.js" as Supplier

ProductosTabForm {
    id: form
    objectName: "ProductosTabForm"

    //TextFields
    textFieldLargoMin.onEditingFinished: Supplier.textValueToBackEnd(
                                             "largoMin", textFieldNombre.text)
    textFieldLargoMax.onEditingFinished: Supplier.textValueToBackEnd(
                                             "largoMax", textFieldNombre.text)
    textFieldEspesorMin.onEditingFinished: Supplier.textValueToBackEnd(
                                               "espesorMin",
                                               textFieldNombre.text)
    textFieldEspesorMax.onEditingFinished: Supplier.textValueToBackEnd(
                                               "espesorMax",
                                               textFieldNombre.text)
    textFieldAnchoMin.onEditingFinished: Supplier.textValueToBackEnd(
                                             "anchoMin", textFieldNombre.text)
    textFieldAnchoMax.onEditingFinished: Supplier.textValueToBackEnd(
                                             "anchoMax", textFieldNombre.text)

    //ComboBoxes
    //comboBoxFormato.currentIndex: -1 => el model se carga a posteriori
    comboBoxFormato.model: SupplierClass.formatoList
    comboBoxFormato.onModelChanged: Supplier.initializationComboBoxIndex(
                                        "comboBoxFormato")
    comboBoxFormato.onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(
                                               "formato",
                                               comboBoxFormato.currentIndex)
    comboBoxMaterial.model: SupplierClass.materialList
    comboBoxMaterial.onModelChanged: Supplier.initializationComboBoxIndex(
                                         "comboBoxMaterial")
    comboBoxMaterial.onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(
                                                "material",
                                                comboBoxMaterial.currentIndex)
    comboBoxTratamiento.model: SupplierClass.formatoList
    comboBoxTratamiento.onModelChanged: Supplier.initializationComboBoxIndex(
                                            "comboBoxTratamiento")
    comboBoxTratamiento.onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(
                                                   "tratamiento",
                                                   comboBoxTratamiento.currentIndex)
    comboBoxAleacion.model: SupplierClass.aleacionList
    comboBoxAleacion.onModelChanged: Supplier.initializationComboBoxIndex(
                                         "comboBoxAleacion")
    comboBoxAleacion.onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(
                                                "aleacion",
                                                comboBoxAleacion.currentIndex)
    comboBoxTemple.model: SupplierClass.templeList
    comboBoxTemple.onModelChanged: Supplier.initializationComboBoxIndex(
                                       "comboBoxTemple")
    comboBoxTemple.onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(
                                              "temple",
                                              comboBoxTemple.currentIndex)
    comboBoxAcabado.model: SupplierClass.acabadoList
    comboBoxAcabado.onModelChanged: Supplier.initializationComboBoxIndex(
                                        "comboBoxAcabado")
    comboBoxAcabado.onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(
                                               "acabado",
                                               comboBoxAcabado.currentIndex)

    //Buttons
    buttonAceptar.onClicked: SupplierClass.onAceptarButton("contacto")
    buttonCancelar.onClicked: close()
    buttonGuardar.onClicked: SupplierClass.onGuardarButton("contacto")

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }
    function onClearProductosFields(tab) {
        //hay que definirla para cada pestaña
        console.log("Se ha llamado a la función onClearProductosFields(" + tab + ")")
        textFieldNombre.clear()
        textFieldApellido.clear()
        textFieldEmail.clear()
        textFieldTelefono.clear()
        textFieldMovil.clear()
        textAreaNotasContacto.clear()
        comboBoxArea.currentIndex = -1
        comboBoxPuesto.currentIndex = -1
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


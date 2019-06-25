import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0
import "supplier.js" as Supplier

EmpresaTabForm {
    id: form
    objectName: "EmpresaTabForm"

    //TextFields
    textFieldEmpresa.onEditingFinished: Supplier.textValueToBackEnd(
                                            "empresa", textFieldEmpresa.text)
    textFieldHolding.onEditingFinished: Supplier.textValueToBackEnd(
                                            "holding", textFieldHolding.text)
    textFieldWeb.onEditingFinished: Supplier.textValueToBackEnd(
                                        "web", textFieldWeb.text)
    textFieldPanjiba.onEditingFinished: Supplier.textValueToBackEnd(
                                            "panjiba", textFieldPanjiba.text)
    textFieldMaps.onEditingFinished: Supplier.textValueToBackEnd(
                                         "maps", textFieldMaps.text)
    textFieldCiudad.onEditingFinished: Supplier.textValueToBackEnd(
                                           "ciudad", textFieldCiudad.text)
    textFieldPostcode.onEditingFinished: Supplier.textValueToBackEnd(
                                             "postcode", textFieldPostcode.text)
    textFieldMoq.onEditingFinished: Supplier.textValueToBackEnd(
                                        "moq", textFieldMoq.text)
    textAreaNotasEmpresa.onEditingFinished: Supplier.textValueToBackEnd(
                                                "notasEmpresa",
                                                textAreaNotasEmpresa.text)

    //ComboBoxes
    comboBoxPais.currentIndex: -1
    comboBoxPais.model: SupplierClass.paisList
    comboBoxPais.onCurrentIndexChanged: Supplier.comboBoxValueToBackEnd(
                                            "pais", comboBoxPais.currentIndex)

    comboBoxActividad.currentIndex: -1
    comboBoxActividad.model: SupplierClass.actividadList
    comboBoxActividad.onCurrentIndexChanged: Supplier.comboBoxValueToBackEnd(
                                                 "actividad",
                                                 comboBoxActividad.currentIndex)

    comboBoxFormaPago.currentIndex: -1
    comboBoxFormaPago.model: SupplierClass.formaPagoList
    comboBoxFormaPago.onCurrentIndexChanged: Supplier.comboBoxValueToBackEnd(
                                                 "formaPago",
                                                 comboBoxFormaPago.currentIndex)

    //Buttons
    buttonAceptar.onClicked: SupplierClass.onAceptarButton("empresa")
    buttonCancelar.onClicked: close()
    buttonGuardar.onClicked: SupplierClass.onGuardarButton("empresa")

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }
    function onClearFormFields(tab) {
        //hay que definirla para cada pestaña
        console.log("Se ha llamado a la función onClearFormFields(" + tab + ")")
        if (tab === "empresa") {
            textFieldEmpresa.clear()
            textFieldHolding.clear()
            comboBoxPais.currentIndex = -1
            textFieldWeb.clear()
            textFieldPanjiba.clear()
            textFieldMaps.clear()
            comboBoxPais.currentIndex = -1
            textFieldCiudad.clear()
            textFieldPostcode.clear()
            textFieldMoq.clear()
            textAreaNotasEmpresa.clear()
            comboBoxFormaPago.currentIndex = -1
        } else if (tab === "contacto") {
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
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


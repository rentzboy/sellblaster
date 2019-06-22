import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0

EmpresaTabForm {
    id: form

    //TextFields
    textFieldEmpresa.onEditingFinished: textValueToBackEnd(
                                            "empresa", textFieldEmpresa.text)
    textFieldHolding.onEditingFinished: textValueToBackEnd(
                                            "holding", textFieldHolding.text)
    textFieldWeb.onEditingFinished: textValueToBackEnd("web", textFieldWeb.text)
    textFieldPanjiba.onEditingFinished: textValueToBackEnd(
                                            "panjiba", textFieldPanjiba.text)
    textFieldMaps.onEditingFinished: textValueToBackEnd("maps",
                                                        textFieldMaps.text)
    textFieldCiudad.onEditingFinished: textValueToBackEnd("ciudad",
                                                          textFieldCiudad.text)
    textFieldPostcode.onEditingFinished: textValueToBackEnd(
                                             "postcode", textFieldPostcode.text)
    textFieldMoq.onEditingFinished: textValueToBackEnd("moq", textFieldMoq.text)
    textAreaNotasEmpresa.onEditingFinished: textValueToBackEnd(
                                                "notasEmpresa",
                                                textAreaNotasEmpresa.text)

    //ComboBoxes
    comboBoxPais.currentIndex: -1
    comboBoxPais.model: SupplierClass.paisList
    comboBoxPais.onCurrentIndexChanged: comboBoxValueToBackEnd(
                                            "pais", comboBoxPais.currentIndex)

    comboBoxActividad.currentIndex: -1
    comboBoxActividad.model: SupplierClass.actividadList
    comboBoxActividad.onCurrentIndexChanged: comboBoxValueToBackEnd(
                                                 "actividad",
                                                 comboBoxActividad.currentIndex)

    comboBoxFormaPago.currentIndex: -1
    comboBoxFormaPago.model: SupplierClass.formaPagoList
    comboBoxFormaPago.onCurrentIndexChanged: comboBoxValueToBackEnd(
                                                 "formaPago",
                                                 comboBoxFormaPago.currentIndex)

    //Buttons
    buttonAceptar.onClicked: SupplierClass.onAceptarButton("empresa")
    buttonCancelar.onClicked: close()
    buttonGuardar.onClicked: SupplierClass.onGuardarButton("empresa")

    //JS FUNCTIONS
    function textValueToBackEnd(field, txt) {
        SupplierClass.textValueToBackEnd(field, txt)
    }

    function comboBoxValueToBackEnd(field, index) {
        var txt
        switch (field) {
        case "pais":
            txt = SupplierClass.paisList[index]
            break
        case "actividad":
            txt = SupplierClass.actividadList[index]
            break
        case "formaPago":
            txt = SupplierClass.formaPagoList[index]
            break
        default:

        }
        textValueToBackEnd(field, txt)
    }

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }

    function resetFormFields() {
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
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


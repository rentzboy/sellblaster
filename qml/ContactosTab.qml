import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0
import "supplier.js" as Supplier

ContactosTabForm {
    id: contactosForm
    objectName: "ContactosTabForm"

    //TextFields
    textFieldNombre.onEditingFinished: textValueToBackEnd("nombre",
                                                          textFieldNombre.text)
    textFieldApellido.onEditingFinished: textValueToBackEnd(
                                             "apellido", textFieldApellido.text)
    textFieldEmail.onEditingFinished: textValueToBackEnd("email",
                                                         textFieldEmail.text)
    textFieldTelefono.onEditingFinished: textValueToBackEnd(
                                             "telefono", textFieldTelefono.text)
    textFieldMovil.onEditingFinished: textValueToBackEnd("movil",
                                                         textFieldMovil.text)
    textAreaNotasContacto.onEditingFinished: textValueToBackEnd(
                                                 "notasContacto",
                                                 textAreaNotasContacto.text)

    //ComboBoxes
    //comboBoxArea.currentIndex: -1 => el model se carga a posteriori
    comboBoxArea.model: SupplierClass.areaList
    comboBoxArea.onModelChanged: Supplier.initializationComboBoxIndex(
                                     "comboBoxArea")
    comboBoxArea.onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(
                                            "area", comboBoxArea.currentIndex)

    //comboBoxPuesto.currentIndex: -1 => el model se carga a posteriori
    comboBoxPuesto.model: SupplierClass.puestoList
    comboBoxPuesto.onModelChanged: Supplier.initializationComboBoxIndex(
                                       "comboBoxPuesto")
    comboBoxPuesto.onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(
                                              "puesto",
                                              comboBoxPuesto.currentIndex)

    //Buttons
    buttonAceptar.onClicked: SupplierClass.onAceptarButton("contacto")
    buttonCancelar.onClicked: close()
    buttonGuardar.onClicked: SupplierClass.onGuardarButton("contacto")

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }
    function onClearContactosFields(tab) {
        //hay que definirla para cada pestaña
        console.log("Se ha llamado a la función onClearContactosFields(" + tab + ")")
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


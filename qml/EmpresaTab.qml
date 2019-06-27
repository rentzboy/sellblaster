import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0
import "../js/supplier.js" as Supplier

EmpresaTabForm {
    id: form
    objectName: "EmpresaTabForm"

    //TextFields (ver TextField1.qml)

    //ComboBoxes
    comboBoxPais.model: SupplierClass.paisList
    comboBoxActividad.model: SupplierClass.actividadList
    comboBoxFormaPago.model: SupplierClass.formaPagoList

    //Buttons
    buttonAceptar.onClicked: SupplierClass.onAceptarButton("empresa")
    buttonCancelar.onClicked: close()
    buttonGuardar.onClicked: SupplierClass.onGuardarButton("empresa")

    //SLOTS
    function onClearFormFields(tab) {
        //hay que definirla para cada pestaña; se llama desde C++
        console.log("Se ha llamado a la función onClearFormFields(" + tab + ")")
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


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
    comboBoxPais.model: SupplierType.paisList
    comboBoxActividad.model: SupplierType.actividadList
    comboBoxFormaPago.model: SupplierType.formaPagoList

    //Buttons
    buttonAceptar.onClicked: SupplierType.onAceptarButton("empresa")
    buttonCancelar.onClicked: SupplierType.onCancelarButton()
    buttonGuardar.onClicked: SupplierType.onGuardarButton("empresa")

    Connections {
        target: SupplierType
        onClearFormFields: onClearFormFields(tab)
    }

    //SLOTS
    function onClearFormFields(tab) {
        //hay que definirla para cada pestaña; se llama desde C++
        console.log("Se ha llamado a la función onClearFormFields(" + tab
                    + ") desde EmpresaTab.qml")
        if (tab === "empresa") {
            textFieldEmpresa.clear()
            textFieldHolding.clear()
            textFieldWeb.clear()
            textFieldPanjiba.clear()
            textFieldMaps.clear()
            textFieldCiudad.clear()
            textFieldPostcode.clear()
            textFieldMoq.clear()
            textAreaNotasEmpresa.clear()
            comboBoxActividad.currentIndex = -1
            comboBoxPais.currentIndex = -1
            comboBoxFormaPago.currentIndex = -1
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


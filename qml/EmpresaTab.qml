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

    textFieldEmpresa.onEditingFinished: SupplierClass.empresa = textFieldEmpresa.text
    textFieldHolding.onEditingFinished: SupplierClass.holding = textFieldHolding.text
    comboBoxActividad.onCurrentIndexChanged: SupplierClass.actividad = comboBoxActividad.currentText
    textFieldWeb.onEditingFinished: SupplierClass.web = textFieldWeb.text
    textFieldPanjiba.onEditingFinished: SupplierClass.panjiba = textFieldPanjiba.text
    textFieldMaps.onEditingFinished: SupplierClass.maps = textFieldMaps.text
    comboBoxPais.onCurrentIndexChanged: SupplierClass.pais = comboBoxPais.currentText
    textFieldCiudad.onEditingFinished: SupplierClass.ciudad = textFieldCiudad.text
    textFieldPostcode.onEditingFinished: SupplierClass.postcode = textFieldPostcode.text
    textFieldMoq.onEditingFinished: SupplierClass.moq = textFieldMoq.text
    textFieldNotasEmpresa.onEditingFinished: SupplierClass.notasEmpresa = textFieldNotas.text
    textFieldPago.onEditingFinished: SupplierClass.formaPago = textFieldPago.text

    empresaButtonAceptar.onClicked: SupplierClass.onEmpresaButtonAceptarClicked()
    empresaButtonCancelar.onClicked: SupplierClass.onEmpresaButtonCancelarClicked()
    empresaButtonGuardar.onClicked: SupplierClass.onEmpresaButtonGuardarClicked()

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


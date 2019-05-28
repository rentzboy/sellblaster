import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"

EmpresaTabForm {
    id: form

    textFieldEmpresa.onEditingFinished: AddSupplier.empresa = textFieldEmpresa.text
    textFieldHolding.onEditingFinished: AddSupplier.holding = textFieldHolding.text
    comboBoxActividad.onEditingFinished: AddSupplier.actividad = comboBoxActividad.text
    textFieldWeb.onEditingFinished: AddSupplier.web = textFieldWeb.text
    textFieldPanjiba.onEditingFinished: AddSupplier.panjiba = textFieldPanjiba.text
    textFieldMaps.onEditingFinished: AddSupplier.maps = textFieldMaps.text
    comboBoxPais.onEditingFinished: AddSupplier.pais = comboBoxPais.text
    textFieldCiudad.onEditingFinished: AddSupplier.ciudad = textFieldCiudad.text
    textFieldPostcode.onEditingFinished: AddSupplier.postcode = textFieldPostcode.text
    textFieldMoq.onEditingFinished: AddSupplier.moq = textFieldMoq.text
    textFieldNotasEmpresa.onEditingFinished: AddSupplier.notasEmpresa = textFieldNotas.text
    textFieldPago.onEditingFinished: AddSupplier.formaPago = textFieldPago.text

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


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
    objectName: "EmpresaTabForm"

    //TextFields & TextArea
    textFieldEmpresa.text: SupplierType.empresaTabField.empresa
    textFieldHolding.text: SupplierType.empresaTabField.holding
    textFieldWeb.text: SupplierType.empresaTabField.web
    textFieldPanjiba.text: SupplierType.empresaTabField.panjiba
    textFieldMaps.text:SupplierType.empresaTabField.maps
    textFieldCiudad.text: SupplierType.empresaTabField.ciudad
    textFieldPostcode.text: SupplierType.empresaTabField.postcode
    textFieldMoq.text: SupplierType.empresaTabField.moq
    textAreaNotasEmpresa.text: SupplierType.empresaTabField.notasEmpresa

    //ComboBoxes (models loaded in C++)

    //Buttons
    buttonAceptar.onClicked: SupplierType.onAceptarButton("empresa")
    buttonCancelar.onClicked: SupplierType.onCancelarButton()
    buttonGuardar.onClicked: SupplierType.onGuardarButton("empresa")
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

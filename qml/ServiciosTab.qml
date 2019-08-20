import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0

ServiciosTabForm {
    id: form
    objectName: "ServiciosTabForm"

    //TextFields & TextArea
    textFieldEspesorMin1.text: SupplierType.servicioTabField.espesorMin1
    textFieldEspesorMin2.text: SupplierType.servicioTabField.espesorMin2
    textFieldEspesorMin3.text: SupplierType.servicioTabField.espesorMin3
    textFieldEspesorMax1.text: SupplierType.servicioTabField.espesorMax1
    textFieldEspesorMax2.text: SupplierType.servicioTabField.espesorMax2
    textFieldEspesorMax3.text: SupplierType.servicioTabField.espesorMax3
    textFieldAnchoMin1.text: SupplierType.servicioTabField.anchoMin1
    textFieldAnchoMin2.text: SupplierType.servicioTabField.anchoMin2
    textFieldAnchoMin3.text: SupplierType.servicioTabField.anchoMin3
    textFieldAnchoMax1.text: SupplierType.servicioTabField.anchoMax1
    textFieldAnchoMax2.text: SupplierType.servicioTabField.anchoMax2
    textFieldAnchoMax3.text: SupplierType.servicioTabField.anchoMax3

    //ComboBoxes
    comboBoxServicios.model: SupplierType.servicioList

    //Buttons
    buttonAceptar.onClicked: SupplierType.onAceptarButton("servicio")
    buttonCancelar.onClicked: SupplierType.onCancelarButton()
    buttonGuardar.onClicked: SupplierType.onGuardarButton("servicio")
}








/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/

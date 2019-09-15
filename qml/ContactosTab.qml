import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0

ContactosTabForm {
    id: contactosForm
    objectName: "ContactosTabForm"

    //TextFields & textArea
    textFieldNombre.text: SupplierType.contactoTabField.nombre
    textFieldApellido.text: SupplierType.contactoTabField.apellido
    textFieldEmail.text: SupplierType.contactoTabField.email
    textFieldTelefono.text: SupplierType.contactoTabField.telefono
    textFieldMovil.text:SupplierType.contactoTabField.movil
    textAreaNotasContacto.text:SupplierType.contactoTabField.notasContacto

    //ComboBoxes (ver ComboBox1.qml)
    comboBoxArea.onDisplayTextChanged: SupplierType.contactoTabField.area = comboBoxArea.displayText
    comboBoxPuesto.onDisplayTextChanged: SupplierType.contactoTabField.puesto = comboBoxArea.displayText

    //Buttons
    buttonAceptar.onClicked: SupplierType.onAceptarButton("contacto")
    buttonCancelar.onClicked: SupplierType.onCancelarButton()
    buttonGuardar.onClicked: SupplierType.onGuardarButton("contacto")
}
/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


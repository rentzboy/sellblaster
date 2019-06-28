import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0
import "../js/supplier.js" as Supplier

ContactosTabForm {
    id: contactosForm
    objectName: "ContactosTabForm"

    //TextFields (ver TextField1.qml)

    //ComboBoxes (ver ComboBox1.qml)
    comboBoxArea.model: SupplierType.areaList
    comboBoxPuesto.model: SupplierType.puestoList

    //Buttons
    buttonAceptar.onClicked: SupplierType.onAceptarButton("contactos")
    buttonCancelar.onClicked: SupplierType.onCancelarButton("contactos")
    buttonGuardar.onClicked: SupplierType.onGuardarButton("contactos")

    //SLOTS
    function onClearContactosFields(tab) {
        //hay que definirla para cada pestaña; se llama desde C++
        //Borra los valores de los campos pero no resetea las variables de la clase C++
        //Es necesario resetear el valor de las member variables para que no
        //pase el valor en la siguiente query aunque el usuario no lo rellene
        console.log("Se ha llamado a la función onClearContactosFields(" + tab + ")")
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

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


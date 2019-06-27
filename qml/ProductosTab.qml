import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0
import "../js/supplier.js" as Supplier

ProductosTabForm {
    id: form
    objectName: "ProductosTabForm"

    //TextFields

    //ComboBoxes
    comboBoxFormato.model: SupplierClass.formatoList
    comboBoxMaterial.model: SupplierClass.materialList
    comboBoxTratamiento.model: SupplierClass.formatoList
    comboBoxAleacion.model: SupplierClass.aleacionList
    comboBoxTemple.model: SupplierClass.templeList
    comboBoxAcabado.model: SupplierClass.acabadoList

    //Buttons
    buttonAceptar.onClicked: SupplierClass.onAceptarButton("contacto")
    buttonCancelar.onClicked: close()
    buttonGuardar.onClicked: SupplierClass.onGuardarButton("contacto")

    //SLOTS
    function onClearProductosFields(tab) {
        //hay que definirla para cada pestaña; se llama desde C++
        console.log("Se ha llamado a la función onClearProductosFields(" + tab + ")")
        //PENDING -no se que campos borrar todavía-
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


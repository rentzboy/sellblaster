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

    function onFormatoComboBoxChanged() {
        //Igual para todos los comboBoxes
        Supplier.comboBoxIndexToBackEnd("formato", comboBoxFormato.currentIndex)
        //Customization
        if (state === "chapa")
            state = "barra"
        else if (state === "barra")
            state = "tubo"
        else
            state = "chapa"
    }

    //States
    states: [
        State {
            name: "chapa"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Espesor min:")
            }
        },
        State {
            name: "barra"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Diametro")
            }
        },
        State {
            name: "tubo"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Diametro int:")
            }
        }
    ]

    //TextFields

    //ComboBoxes
    comboBoxFormato.onCurrentIndexChanged: onFormatoComboBoxChanged()
    comboBoxFormato.model: SupplierType.formatoList
    comboBoxMaterial.model: SupplierType.materialList
    comboBoxTratamiento.model: SupplierType.tratamientoList
    comboBoxAleacion.model: SupplierType.aleacionList
    comboBoxTemple.model: SupplierType.templeList
    comboBoxAcabado.model: SupplierType.acabadoList

    //Buttons
    buttonAceptar.onClicked: SupplierType.onAceptarButton("productos")
    buttonCancelar.onClicked: SupplierType.onCancelarButton()
    buttonGuardar.onClicked: SupplierType.onGuardarButton("productos")

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

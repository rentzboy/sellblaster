import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Layouts 1.3
import "components"
import SupplierClass 1.0

ContactosTabForm {
    id: form

    //TextFields
    textFieldNombre.onEditingFinished: textValueToBackEnd("nombre",
                                                          textFieldNombre.text)
    textFieldApellido.onEditingFinished: textValueToBackEnd(
                                             "apellido", textFieldApellido.text)
    textFieldEmail.onEditingFinished: textValueToBackEnd("email",
                                                         textFieldEmail.text)
    textFieldTelefono.onEditingFinished: textValueToBackEnd(
                                             "telefono", textFieldTelefono.text)
    textFieldMovil.onEditingFinished: textValueToBackEnd("movil",
                                                         textFieldMovil.text)
    textAreaNotasContacto.onEditingFinished: textValueToBackEnd(
                                                 "notasContacto",
                                                 textAreaNotasContacto.text)

    //ComboBoxes
    comboBoxArea.currentIndex: -1
    comboBoxArea.model: SupplierClass.areaList
    comboBoxArea.onCurrentIndexChanged: comboBoxValueToBackEnd(
                                            "area", comboBoxArea.currentIndex)

    comboBoxPuesto.currentIndex: -1
    comboBoxPuesto.model: SupplierClass.puestoList
    comboBoxPuesto.onCurrentIndexChanged: comboBoxValueToBackEnd(
                                              "puesto",
                                              comboBoxPuesto.currentIndex)

    //Buttons
    buttonAceptar.onClicked: SupplierClass.onAceptarButton("contacto")
    buttonCancelar.onClicked: close()
    buttonGuardar.onClicked: SupplierClass.onGuardarButton("contacto")

    //JS FUNCTIONS
    function textValueToBackEnd(field, txt) {
        SupplierClass.textValueToBackEnd(field, txt)
    }

    function comboBoxValueToBackEnd(field, index) {
        var txt
        switch (field) {
        case "area":
            txt = SupplierClass.areaList[index]
            break
        case "puesto":
            txt = SupplierClass.puestoList[index]
            break
        default:

        }
        textValueToBackEnd(field, txt)
    }

    //SLOTS
    function onCloseQmlInstance() {
        close()
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/


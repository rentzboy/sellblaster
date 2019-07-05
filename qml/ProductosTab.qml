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
        console.log("currentText: " + comboBoxFormato.displayText
                    + ", currentIndex: " + comboBoxFormato.currentIndex)

        //Customization
        switch (comboBoxFormato.displayText) {
        case "Chapa":
            state = "chapa"
            break
        case "Bobina":
            state = "chapa"
            break
        case "Fleje":
            state = "chapa"
            break
        case "Barra":
            state = "barra"
            break
        case "Tubo":
            state = "tubo"
            break
        case "Pletina":
            state = "pletina"
            break
        default:

        }
    }

    //States
    states: [
        State {
            name: "chapa"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Espesor min:")
            }
            PropertyChanges {
                target: labelEspesorMax
                text: qsTr("Espesor max:")
            }
        },
        State {
            name: "barra"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Diametro")
                visible: true
            }
            PropertyChanges {
                target: labelEspesorMax
                visible: false
            }
        },
        State {
            name: "tubo"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Diametro int:")
                visible: true
            }
            PropertyChanges {
                target: labelEspesorMax
                text: qsTr("Diametro ext:")
                visible: true
            }
            PropertyChanges {
                target: labelAnchoMin
                visible: false
            }
            PropertyChanges {
                target: labelAnchoMax
                visible: fasle
            }
        },
        State {
            name: "pletina"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Alto:")
            }
            PropertyChanges {
                target: labelEspesorMax
                text: qsTr("Ancho:")
            }
        },
        State {
            name: "barra1"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Diametro")
                visible: true
            }

            PropertyChanges {
                target: labelEspesorMax
                visible: false
            }
        },
        State {
            name: "barra2"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Diametro")
                visible: true
            }

            PropertyChanges {
                target: labelEspesorMax
                visible: false
            }
        },
        State {
            name: "barra3"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Diametro")
                visible: true
            }

            PropertyChanges {
                target: labelEspesorMax
                visible: false
            }
        },
        State {
            name: "barra4"
            PropertyChanges {
                target: labelEspesorMin
                text: qsTr("Diametro")
                visible: true
            }

            PropertyChanges {
                target: labelEspesorMax
                visible: false
            }
        }
    ]

    //TextFields

    //ComboBoxes
    comboBoxFormato.onDisplayTextChanged: onFormatoComboBoxChanged()
    //comboBoxFormato.onCurrentIndexChanged:
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
    D{i:0;autoSize:true;height:480;width:1000}
}
 ##^##*/

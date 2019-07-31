import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import SupplierClass 1.0
import "../../js/supplier.js" as Supplier


/* IMPORTANTE: que todos los comboBox1 que creemos le asignemos
  un objectName pues se necesitan para las funciones de JS
*/
ComboBox {
    id: comboBox11
    Layout.minimumWidth: 150
    Layout.fillWidth: true
    Layout.preferredHeight: 40
    objectName: objectName //para poder llamarlo desde checkDelegate

    delegate: Item {
        //Hack para que no se cierre automáticamente el popup onClick
        id: itemDelegate
        width: parent.width
        implicitHeight: checkDelegate.implicitHeight

        CheckDelegate {
        id: checkDelegate
        width: parent.width
        text: modelData
        checked: false //para que asigne el valor al crearse
        //onCheckedChanged: model.checked = checked (otra manera de hacerlo)
        onToggled: Supplier.checkingCheckBoxes(comboBox11.objectName, text, checked)
        }
    }
    onModelChanged: Supplier.initializationComboBoxIndex()
    //Component.onCompleted: Supplier.onComboBoxCompleted()
}

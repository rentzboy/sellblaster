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
    property string supplierTab
    property bool toogleAllValues
    Layout.minimumWidth: 150 //si lo quito NO carga NewProveedor.qml !!
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
            checked: toogleAllValues
            //onCheckedChanged: model.checked = checked (otra manera de hacerlo)
            onToggled: Supplier.textListToBackEnd(comboBox11.objectName, text, checked) //OJO: checked es el valor de property
        }
    }
    //onModelChanged: Supplier.resetComboBoxIndex(supplierTab, objectName)
    //Component.onCompleted: Supplier.onComboBoxCompleted()
}

     /*DEPRECATED: No funciona pues NO utilizamos un ListModel
    onToggled: toogleCheckValues(comboBox11.objectName, modelData, text, checked, index) //index=>view ListModel
    function toogleCheckValues(objectName, model, textValue, checkedValue, index) {
        console.log("model.count=" + model.count)
        if(index === 0) {
            var i = 0;
            while(i <model.count) {
                console.log("i=" + i)
                model.setProperty(i, "checked", !checkedValue)
                i++
            //checked = SupplierType.toogleAllValues(objectName)
            }
        }
        else Supplier.textListToBackEnd(objectName, textValue, checkedValue, modelIndex)
    } */



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

    id: comboListView
    Layout.minimumWidth: 150
    Layout.fillWidth: true
    Layout.preferredHeight: 40
    objectName: objectName //para poder llamarlo desde checkDelegate

    textRole: "name" //ComboBox only can show 1 role

    model: ListModel {
        id: model
        ListElement { name: "Banana"
                               checked: false }
        ListElement { name: "Apple"
                                checked: false}
        ListElement { name: "Coconut"
                                checked: false}}


        delegate: Item {
            //Hack para que no se cierre automáticamente el popup onClick
            id: itemDelegate
            width: parent.width
            implicitHeight: checkDelegate.implicitHeight

            CheckDelegate {
            id: checkDelegate
            width: parent.width
            text: model.name
            checked: toogleValue //para que asigne el valor al crearse
            onCheckedChanged: showCurrentCheckBox(comboListView.model, index, checked)
            //onToggled: Supplier.textListToBackEnd(comboListView.objectName, text, checked) //OJO: checked es el valor de property
            }
            //onModelChanged: Supplier.resetComboBoxIndex(objectName)
}
        function showCurrentCheckBox(model, index, checked) {
            var i = 1;
            console.log("indice[0]=" + model.get(0).name)
            console.log("indice[1]=" + model.get(1).name)
            console.log("indice[2]=" + model.get(2).name)
            while(i <model.count) {
                console.log("model.count=" + model.count)
                console.log("i=" + i)
                model.setProperty(i, "checked", checked)
                i++
            }
            //console.log("name:" + model.get(index).name + ", checked: " + model.get(index).checked)
        }

    //Component.onCompleted: Supplier.onComboBoxCompleted()
}

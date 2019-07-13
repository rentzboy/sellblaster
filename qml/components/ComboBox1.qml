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
    id: comboBox
    Layout.minimumWidth: 150
    Layout.fillWidth: true
    Layout.preferredHeight: 40

    onModelChanged: initializationComboBoxIndex(objectName)
    onCurrentIndexChanged: Supplier.comboBoxIndexToBackEnd(objectName,
                                                           currentIndex)
    //Component.onCompleted: onComboBoxCompleted()

    //JS
    function onComboBoxCompleted() {
        console.log("Componente cargado: " + objectName + " con el modelo: " + model)
    }
    function initializationComboBoxIndex(comboBox) {

        /*Los comboBox se inician a -1 (no muestran valores) pero al cargar el model,
        automáticamente coge el primer valor, en este caso el index 0, por lo que
        muestra un valor aunque el usuario no haya seleccionado nada.
       La función initializationComboBoxIndex permite que no se muestre ningún
       valor en el comboBox hasta que el usuario no seleccione uno, por lo
       que hay que asignarla a onModelChanged.*/
        //console.log("Se ha llamado a la función initializationComboBoxIndex(" + comboBox + ")")
        currentIndex = -1
    }
}

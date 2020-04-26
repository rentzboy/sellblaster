import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import SupplierClass 1.0
import "../../js/supplier.js" as Supplier


/* IMPORTANTE: que todos los comboBox1 que creemos le asignemos
  un objectName pues se necesitan para las funciones de JS */
ComboBox {
    id: comboBox
    property string supplierTab
    Layout.minimumWidth: 150
    Layout.fillWidth: true
    Layout.preferredHeight: 40

    onActivated: Supplier.textValueToBackEnd(supplierTab, objectName, displayText)
    //onModelChanged: Supplier.resetComboBoxIndex(supplierTab, objectName)
    //onDisplayTextChanged: Supplier.textValueToBackEnd(supplierTab, objectName, displayText)
    //Component.onCompleted: Supplier.onComboBoxCompleted()
}

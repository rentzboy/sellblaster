import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import SupplierClass 1.0
import "../../js/supplier.js" as Supplier

TextField {
    id: textField
    property string supplierTab
    Layout.fillWidth: true
    Layout.preferredHeight: 40
    //overwriteMode: true => cambia el cursor x uno bastante raro ......
    selectByMouse: true
    onEditingFinished: Supplier.textValueToBackEnd(supplierTab, objectName, text)
}

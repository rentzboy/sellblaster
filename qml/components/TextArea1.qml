import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import SupplierClass 1.0
import "../../js/supplier.js" as Supplier

TextArea {
    id: textArea
    property string supplierTab
    property Item navigationTab

    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.preferredHeight: 40
    wrapMode: Text.WordWrap
    KeyNavigation.tab: navigationTab
    KeyNavigation.priority: KeyNavigation.BeforeItem
    selectByMouse: true
    clip: true
    //overwriteMode: true => cambia el cursor x uno bastante raro ......
    onEditingFinished: Supplier.textValueToBackEnd(supplierTab, objectName, text)
}

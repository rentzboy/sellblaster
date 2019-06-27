import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import SupplierClass 1.0
import "../../js/supplier.js" as Supplier

TextArea {
    id: textArea
    onEditingFinished: Supplier.textValueToBackEnd(objectName, text)
}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3

//Es un comboBox normal, pero al crearse el currentIndex se pone a-1
//Los ComboBox normales se inician a 0 por lo que se muestra el 1er valor
ComboBox {
    id: comboBox
    currentIndex: -1
}

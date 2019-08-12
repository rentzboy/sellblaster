//Ver Importing JavaScript Resources in QML
.import  SupplierClass 1.0 as Supplier

//JS FUNCTIONS
function textValueToBackEnd(tab, fieldName, value) {
        Supplier.SupplierType.textValueToBackEnd(tab, fieldName, value)
}
function textListToBackEnd(fieldName, text, checked) {
    if(text)
        Supplier.SupplierType.textListToBackEnd(fieldName, text, checked)
}
function onRadioButtonClicked(objectName) {
    //console.log("onRadioButtonClicked: (" + objectName + ")")
    SupplierType.onRelatedFieldUpdated(objectName);
}
function resetComboBoxIndex(tab, fieldName) {
    /*Los comboBox se inician a -1 (no muestran valores) pero al cargar el model,
    automáticamente coge el primer valor, en este caso el index 0, por lo que
    muestra un valor aunque el usuario no haya seleccionado nada.
    Hay que llamar a esta función desde onModelChanged */

    //console.log("Se ha llamado a resetComboBoxIndex (" + fieldName + ")")

    // Mostrar el comboBox en blanco hasta que el usuario seleccione uno,
    currentIndex = -1

    //Para eliminar el valor que se ha pasado automáticamente a C++ al cargar el modelo
    textValueToBackEnd(tab, fieldName, "reset")
}
function onTipoComboBoxChanged(currentText) {
    //console.log("currentText: " + comboBoxTipo.currentText + ", currentIndex: " + comboBoxTipo.currentIndex)

    //Para que se muestre el state=reset al cargar la 1era vez ProductosTab
    counter++
    if(counter === 2) {
        state = "reset"
        return
    }

    //Customization
    switch (currentText) {
    case "Inicio":
        state = "reset"
        break
    case "Bobina":
        state = "bobina"
        break
    case "Chapa":
        state = "chapa"
        break
    case "Barra":
        state = "barra"
        break
    case "Tubo":
        state = "tubo"
        break
    case "Plancha":
        state = "chapa"
        break
    case "Disco":
        state = "disco"
        break
    case "Pletina":
        state = "pletina"
        break
    default:

    }
}
//Deprecated
function onComboBoxCompleted() {
    console.log("Componente cargado: " + objectName + " con el modelo: " + model)
}

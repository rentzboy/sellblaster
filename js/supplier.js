//Ver Importing JavaScript Resources in QML
.import  SupplierClass 1.0 as Supplier

//JS FUNCTIONS
function textValueToBackEnd(tab, fieldName, value) {
    //console.log("Call to textValueToBackEnd() " + "tab: " + tab + " fieldName: " + fieldName + " displayText: " + value)
    Supplier.SupplierType.textValueToBackEnd(tab, fieldName, value)
    if(fieldName === "tipo")
        onTipoComboBoxChanged(value)
}
function textListToBackEnd(fieldName, text, checked) {
    if(text)
        Supplier.SupplierType.textListToBackEnd(fieldName, text, checked)
}
function onRadioButtonClicked(objectName) {
    //console.log("onRadioButtonClicked: (" + objectName + ")")
    Supplier.SupplierType.onRelatedFieldUpdated(objectName);
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
function onTipoComboBoxChanged(displayText) {
    //console.log("displayText: " + displayText + ", currentText: " + comboBoxTipo.currentText)

    //Para que se muestre el state=reset al cargar la 1era vez ProductosTab
    //Sino se muestra por defecto state=bobina
    productosTab.counter++
    if(productosTab.counter === 2) {
        productosTab.state = "reset"
        return
    }

    //Customization
    switch (displayText) {
    case "Inicio":
        productosTab.state = "reset"
        break
    case "Bobina":
        productosTab.state = "bobina"
        break
    case "Chapa":
        productosTab.state = "chapa"
        break
    case "Barra":
        productosTab.state = "barra"
        break
    case "Tubo":
        productosTab.state = "tubo"
        break
    case "Plancha":
        productosTab.state = "chapa"
        break
    case "Disco":
        productosTab.state = "disco"
        break
    case "Pletina":
        productosTab.state = "pletina"
        break
    default:

    }
}

//Deprecated
function onComboBoxCompleted() {
    console.log("Componente cargado: " + objectName + " con el modelo: " + model)
}

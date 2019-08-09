//Ver Importing JavaScript Resources in QML
.import  SupplierClass 1.0 as Supplier

//JS FUNCTIONS
function textValueToBackEnd(fieldName, value) { 
        Supplier.SupplierType.textValueToBackEnd(fieldName, value)
}
function textListToBackEnd(fieldName, text, checked) {
    if(text)
        Supplier.SupplierType.textListToBackEnd(fieldName, text, checked)
}
function resetComboBoxIndex(fieldName) {
    /*Los comboBox se inician a -1 (no muestran valores) pero al cargar el model,
    automáticamente coge el primer valor, en este caso el index 0, por lo que
    muestra un valor aunque el usuario no haya seleccionado nada.
    Hay que llamar a esta función desde onModelChanged */

    console.log("Se ha llamado a resetComboBoxIndex (" + fieldName + ")")

    // Mostrar el comboBox en blanco hasta que el usuario seleccione uno,
    currentIndex = -1

    //Para eliminar el valor que se ha pasado automáticamente a C++ al cargar el modelo
    textValueToBackEnd(fieldName, "reset")
}

//Deprecated
function onComboBoxCompleted() {
    console.log("Componente cargado: " + objectName + " con el modelo: " + model)
}

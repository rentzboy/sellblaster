//Ver Importing JavaScript Resources in QML
.import  SupplierClass 1.0 as Supplier

//JS FUNCTIONS
function textValueToBackEnd(fieldName, value) { 
    if(value) //sanitation check
    Supplier.SupplierType.textValueToBackEnd(fieldName, value)
}

function checkingCheckBoxes(fieldName, text, checked) {
    if(text) //sanitation check
    Supplier.SupplierType.textListToBackEnd(fieldName, text, checked)
}

function initializationComboBoxIndex() {
    /*Los comboBox se inician a -1 (no muestran valores) pero al cargar el model,
    automáticamente coge el primer valor, en este caso el index 0, por lo que
    muestra un valor aunque el usuario no haya seleccionado nada.
   La función initializationComboBoxIndex permite que no se muestre ningún
   valor en el comboBox hasta que el usuario no seleccione uno, por lo
   que hay que asignarla a onModelChanged.*/
    currentIndex = -1
}

//Deprecated
function comboBoxIndexToBackEnd(fieldName, index) {
    console.log("Se ha llamado a comboBoxIndexToBackEnd: (" + fieldName + ", " + index + ")")
    if (index === -1)
        return
    var txt
    switch (fieldName) {
    case "pais":
        txt = Supplier.SupplierType.paisList[index]
        break
    case "actividad":
        txt = Supplier.SupplierType.actividadList[index]
        break
    case "formaPago":
        txt = Supplier.SupplierType.formaPagoList[index]
        break
    case "area":
        txt = Supplier.SupplierType.areaList[index]
        break
    case "puesto":
        txt = Supplier.SupplierType.puestoList[index]
        break
    case "tipo":
        txt = Supplier.SupplierType.tipoList[index]
        break
    case "material":
        txt = Supplier.SupplierType.materialList[index]
        break
    case "serie":
        txt = Supplier.SupplierType.serieList[index]
        break
    case "aleacion":
        txt = Supplier.SupplierType.aleacionList[index]
        break
    case "temple":
        txt = Supplier.SupplierType.templeList[index]
        break
    case "acabado":
        txt = Supplier.SupplierType.acabadoList[index]
        break
    case "acabado":
        txt = Supplier.SupplierType.acabadoList[index]
        break
    case "formatoChapa":
        txt = Supplier.SupplierType.formatoList[index]
        break
    case "anchoBobina":
        txt = Supplier.SupplierType.formatoList[index]
        break
    case "diametroIntBobina":
        txt = Supplier.SupplierType.idBobinaList[index]
        break
    default:

    }
    textValueToBackEnd(fieldName, txt)
}

function onComboBoxCompleted() {
    console.log("Componente cargado: " + objectName + " con el modelo: " + model)
}

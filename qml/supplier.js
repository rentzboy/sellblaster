//Functions to be used with AddSupplier

//JS FUNCTIONS
function initializationComboBoxIndex(comboBox) {
    console.log("Se ha llamado a la función initializationComboBoxIndex(" + comboBox + ")")
    if (comboBox === "comboBoxArea") {
        comboBoxArea.currentIndex = -1
    } else if (comboBox === "comboBoxPuesto") {
        comboBoxPuesto.currentIndex = -1
    } else if (comboBox === "comboBoxFormato") {
        comboBoxFormato.currentIndex = -1
    } else if (comboBox === "comboBoxMaterial") {
        comboBoxMaterial.currentIndex = -1
    } else if (comboBox === "comboBoxTratamiento") {
        comboBoxTratamiento.currentIndex = -1
    } else if (comboBox === "comboBoxAleacion") {
        comboBoxAleacion.currentIndex = -1
    }
}
function textValueToBackEnd(field, txt) {
    SupplierClass.textValueToBackEnd(field, txt)
}
function comboBoxIndexToBackEnd(field, index) {
    console.log("Se ha llamado a comboBoxIndexToBackEnd: " + field + ", " + index)
    var txt
    switch (field) {
    case "pais":
        txt = SupplierClass.paisList[index]
        break
    case "actividad":
        txt = SupplierClass.actividadList[index]
        break
    case "formaPago":
        txt = SupplierClass.formaPagoList[index]
        break
    case "area":
        txt = SupplierClass.areaList[index]
        break
    case "puesto":
        txt = SupplierClass.puestoList[index]
        break
    case "formato":
        txt = SupplierClass.formatoList[index]
        break
    case "material":
        txt = SupplierClass.materialList[index]
        break
    case "tratamiento":
        txt = SupplierClass.tratamientoList[index]
        break
    case "aleacion":
        txt = SupplierClass.aleacionList[index]
        break
    default:

    }
    textValueToBackEnd(field, txt)
}

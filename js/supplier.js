//Ver Importing JavaScript Resources in QML
.import  SupplierClass 1.0 as SupplierClass

//JS FUNCTIONS
function textValueToBackEnd(fieldName, value) {
    SupplierClass.SupplierClass.textValueToBackEnd(fieldName, value)
}
function comboBoxIndexToBackEnd(fieldName, index) {
    console.log("Se ha llamado a comboBoxIndexToBackEnd: (" + fieldName + ", " + index + ")")
    if (index === 0 || index === -1)
        return
    var txt
    switch (fieldName) {
    case "pais":
        txt = SupplierClass.SupplierClass.paisList[index]
        break
    case "actividad":
        txt = SupplierClass.SupplierClass.actividadList[index]
        break
    case "formaPago":
        txt = SupplierClass.SupplierClass.formaPagoList[index]
        break
    case "area":
        txt = SupplierClass.SupplierClass.areaList[index]
        break
    case "puesto":
        txt = SupplierClass.SupplierClass.puestoList[index]
        break
    case "formato":
        txt = SupplierClass.SupplierClass.formatoList[index]
        break
    case "material":
        txt = SupplierClass.SupplierClass.materialList[index]
        break
    case "tratamiento":
        txt = SupplierClass.SupplierClass.tratamientoList[index]
        break
    case "aleacion":
        txt = SupplierClass.SupplierClass.aleacionList[index]
        break
    case "temple":
        txt = SupplierClass.SupplierClass.templeList[index]
        break
    case "acabado":
        txt = SupplierClass.SupplierClass.acabadoList[index]
        break
    default:

    }
    textValueToBackEnd(fieldName, txt)
}

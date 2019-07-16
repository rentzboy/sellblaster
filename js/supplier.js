//Ver Importing JavaScript Resources in QML
.import  SupplierClass 1.0 as Supplier

//JS FUNCTIONS
function textValueToBackEnd(fieldName, value) {
    Supplier.SupplierType.textValueToBackEnd(fieldName, value)
}
//jjj
function comboBoxIndexToBackEnd(fieldName, index) {
    //console.log("Se ha llamado a comboBoxIndexToBackEnd: (" + fieldName + ", " + index + ")")
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
    default:

    }
    textValueToBackEnd(fieldName, txt)
}

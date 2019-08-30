#include "addsupplier.h"
#include "basic_headers.h"
#include <QMap>
#include <QMessageBox>
#include <QQmlProperty>

//static initialization
QQmlApplicationEngine* AddSupplier::engine = Q_NULLPTR;
AddSupplier* AddSupplier::uniqueInstance = Q_NULLPTR;
int AddSupplier::typeId = 0;

//PUBLIC MEMBERS
void AddSupplier::createComponent(void)
{
    if(uniqueInstance == Q_NULLPTR)
    {
        uniqueInstance = new AddSupplier;
        registerSingleton();

        //Load QML component
        engine = new QQmlApplicationEngine;
        engine->load(QUrl(QStringLiteral("qrc:/qml/NewProveedor.qml")));

        connect(uniqueInstance, &AddSupplier::relatedFieldUpdated, uniqueInstance, &AddSupplier::onRelatedFieldUpdated);
        connect(engine->rootObjects().value(AddSupplier::typeId), SIGNAL(closeQmlInstance()), uniqueInstance, SLOT(onCloseQmlInstance()));


        /* DEPRECATED:
         * Hemos encontrado otras maneras + sencillas, pero lo dejo pues explica como conectar los signals/slots
        1- Connect C++ to QML Signals / Slots
        engine->rootObjects() solo recupera los objetos instanciados con load (si utilizamos component.create() no funciona)
        Solo funciona para SLOTS definidos en archivo .qml que cargamos mediante engine->load
        QObject *contactosTabObject = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("ContactosTabForm");
        connect(uniqueInstance, SIGNAL(clearFormFields(QVariant)), contactosTabObject, SLOT(onClearContactosFields(QVariant)));
        QObject *productosTabObject = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("ProductosTabForm");
        connect(uniqueInstance, SIGNAL(clearFormFields(QVariant)), productosTabObject, SLOT(onClearProductosFields(QVariant)));

        2- Connect QML to C++ Signals/Slots
        connect(engine->rootObjects().value(AddSupplier::typeId), SIGNAL(closing(CloseEvent)), uniqueInstance, SLOT(closeEvent(QCloseEvent*)));
        connect(engine->rootObjects().value(AddSupplier::typeId), SIGNAL(closing(CloseEvent)), uniqueInstance, SLOT(onCloseEventCaller())); */

        qDebug() << "***** FINAL CREATE_COMPONENT ADDSUPPLIER *****";
    }
    else
    {
        //Load QML component
        engine = new QQmlApplicationEngine;
        engine->load(QUrl(QStringLiteral("qrc:/qml/NewProveedor.qml")));
    }
}
void AddSupplier::textValueToBackEnd(QString tab, QString fieldName, QString text)
{
//    PRINT_FUNCTION_NAME
//    qDebug() << "tab:" << tab <<"fieldName:" << fieldName << ", " << "tex: " << text;

    if(tab == "empresa")
        setEmpresaTabField(fieldName, text);
    else if(tab == "contacto")
        setContactoTabField(fieldName, text);
    else if(tab == "producto")
    {
        setProductoTabField(fieldName, text);

        //Cargar los comboBoxes relacionados
        if(fieldName == "tipo" || fieldName == "material")
            emit relatedFieldUpdated(fieldName);
    }
    else if(tab == "servicio")
        setServicioTabField(fieldName, text);
}
void AddSupplier::textListToBackEnd(QString fieldName, QString text, bool value)
{
    PRINT_FUNCTION_NAME
    qDebug() << "fieldName: " << fieldName << ", text: " << text << ", value: " << value;

    if(fieldName == "serie")
    {
        if(value) //checked=true
            serieSelectionList.append(text);
        else
            serieSelectionList.removeOne(text);
        emit relatedFieldUpdated(fieldName);
    }
    else if(fieldName == "aleacion")
    {
        if(value) aleacionSelectionList.append(text);
        else aleacionSelectionList.removeOne(text);
    }
    else if(fieldName == "temple")
    {
        if(value) templeSelectionList.append(text);
        else templeSelectionList.removeOne(text);
    }
    else if(fieldName == "acabado")
    {
        if(value) acabadoSelectionList.append(text);
        else acabadoSelectionList.removeOne(text);
    }
    else if(fieldName == "formatoChapa")
    {
        if(value) formatoChapaSelectionList.append(text);
        else formatoChapaSelectionList.removeOne(text);
    }
    else if(fieldName == "anchoBobina")
    {
        if(value) formatoBobinaSelectionList.append(text);
        else formatoBobinaSelectionList.removeOne(text);
    }
    else if(fieldName == "diametroIntBobina")
    {
        if(value) idBobinaSelectionList.append(text);
        else idBobinaSelectionList.removeOne(text);
    }
    else if(fieldName == "servicio")
    {
        if(value) servicioSelectionList.append(text);
        else servicioSelectionList.removeOne(text);
    }
}
void AddSupplier::uncheckAllValues(QString comboBox)
{
    //Se llama despues de añadir un registro a la DB y al modificar los comboBoxes Tipo, Material y Serie
    //Hay que emitir 2 veces la señal pues solo se actualiza el valor en QML si el valor realmente ha cambiado
    toogleValue.insert(comboBox, true);
    emit toogleValueChanged();
    toogleValue.insert(comboBox, false);
    emit toogleValueChanged();

    //Si tuvieramos los selectionList en un QMap<QString, QStringList>
    //no habria que ir con los ifs ...........
    /////////////////////// PRODUCTOS ///////////////////////
    if(comboBox == "serie")
         serieSelectionList.clear();
    else if(comboBox == "aleacion")
        aleacionSelectionList.clear();
    else if(comboBox == "temple")
        templeSelectionList.clear();
    else if(comboBox == "acabado")
        acabadoSelectionList.clear();
    else if(comboBox == "anchoBobina")
        formatoBobinaSelectionList.clear();
    else if(comboBox == "diametroIntBobina")
        idBobinaSelectionList.clear();
    else if(comboBox == "formatoChapa")
        formatoChapaSelectionList.clear();
    /////////////////////// SERVICIOS ///////////////////////
    else if(comboBox == "servicio")
        servicioSelectionList.clear();
}
void AddSupplier::toogleAllValues(QString comboBox)
{
    //Toogle all checkboxes for the ComboBox's parameter -se activa mediante la key F12-
    bool tmp = toogleValue.value(comboBox).toBool();
    toogleValue.insert(comboBox, !tmp);
    emit toogleValueChanged();

    if(comboBox == "serie")
    {
        if(tmp) //all checked --> change to unchecked
            serieSelectionList.clear();
        else
            serieSelectionList = serieList;
    }
    else if(comboBox == "aleacion")
    {        if(tmp) //all checked
            aleacionSelectionList.clear();
        else
            aleacionSelectionList = aleacionList;
    }
    else if(comboBox == "temple")
    {
        if(tmp) //all checked
            templeSelectionList.clear();
        else
            templeSelectionList = templeList;
    }
    else if(comboBox == "acabado")
    {
        if(tmp) //all checked
            acabadoSelectionList.clear();
        else
            acabadoSelectionList = acabadoList;
    }
    else if(comboBox == "anchoBobina")
    {
        if(tmp) //all checked
            formatoBobinaSelectionList.clear();
        else
            formatoBobinaSelectionList = formatoList;
    }
    else if(comboBox == "diametroIntBobina")
    {
        if(tmp) //all checked
            idBobinaSelectionList.clear();
        else
            idBobinaSelectionList = idBobinaList;
    }
    else if(comboBox == "formatoChapa")
    {
        if(tmp) //all checked
            formatoChapaSelectionList.clear();
        else
            formatoChapaSelectionList = formatoList;
    }
}
AddSupplier::~AddSupplier()
{
    PRINT_FUNCTION_NAME

    //Importante
    uniqueInstance = Q_NULLPTR;
}

//PRIVATE MEMBERS
AddSupplier::AddSupplier(QObject *parent) : QObject(parent) //private singleton constructor
{
    this->fillComboBoxesFromDb("empresa");
    //fill ComboBox with checkboxes
    //this->fillComboBoxWithCheckBoxFromDb();
    //PENDING
}
void AddSupplier::registerSingleton(void)
{
    qmlRegisterSingletonType<AddSupplier>("SupplierClass", 1, 0, "SupplierType",
        [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(scriptEngine)
        Q_UNUSED(engine)
        return uniqueInstance;
            });
}
void AddSupplier::fillRelatedComboCheckBoxFromDb(QString)
{
    //Unicamente se llama al modificar el comboBox SERIE
    //El comboBox dependiente es el de ALEACION
    //por lo que el parámetero de la función NO es necesario.

    QSqlQuery result;
    QString sqlQuery;

    //Aleación
    aleacionList.clear();
    serieIndexList.clear();
    if(serieSelectionList.isEmpty())
    {
        aleacionList = aleacionListCompleta;
    }
    else
    {
        for (auto itr : serieSelectionList)
        {
            serieIndexList.append(QString::number(serieListCompleta.indexOf(itr) + 1)); //+1 from comboBox index to idTableName
        }
        QString indexList = serieIndexList.join(", ");
        //qDebug() << "serieIndexList: " << serieIndexList;

        sqlQuery = "CALL get_AlloyDropDownMenu(";
        sqlQuery.append("'alloy', '").append(aleacionRadioButton).append("', 'id_serie', '").append(indexList).append("');");
        //qDebug() << sqlQuery;
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            aleacionList.append(result.value(0).toString());
        }
    }
    emit aleacionListChanged();
    //qDebug() << "aleacionList: " << aleacionList;
}
void AddSupplier::fillRelatedComboBoxFromDb(QString comboBox)
{   
    //Actualiza los comboBoxes dependientes
    QString value;
    QSqlQuery result;
    QString sqlQuery;
    QString idType, idMaterial;

    if(comboBox == "tipo")
    {
        value = productoTabField.value("tipo").toString();

        if(value == "Bobina" || value == "Chapa" || value == "Plancha")
        {
            //Formato Chapa-Plancha / Ancho-Bobina (comparten el mismo)
            formatoList.clear();
            idType = QString::number(tipoList.indexOf(value) + 1);
            sqlQuery = "CALL get_DependentDropDownMenu(";
            sqlQuery.append("'format', 'format', 'id_type', ").append(idType).append(");");
            MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
            while(result.next())
            {
                formatoList.append(result.value(0).toString());
            }
            emit formatoListChanged();
            //qDebug() << "formatoList: " << formatoList;
        }
    }
    else if(comboBox == "material")
    {
        value = productoTabField.value("material").toString();
        idMaterial = QString::number(materialList.indexOf(value) + 1);

        //SERIE
        serieList.clear();
        sqlQuery = "CALL get_DependentDropDownMenu(";
        sqlQuery.append("'serie', 'serie', 'id_metal', ").append(idMaterial).append(");");
        //qDebug() << "sqlQuery for serieList" << sqlQuery;
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            serieList.append(result.value(0).toString());
        }
        emit serieListChanged();
        //qDebug() << "serieList: " << serieList;

        //ALEACION
        aleacionList.clear();
        sqlQuery = "CALL get_DependentDropDownMenu('alloy', '";
        sqlQuery.append(aleacionRadioButton).append("', 'id_metal', ").append(idMaterial).append(");");
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            aleacionList.append(result.value(0).toString());
        }
        emit aleacionListChanged();
        //qDebug() << "aleacionList: " << aleacionList;

        //TEMPLE
        templeList.clear();
        sqlQuery = "CALL get_DependentDropDownMenu(";
        sqlQuery.append("'temper', 'temper', 'id_metal', ").append(idMaterial).append(");");
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            templeList.append(result.value(0).toString());
        }
        emit templeListChanged();
        //qDebug() << "templeList: " << templeList;

        //ACABADO
        acabadoList.clear();
        sqlQuery = "CALL get_DependentDropDownMenu(";
        sqlQuery.append("'finition', 'finition', 'id_metal', ").append(idMaterial).append(");");
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            acabadoList.append(result.value(0).toString());
        }
        emit acabadoListChanged();
        //qDebug() << "acabadoList: " << acabadoList;
    }
}
void AddSupplier::fillComboBoxesFromDb(QString tab)
{
    //Unicamente se llama una vez para cada pestaña -empresa, contactos, productos-
    //Los resultados NO se actualizan en f(selección usuario)
    //qDebug() << "Se ha llamado a la función: " << __FUNCTION__ <<"(" << tab << ")";

    QSqlQuery result; //sirve para todas las consultas

    if(tab == "empresa") //Se carga desde el constructor
    {
        QString sqlQuery = "CALL get_DropDownMenu('country', 'country')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            paisList.append(result.value(0).toString());
        }
        emit paisListChanged(); //Para "empresa" no hace falta pues al crearse el comboBox ya tenemos listo el modelo con los datos
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('activity', 'activity')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            actividadList.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('payment', 'payment')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            formaPagoList.append(result.value(0).toString());
        }
    }
    else if (tab == "contactos") //Se llama desde JS, al actualizarse el TabBar
    {
        QString sqlQuery = "CALL get_DropDownMenu('department', 'department')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            areaList.append(result.value(0).toString());
        }
        emit areaListChanged();
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('position', 'position')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            puestoList.append(result.value(0).toString());
        }
        emit puestoListChanged();
    }
    else if(tab == "productos") //Se llama desde JS, al actualizarse el TabBar
    {
        QString sqlQuery = "CALL get_DropDownMenu('type', 'type')"; //Tipo
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            tipoList.append(result.value(0).toString());
        }
        emit tipoListChanged();
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('metal', 'metal')"; //Material
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            materialList.append(result.value(0).toString());
        }
        emit materialListChanged();
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('serie', 'serie')"; //Serie -se utiliza como apoyo-
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            serieListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenuComplete('alloy', 'aisi')"; //AISI -se utiliza como apoyo-
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            aleacionListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenuComplete('temper', 'temper')"; //Temple -se utiliza como apoyo-
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            templeListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenuComplete('finition', 'finition')"; //Acabado -se utiliza como apoyo-
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            acabadoListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenuComplete('format', 'format')"; //Formato -se utiliza como apoyo-
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            formatoListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('inner_diameter', 'inner_diameter')"; //I.D.
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            idBobinaList.append(result.value(0).toString());
        }
        emit idBobinaListChanged();
    }
    else if (tab == "servicios") //Se llama desde JS, al actualizarse el TabBar
    {
        QString sqlQuery = "CALL get_DropDownMenu('servicing', 'servicing')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            servicioList.append(result.value(0).toString());
        }
        emit servicioListChanged();
        //qDebug() << "servicioList. " << servicioList;
    }
}
bool AddSupplier::sanitationCheck(QString tab)
{
    if(tab == "empresa")
    {
        //Checking key fields & numeric fields are not empty
        if(empresaTabField.value("empresa").toString().isEmpty()     ||
            empresaTabField.value("ciudad").toString().isEmpty()        ||
            empresaTabField.value("actividad").toString().isEmpty()    ||
            empresaTabField.value("formaPago").toString().isEmpty() ||
            empresaTabField.value("pais").toString().isEmpty())
            return EXIT_FAILURE;
        else
        {
            MainWindow::sanitationUserInput(empresaTabField);
            return EXIT_SUCCESS;
        }
    }
    else if (tab == "contacto")
    {
        //Checking key fields & numeric fields are not empty
        if(empresaTabField.value("empresa").toString().isEmpty()     || //Hay que controlarlo en todas las tabs
            contactoTabField.value("nombre").toString().isEmpty()      ||
            contactoTabField.value("email").toString().isEmpty()         ||
            contactoTabField.value("area").toString().isEmpty()           ||
            contactoTabField.value("puesto").toString().isEmpty())
            return EXIT_FAILURE;
        else
        {
            MainWindow::sanitationUserInput(contactoTabField);
            return EXIT_SUCCESS;
        }
    }
    else if (tab == "producto")
    {
        if(empresaTabField.value("empresa").toString().isEmpty()     || //Hay que controlarlo en todas las tabs
            productoTabField.value("tipo").toString().isEmpty()           ||
            productoTabField.value("material").toString().isEmpty()    ||
            aleacionSelectionList.isEmpty() ||
            templeSelectionList.isEmpty() ||
            acabadoSelectionList.isEmpty())
            return EXIT_FAILURE;
        else
            MainWindow::sanitationUserInput(productoTabField);

        //Prepare fields before SQL Query
        if(productoTabField.value("tipo") == "Bobina")
        {
            if(formatoBobinaSelectionList.isEmpty() || idBobinaSelectionList.isEmpty())
                return EXIT_FAILURE;
            else
            {
                if(productoTabField.value("espesorMin").toString().isEmpty())
                    productoTabField.insert("espesorMin",  "NULL");
                if(productoTabField.value("espesorMax").toString().isEmpty())
                    productoTabField.insert("espesorMax",  "NULL");
                productoTabField.insert("diametroMin",  "NULL");
                productoTabField.insert("diametroMax",  "NULL");
                productoTabField.insert("largoMin",  "NULL");
                productoTabField.insert("largoMax",  "NULL");
                productoTabField.insert("diametroIntMin",  "NULL");
                productoTabField.insert("diametroIntMax",  "NULL");
                productoTabField.insert("diametroExtMin",  "NULL");
                productoTabField.insert("diametroExtMax",  "NULL");
            }
        }
        else if(productoTabField.value("tipo").toString() == "Chapa" || productoTabField.value("tipo").toString() == "Plancha")
        {
            if(formatoChapaSelectionList.isEmpty())
                return EXIT_FAILURE;
            else
            {
                if(productoTabField.value("espesorMin").toString().isEmpty())
                    productoTabField.insert("espesorMin",  "NULL");
                if(productoTabField.value("espesorMax").toString().isEmpty())
                    productoTabField.insert("espesorMax",  "NULL");
                productoTabField.insert("diametroMin",  "NULL");
                productoTabField.insert("diametroMax",  "NULL");
                productoTabField.insert("largoMin",  "NULL");
                productoTabField.insert("largoMax",  "NULL");
                productoTabField.insert("diametroIntMin",  "NULL");
                productoTabField.insert("diametroIntMax",  "NULL");
                productoTabField.insert("diametroExtMin",  "NULL");
                productoTabField.insert("diametroExtMax",  "NULL");
            }
        }
        else if(productoTabField.value("tipo").toString() == "Barra")
        {
            if(productoTabField.value("diametroMin").toString().isEmpty())
                productoTabField.insert("diametroMin",  "NULL");
            if(productoTabField.value("diametroMax").toString().isEmpty())
                productoTabField.insert("diametroMax",  "NULL");
            if(productoTabField.value("largoMin").toString().isEmpty())
                productoTabField.insert("largoMin",  "NULL");
            if(productoTabField.value("largoMax").toString().isEmpty())
                productoTabField.insert("largoMax",  "NULL");
            productoTabField.insert("espesorMin",  "NULL");
            productoTabField.insert("espesorMax",  "NULL");
            productoTabField.insert("diametroIntMin",  "NULL");
            productoTabField.insert("diametroIntMax",  "NULL");
            productoTabField.insert("diametroExtMin",  "NULL");
            productoTabField.insert("diametroExtMax",  "NULL");
        }
        else if(productoTabField.value("tipo").toString() == "Tubo")
        {
            productoTabField.insert("espesorMin",  "NULL");
            productoTabField.insert("espesorMax",  "NULL");
            productoTabField.insert("diametroMin",  "NULL");
            productoTabField.insert("diametroMax",  "NULL");
            if(productoTabField.value("largoMin").toString().isEmpty())
                productoTabField.insert("largoMin",  "NULL");
            if(productoTabField.value("largoMax").toString().isEmpty())
                productoTabField.insert("largoMax",  "NULL");
            if(productoTabField.value("diametroIntMin").toString().isEmpty())
                productoTabField.insert("diametroIntMin",  "NULL");
            if(productoTabField.value("diametroIntMax").toString().isEmpty())
                productoTabField.insert("diametroIntMax",  "NULL");
            if(productoTabField.value("diametroExtMin").toString().isEmpty())
                productoTabField.insert("diametroExtMin",  "NULL");
            if(productoTabField.value("diametroExtMax").toString().isEmpty())
                productoTabField.insert("diametroExtMax",  "NULL");
        }
        else if(productoTabField.value("tipo").toString() == "Disco")
        {
            if(productoTabField.value("diametroMin").toString().isEmpty())
                productoTabField.insert("diametroMin",  "NULL");
            if(productoTabField.value("diametroMax").toString().isEmpty())
                productoTabField.insert("diametroMax",  "NULL");
            if(productoTabField.value("espesorMin").toString().isEmpty())
                productoTabField.insert("espesorMin",  "NULL");
            if(productoTabField.value("espesorMax").toString().isEmpty())
                productoTabField.insert("espesorMax",  "NULL");
            productoTabField.insert("largoMin",  "NULL");
            productoTabField.insert("largoMax",  "NULL");
            productoTabField.insert("diametroIntMin",  "NULL");
            productoTabField.insert("diametroIntMax",  "NULL");
            productoTabField.insert("diametroExtMin",  "NULL");
            productoTabField.insert("diametroExtMax",  "NULL");
        }
        return EXIT_SUCCESS;
    }
    else if (tab == "servicio")
    {
        //Checking key fields & numeric fields are not empty
        if(empresaTabField.value("empresa").toString().isEmpty()     || //Hay que controlarlo en todas las tabs
            servicioSelectionList.isEmpty())
            return EXIT_FAILURE;
        if(servicioSelectionList.contains("Slitting") &&
            servicioTabField.value("espesorMin1").toString().isEmpty() &&
            servicioTabField.value("espesorMin2").toString().isEmpty() &&
            servicioTabField.value("espesorMin3").toString().isEmpty())
            return EXIT_FAILURE;

        else
        {
            //Si se deja vacio EspesorMin se anula el registro completo
            if(servicioTabField.value("espesorMin1").toString().isEmpty())
            {
                servicioTabField.insert("espesorMin1",  "NULL");
                servicioTabField.insert("espesorMax1",  "NULL");
                servicioTabField.insert("anchoMin1",  "NULL");
                servicioTabField.insert("anchoMax1",  "NULL");
            }
            if(servicioTabField.value("espesorMin2").toString().isEmpty())
            {
                servicioTabField.insert("espesorMin2",  "NULL");
                servicioTabField.insert("espesorMax2",  "NULL");
                servicioTabField.insert("anchoMin2",  "NULL");
                servicioTabField.insert("anchoMax2",  "NULL");
            }
            if(servicioTabField.value("espesorMin3").toString().isEmpty())
            {
                servicioTabField.insert("espesorMin3",  "NULL");
                servicioTabField.insert("espesorMax3",  "NULL");
                servicioTabField.insert("anchoMin3",  "NULL");
                servicioTabField.insert("anchoMax3",  "NULL");
            }

            if(servicioTabField.value("espesorMax1").toString().isEmpty())
                servicioTabField.insert("espesorMax1",  "NULL");
            if(servicioTabField.value("espesorMax2").toString().isEmpty())
                servicioTabField.insert("espesorMax2",  "NULL");
            if(servicioTabField.value("espesorMax3").toString().isEmpty())
                servicioTabField.insert("espesorMax3",  "NULL");

            if(servicioTabField.value("anchoMin1").toString().isEmpty())
                servicioTabField.insert("anchoMin1",  "NULL");
            if(servicioTabField.value("anchoMin2").toString().isEmpty())
                servicioTabField.insert("anchoMin2",  "NULL");
            if(servicioTabField.value("anchoMin3").toString().isEmpty())
                servicioTabField.insert("anchoMin3",  "NULL");

            if(servicioTabField.value("anchoMax1").toString().isEmpty())
                servicioTabField.insert("anchoMax1",  "NULL");
            if(servicioTabField.value("anchoMax2").toString().isEmpty())
                servicioTabField.insert("anchoMax2",  "NULL");
            if(servicioTabField.value("anchoMax3").toString().isEmpty())
                servicioTabField.insert("anchoMax3",  "NULL");

            if(servicioTabField.value("catalogo").toString().isEmpty())
                servicioTabField.insert("catalogo",  "NULL");

            MainWindow::sanitationUserInput(servicioTabField);
            return EXIT_SUCCESS;
        }
    }
}
void AddSupplier::resetFields(QString tab)
{
    if(tab == "empresa")
    {
         //Solo se ejecuta al Cancalear/Guardar, pues borrariamos el textField "Empresa"
        this->setEmpresaTabField("clearAll", "");
        //Reset comboBoxes
        QObject *object = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("pais");
        QQmlProperty::write(object, "currentIndex", -1);
        object = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("actividad");
        QQmlProperty::write(object, "currentIndex", -1);
        object = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("formaPago");
        QQmlProperty::write(object, "currentIndex", -1);
    }
    else if(tab == "contacto")
    {
        //Delete textFields
        this->setContactoTabField("clearAll", "");
        //Reset comboBoxes
        QObject *object = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("area");
        QQmlProperty::write(object, "currentIndex", -1);
        object = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("puesto");
        QQmlProperty::write(object, "currentIndex", -1);
    }
    else if(tab == "producto")
    {
        //Delete textFields
        this->setProductoTabField("clearAll", "");
        //Reset comboBoxes
        QObject *object = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("tipo");
        QQmlProperty::write(object, "currentIndex", -1);
        object = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("material");
        QQmlProperty::write(object, "currentIndex", -1);

        this->uncheckAllValues("serie");
        this->uncheckAllValues("aleacion");
        this->uncheckAllValues("temple");
        this->uncheckAllValues("acabado");
        this->uncheckAllValues("anchoBobina");
        this->uncheckAllValues("diametroIntBobina");
        this->uncheckAllValues("formatoChapa");
    }
    else if(tab == "servicio")
    {
        //Delete textFields
        this->setServicioTabField("clearAll", "");
        //Reset comboBoxes
        this->uncheckAllValues("servicio");
    }
}

//PUBLIC SLOTS
bool AddSupplier::onAceptarButton(QString tab)
{
//    qDebug() << "Se ha llamado a la función: " << __FUNCTION__ <<"(" << tab << ")";

    if(tab == "empresa")
    {
        if (this->sanitationCheck(tab) == EXIT_FAILURE)
        {
            errorMessage = new QErrorMessage;
            errorMessage->setAttribute(Qt::WA_DeleteOnClose);
            errorMessage->showMessage(QObject::tr("Revise que los campos obligatorios no estén vacios!"));
            errorMessage->resize(400,200);
            return EXIT_FAILURE;
        }

        //Retrieve index from ComboBoxes -no pueden estar vacios pues romperian la SQL query -
        //El index de xxxList empieza en 0, pero los registros de la DB en 1 => +1
        QString idActividad = QString::number (actividadList.indexOf(empresaTabField.value("actividad").toString()) +1);
        QString idPais = QString::number (paisList.indexOf(empresaTabField.value("pais").toString()) +1);
        QString idFormaPago = QString::number (formaPagoList.indexOf(empresaTabField.value("formaPago").toString()) +1);

        //OPTION #1: Stored Procedures
        QString sqlQuery = "CALL insert_Supplier(";
        sqlQuery.append("'").append(empresaTabField.value("empresa").toString()).append("', '")
        .append(empresaTabField.value("holding").toString()).append("', ")
        .append(idActividad).append(", '") //number, sin ' '
        .append(empresaTabField.value("web").toString()).append("', '")
        .append(empresaTabField.value("panjiba").toString()).append("', '")
        .append(empresaTabField.value("maps").toString()).append("', ")
        .append(idPais).append(", '")//number, sin ' '
        .append(empresaTabField.value("ciudad").toString()).append("', '")
        .append(empresaTabField.value("postcode").toString()).append("', '") //varchar
        .append(empresaTabField.value("moq").toString()).append("', '")  //varchar
        .append(empresaTabField.value("notasEmpresa").toString()).append("', ")
        .append(idFormaPago).append(");"); //number, sin ' '
        qDebug() << "Stored Procedure: " << sqlQuery;

        if(MainWindow::executeForwardSql(sqlQuery, MAIN_DB_CONNECTION_NAME) == EXIT_SUCCESS)
        {
            QMessageBox::information(Q_NULLPTR, "Database", "La empresa se ha dado de alta",QMessageBox::Ok);
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;

        /* OPTION #2: Qt Function
             //Database connection
             auto tmp = QSqlDatabase::database(MAIN_DB_CONNECTION_NAME);
             if(!tmp.isOpen())
                 throw(tmp.lastError());
             QSqlQuery query(tmp);
             QString text = "INSERT INTO sellblaster.company (company, holding, website, country, town,"
                                     "postcode, description, comments) VALUES (:company, :holding, :website, :country,"
                                     ":town, :postcode, :description, :comments)";

             query.prepare(text);
             query.bindValue(":company", ui->empresaLineEdit->text());
             query.bindValue(":holding", ui->holdingLineEdit->text());
             query.bindValue(":website", ui->webLineEdit->text());
             query.bindValue(":country", ui->paisComboBox->currentText());
             query.bindValue(":town", ui->ciudadLineEdit->text());
             query.bindValue(":postcode", ui->postalCodeLineEdit->text());
             query.bindValue(":description", ui->descripcionTextEdit->toPlainText());
             query.bindValue(":comments", ui->notasTextEdit->toPlainText());

             if(!query.exec())
                 throw(query.lastError()); */
    }
    else if (tab == "contacto")
    {
        if (this->sanitationCheck(tab) == EXIT_FAILURE)
        {
            errorMessage = new QErrorMessage;
            errorMessage->setAttribute(Qt::WA_DeleteOnClose);
            errorMessage->showMessage(QObject::tr("Revise que los campos obligatorios no estén vacios!"));
            errorMessage->resize(400,200);
            return EXIT_FAILURE;
        }

        //Retrieve index from ComboBoxes -no pueden estar vacios pues romperian la SQL query -
        QString idArea = QString::number (areaList.indexOf(contactoTabField.value("area").toString()) + 1);
        QString idPuesto = QString::number (puestoList.indexOf(contactoTabField.value("puesto").toString()) + 1);

        //OPTION #1: Stored Procedures
        QString sqlQuery = "CALL insert_Contact(";
        sqlQuery.append("'").append(empresaTabField.value("empresa").toString()).append("', '")
        .append(contactoTabField.value("nombre").toString()).append("', '")
        .append(contactoTabField.value("apellido").toString()).append("', '")
        .append(contactoTabField.value("email").toString()).append("', '")
        .append(contactoTabField.value("telefono").toString()).append("', '")
        .append(contactoTabField.value("movil").toString()).append("', ")
        .append(idArea).append(", ") //number, sin ' '
        .append(idPuesto).append(", '") //number, sin ' '
        .append(contactoTabField.value("notasContacto").toString()).append("');");
        qDebug() << "Stored Procedure: " << sqlQuery;

        if(MainWindow::executeForwardSql(sqlQuery, MAIN_DB_CONNECTION_NAME) == EXIT_SUCCESS)
        {
            resetFields(tab);
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }
    else if (tab == "producto")
    {
        if (this->sanitationCheck(tab) == EXIT_FAILURE)
        {
            errorMessage = new QErrorMessage;
            errorMessage->setAttribute(Qt::WA_DeleteOnClose);
            errorMessage->showMessage(QObject::tr("Revise que los campos obligatorios no estén vacios!"));
            errorMessage->resize(400,200);
            return EXIT_FAILURE;
        }

        //Retrieve index from ComboBoxes -no pueden estar vacios pues romperian la SQL query -
        QString idTipo = QString::number (tipoList.indexOf(productoTabField.value("tipo").toString()) + 1);
        QString idMaterial = QString::number (materialList.indexOf(productoTabField.value("material").toString()) + 1);

       //Retrieve indexes from ComboCheckBoxes
        QString idAleacion, idTemple, idAcabado, idDiametroInterior, idAncho, idLargo;
        for (auto aleacion : aleacionSelectionList)
            idAleacion.append(QString::number (aleacionListCompleta.indexOf(aleacion) + 1)).append(","); //la QString tiene que terminar con ','
         for(auto temple : templeSelectionList)
             idTemple.append(QString::number (templeListCompleta.indexOf(temple) + 1)).append(",");
       for(auto acabado : acabadoSelectionList)
           idAcabado.append(QString::number (acabadoListCompleta.indexOf(acabado) + 1)).append(",");

       if(productoTabField.value("tipo").toString() == "Bobina")
       {
           idLargo="NULL";
           for(auto formato : formatoBobinaSelectionList)
               idAncho.append(formato).append(",");

           for(auto diametroInterior : idBobinaSelectionList)
                idDiametroInterior.append(QString::number (idBobinaList.indexOf(diametroInterior) + 1)).append((","));
       }

       else if (productoTabField.value("tipo").toString() == "Chapa" || productoTabField.value("tipo").toString() == "Plancha")
       {
           idDiametroInterior="NULL";
           for(auto formato : formatoChapaSelectionList)
           {
               //Recuperar el ancho y largo del formato (1000x2000, 1250x2500,...)
               QStringList tmp = formato.split('x');
               idAncho.append(tmp.at(0));
               idLargo.append(tmp.at(1));
               idAncho.append(",");
               idLargo.append(",");
           }
       }

       else if (productoTabField.value("tipo").toString() == "Barra")
       {
           idAncho="NULL";
           idLargo="NULL";
           idDiametroInterior="NULL";
       }

       else if (productoTabField.value("tipo").toString() == "Tubo")
       {
           idAncho="NULL";
           idLargo="NULL";
           idDiametroInterior="NULL";
       }

       else if (productoTabField.value("tipo").toString() == "Disco")
       {
           idAncho="NULL";
           idLargo="NULL";
           idDiametroInterior="NULL";
       }

       //SQL Query
       QSqlQuery result;
        QString sqlQuery = "CALL insert_ProductList(";
        sqlQuery.append("'").append(empresaTabField.value("empresa").toString()).append("', ")
        .append(idTipo).append(", ")  //number
        .append(idMaterial).append(", ") //number
        .append("'").append(idAleacion).append("'").append(", ") //varchar (array)
        .append("'").append(idTemple).append("'").append(", ") //varchar (array)
        .append("'").append(idAcabado).append("'").append(", ") //varchar (array)
        .append("'").append(idDiametroInterior).append("'").append(", ") //varchar (array) - ⌀interior (bobinas)
        .append("'").append(idAncho).append("'").append(", ") //varchar (array) - Ancho (chapas, bobinas)
        .append("'").append(idLargo).append("'").append(", ")  //varchar (array) - Largo (chapas)
        .append(productoTabField.value("espesorMin").toString()).append(", ") //Espesor min (chapas, bobinas, discos)
        .append(productoTabField.value("espesorMax").toString()).append(", ") //Espesor max (chapas, bobinas, discos)
        .append(productoTabField.value("diametroMin").toString()).append(", ") //⌀min (discos, barras)
        .append(productoTabField.value("diametroMax").toString()).append(", ") //⌀max (discos, barras)
        .append(productoTabField.value("largoMin").toString()).append(", ") //Largo min (tubos, barras)
        .append(productoTabField.value("largoMax").toString()).append(", ") //Largo max (tubos, barras)
        .append(productoTabField.value("diametroIntMax").toString()).append(", ") //⌀interior min (tubos)
        .append(productoTabField.value("diametroIntMax").toString()).append(", ") //⌀interior max (tubos)
        .append(productoTabField.value("diametroExtMin").toString()).append(", ") //⌀exterior min (tubos)
        .append(productoTabField.value("diametroExtMax").toString()).append(");"); //⌀exterior max (tubos)
        qDebug() << sqlQuery;

        if(MainWindow::executeForwardSql(sqlQuery, MAIN_DB_CONNECTION_NAME) == EXIT_SUCCESS)
        {
            resetFields(tab);
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }
    else if (tab == "servicio")
    {
        if (this->sanitationCheck(tab) == EXIT_FAILURE)
        {
            errorMessage = new QErrorMessage;
            errorMessage->setAttribute(Qt::WA_DeleteOnClose);
            errorMessage->showMessage(QObject::tr("Revise que los campos obligatorios no estén vacios!"));
            errorMessage->resize(400,200);
            return EXIT_FAILURE;
        }

        //Retrieve indexes from ComboCheckBoxes
         QString idServicio;
         for (auto servicio : servicioSelectionList)
             idServicio.append(QString::number (servicioList.indexOf(servicio) + 1)).append(","); //OJO: QString termina en ','

        //If EspesorMin is NULL delete register to avoid empty rows in the DB
         QString idEspesorMin, idEspesorMax, idAnchoMin, idAnchoMax;
         if(servicioTabField.value("espesorMin1").toString() != "NULL")
         {
             idEspesorMin = servicioTabField.value("espesorMin1").toString().append(",");
             idEspesorMax = servicioTabField.value("espesorMax1").toString().append(",");
             idAnchoMin = servicioTabField.value("anchoMin1").toString().append(",");
             idAnchoMax = servicioTabField.value("anchoMax1").toString().append(",");
         }
         if(servicioTabField.value("espesorMin2").toString() != "NULL")
         {
             idEspesorMin.append(servicioTabField.value("espesorMin2").toString()).append(",");
             idEspesorMax.append(servicioTabField.value("espesorMax2").toString()).append(",");
             idAnchoMin.append(servicioTabField.value("anchoMin2").toString()).append(",");
             idAnchoMax.append(servicioTabField.value("anchoMax2").toString()).append(",");
         }
         if(servicioTabField.value("espesorMin3").toString() != "NULL")
         {
             idEspesorMin.append(servicioTabField.value("espesorMin3").toString()).append(",");
             idEspesorMax.append(servicioTabField.value("espesorMax3").toString()).append(",");
             idAnchoMin.append(servicioTabField.value("anchoMin3").toString()).append(",");
             idAnchoMax.append(servicioTabField.value("anchoMax3").toString()).append(",");
         }

//         qDebug() << "idEspesorMin" << idEspesorMin;
//         qDebug() << "idEspesorMax" << idEspesorMax;
//         qDebug() << "idAnchoMin" << idAnchoMin;
//         qDebug() << "idAnchoMax" << idAnchoMax;

        //OPTION #1: Stored Procedures
        QString sqlQuery = "CALL insert_ServiceList(";
        sqlQuery.append("'").append(empresaTabField.value("empresa").toString()).append("', '")
        .append(servicioTabField.value("catalogo").toString()).append("', '")
        .append(idServicio).append("', '")
        .append(idEspesorMin).append("', '")
        .append(idEspesorMax).append("', '")
        .append(idAnchoMin).append("', '")
        .append(idAnchoMax).append("');");
        qDebug() << "Stored Procedure: " << sqlQuery;

        if(MainWindow::executeForwardSql(sqlQuery, MAIN_DB_CONNECTION_NAME) == EXIT_SUCCESS)
        {
            resetFields(tab);
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }
}
void AddSupplier::onCancelarButton(void)
{
    PRINT_FUNCTION_NAME

    //Opción #1: Eliminar el Objeto
    delete uniqueInstance;

    /*Opción #2: Resetear todas las variables y los campos del formulario
    this->resetFields("empresa");
    this->resetFields("contactos");
    this->resetFields("productos");
    emit this->closeQmlInstance(); //trow in C++, catcher in QML
    reset los xxxList para que los comboBoxes no dupliquen sus campos tras cerrar y volver a abrir NewProveedor.qml */
}
void AddSupplier::onGuardarButton(QString tab)
{
    if(this->onAceptarButton(tab) == EXIT_SUCCESS)
        this->onCancelarButton();
}
void AddSupplier::onRelatedFieldUpdated(QString fieldName)
{
    //Se llama desde QML (onRadioButtonClicked) y desde textValueToBackEnd() en C++
    if(fieldName == "tipo")
    {
        this->uncheckAllValues("anchoBobina");
        this->uncheckAllValues("diametroIntBobina");
        this->uncheckAllValues("formatoChapa");
        fillRelatedComboBoxFromDb(fieldName);
    }
    else if(fieldName == "material")
    {
        //Al cambiar el material cambian los models de los comboBoxes pero NO los selectionList
        //Serie, aleación, temple y acabado => reset selectionList
        this->uncheckAllValues("aleacion");
        this->uncheckAllValues("temple");
        this->uncheckAllValues("acabado");
        fillRelatedComboBoxFromDb(fieldName);
    }
    else if(fieldName == "serie")
        fillRelatedComboCheckBoxFromDb(fieldName);
    else if(fieldName == "aisi" || fieldName == "werkstoff") //RadioButton
    {
        aleacionListCompleta.clear();
        aleacionRadioButton = fieldName;

        QSqlQuery result;
        QString sqlQuery = "CALL get_DropDownMenuComplete('alloy', '";
        sqlQuery.append(fieldName).append("')"); //Se utiliza como apoyo
        //qDebug() << sqlQuery;
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            aleacionListCompleta.append(result.value(0).toString());
        }
        aleacionList = aleacionListCompleta; //aleacionListCompleta se guarda para luego recuperar los ids sin consultar la DB
        emit aleacionListChanged();
        //Resetear la selección en los comboBoxes Serie y Aleación
        this->uncheckAllValues("serie");
        this->uncheckAllValues("aleacion");
    }
}
void AddSupplier::onCloseQmlInstance()
{
    this->onCancelarButton();
}

//SETTERS & GETTERS
void AddSupplier::setEmpresaTabField(const QString key, const QString value)
{
    if(key != "clearAll")
        empresaTabField.insert(key, QVariant(value));
    else
    {
        QMap<QString, QVariant>::iterator itr;
        for(itr = empresaTabField.begin(); itr != empresaTabField.end(); ++itr)
            empresaTabField.insert(itr.key(), "");
    }
    emit empresaTabFieldChanged();
}
void AddSupplier::setContactoTabField(const QString key, const QString value)
{
    if(key != "clearAll")
        contactoTabField.insert(key, QVariant(value));
    else
    {
        QMap<QString, QVariant>::iterator itr;
        for(itr = contactoTabField.begin(); itr != contactoTabField.end(); ++itr)
            contactoTabField.insert(itr.key(), "");
    }
    emit contactoTabFieldChanged();
}
void AddSupplier::setProductoTabField(const QString key, const QString value)
{
    if(key != "clearAll")
        productoTabField.insert(key, QVariant(value));
    else
    {
        QMap<QString, QVariant>::iterator itr;
        for(itr = productoTabField.begin(); itr != productoTabField.end(); ++itr)
            productoTabField.insert(itr.key(), "");
    }
    emit productoTabFieldChanged();
}
void AddSupplier::setServicioTabField(const QString key, const QString value)
{
    if(key != "clearAll")
        servicioTabField.insert(key, QVariant(value));
    else
    {
        QMap<QString, QVariant>::iterator itr;
        for(itr = servicioTabField.begin(); itr != servicioTabField.end(); ++itr)
            servicioTabField.insert(itr.key(), "");
    }
    emit servicioTabFieldChanged();
}


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

        connect(uniqueInstance, &AddSupplier::formFieldUpdated, uniqueInstance, &AddSupplier::onFormFieldUpdated);

        /* DEPRECATED:
         * Hemos encontrado otras maneras + sencillas, pero lo dejo pues explica como conectar los signals/slots
        Connect C++ to QML Signals / Slots
        engine->rootObjects() solo recupera los objetos instanciados con load (si utilizamos component.create() no funciona)
        Solo funciona para SLOTS definidos en archivo .qml que cargamos mediante engine->load
        QObject *contactosTabObject = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("ContactosTabForm");
        connect(uniqueInstance, SIGNAL(clearFormFields(QVariant)), contactosTabObject, SLOT(onClearContactosFields(QVariant)));
        QObject *productosTabObject = engine->rootObjects().value(AddSupplier::typeId)->findChild<QObject*> ("ProductosTabForm");
        connect(uniqueInstance, SIGNAL(clearFormFields(QVariant)), productosTabObject, SLOT(onClearProductosFields(QVariant)));

        Connect QML to C++ Signals/Slots
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
void AddSupplier::textValueToBackEnd(QString fieldName, QString text)
{
    PRINT_FUNCTION_NAME

    //Guarda los valores de los comboBoxes sin checkboxes y textFields
    if(text == "reset")
        formField.remove(fieldName); //resetear el valor pasado al cargar el modelo del comboBox
    else
        formField.insert(fieldName, text); //no puede haber 2 key iguales en el QMap

    //Cargar los comboBoxes relacionados
    if(fieldName == "tipo" || fieldName == "material")
        emit formFieldUpdated(fieldName);
}
void AddSupplier::textListToBackEnd(QString fieldName, QString text, bool value)
{
    PRINT_FUNCTION_NAME

    qDebug() << "fieldName: " << fieldName << ", text: " << text << ", value: " << value;

    if(fieldName == "serie")
    {
        if(value) serieSelectionList.append(text);
        else serieSelectionList.removeOne(text);
        emit formFieldUpdated(fieldName);
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
void AddSupplier::fillDependentComboCheckBoxFromDb(QString)
{
    //Ahora mismo solo cumple esta condición el comboBox Aleación
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
        QString str = serieIndexList.join(", ");
        //qDebug() << "serieIndexList: " << serieIndexList;

        sqlQuery = "CALL get_SerieDropDownMenu(";
        sqlQuery.append("'alloy', 'aisi', 'id_serie', '").append(str).append("');");
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
void AddSupplier::fillDependentComboBoxFromDb(QString comboBox)
{   
    QString value;
    QSqlQuery result;
    QString sqlQuery;
    QString idType, idMetal;

    if(comboBox == "tipo")
    {
        value = formField.value("tipo");

        if(value == "Bobina" || value == "Chapa" || value == "Plancha")
        {
            //Formato Chapa-Planch / Ancho Bobina (comparten el mismo)
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
            qDebug() << "formatoList: " << formatoList;
        }
    }
    else if(comboBox == "material")
    {
        value = formField.value("material");
        idMetal = QString::number(materialList.indexOf(value) + 1);
        //Serie
        serieList.clear();
        sqlQuery = "CALL get_DependentDropDownMenu(";
        sqlQuery.append("'serie', 'serie', 'id_metal', ").append(idMetal).append(");");
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            serieList.append(result.value(0).toString());
        }
        emit serieListChanged();
        qDebug() << "serieList: " << serieList;
        //Aleación
        aleacionList.clear();
        sqlQuery = "CALL get_DependentDropDownMenu(";
        sqlQuery.append("'alloy', 'aisi', 'id_metal', ").append(idMetal).append(");");
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            aleacionList.append(result.value(0).toString());
        }
        emit aleacionListChanged();
        qDebug() << "aleacionList: " << aleacionList;
        //Temple
        templeList.clear();
        sqlQuery = "CALL get_DependentDropDownMenu(";
        sqlQuery.append("'temper', 'temper', 'id_metal', ").append(idMetal).append(");");
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            templeList.append(result.value(0).toString());
        }
        emit templeListChanged();
        qDebug() << "templeList: " << templeList;
        //Acabado
        acabadoList.clear();
        sqlQuery = "CALL get_DependentDropDownMenu(";
        sqlQuery.append("'finition', 'finition', 'id_metal', ").append(idMetal).append(");");
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            acabadoList.append(result.value(0).toString());
        }
        emit acabadoListChanged();
        qDebug() << "acabadoList: " << acabadoList;
    }
}
void AddSupplier::fillComboBoxesFromDb(QString tab)
{
    //Unicamente se llama una vez para cada pestaña -empresa, contactos, productos-
    //Los resultados NO se actualizan en f(selección usuario)
    qDebug() << "Se ha llamado a la función: " << __FUNCTION__ <<"(" << tab << ")";

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
        sqlQuery = "CALL get_DropDownMenu('serie', 'serie')"; //Se utiliza como apoyo
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            serieListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('alloy', 'aisi')"; //Se utiliza como apoyo
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            aleacionListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('temper', 'temper')"; //Se utiliza como apoyo
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            templeListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('finition', 'finition')"; //Se utiliza como apoyo
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            acabadoListCompleta.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenu('format', 'format')"; //Se utiliza como apoyo
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
}
bool AddSupplier::sanitationCheck(QString tab)
{
    if(tab == "empresa")
    {
        //Checking key fields & numeric fields are not empty
        if(formField.value("empresa").isEmpty()     ||
            formField.value("ciudad").isEmpty()        ||
            formField.value("actividad").isEmpty()    ||
            formField.value("formaPago").isEmpty() ||
            formField.value("pais").isEmpty())
            return EXIT_FAILURE;
    }
    else if (tab == "contactos")
    {
        //Checking key fields & numeric fields are not empty
        if(formField.value("empresa").isEmpty() || //Hay que controlarlo en todas las tabs
            formField.value("nombre").isEmpty()     ||
            formField.value("email").isEmpty()     ||
            formField.value("area").isEmpty()       ||
            formField.value("puesto").isEmpty())
            return EXIT_FAILURE;
    }
    else if (tab == "productos")
    {
        if(formField.value("empresa").isEmpty() || //Hay que controlarlo en todas las tabs
            formField.value("tipo").isEmpty()  ||
            formField.value("material").isEmpty() ||
            aleacionSelectionList.isEmpty() ||
            templeSelectionList.isEmpty() ||
            acabadoSelectionList.isEmpty())
            return EXIT_FAILURE;
        if(formField.value("tipo") == "Bobina")
        {
            if(formatoBobinaSelectionList.isEmpty() || idBobinaSelectionList.isEmpty())
                return EXIT_FAILURE;
            else
            {
                //Prepare fields before SQL Query
                if(formField.value("espesorMin").isEmpty())
                    formField.insert("espesorMin",  "NULL");
                if(formField.value("espesorMax").isEmpty())
                    formField.insert("espesorMax",  "NULL");
                formField.insert("diametroMin",  "NULL");
                formField.insert("diametroMax",  "NULL");
                formField.insert("largoMin",  "NULL");
                formField.insert("largoMax",  "NULL");
                formField.insert("diametroIntMin",  "NULL");
                formField.insert("diametroIntMax",  "NULL");
                formField.insert("diametroExtMin",  "NULL");
                formField.insert("diametroExtMax",  "NULL");
            }
        }
        else if(formField.value("tipo") == "Chapa" || formField.value("tipo") == "Plancha")
        {
            if(formatoChapaSelectionList.isEmpty())
                return EXIT_FAILURE;
            else
            {
                //Prepare fields before SQL Query
                if(formField.value("espesorMin").isEmpty())
                    formField.insert("espesorMin",  "NULL");
                if(formField.value("espesorMax").isEmpty())
                    formField.insert("espesorMax",  "NULL");
                formField.insert("diametroMin",  "NULL");
                formField.insert("diametroMax",  "NULL");
                formField.insert("largoMin",  "NULL");
                formField.insert("largoMax",  "NULL");
                formField.insert("diametroIntMin",  "NULL");
                formField.insert("diametroIntMax",  "NULL");
                formField.insert("diametroExtMin",  "NULL");
                formField.insert("diametroExtMax",  "NULL");
            }
        }
        else if(formField.value("tipo") == "Barra")
        {
            if(formField.value("diametroMin").isEmpty())
                formField.insert("diametroMin",  "NULL");
            if(formField.value("diametroMax").isEmpty())
                formField.insert("diametroMax",  "NULL");
            if(formField.value("largoMin").isEmpty())
                formField.insert("largoMin",  "NULL");
            if(formField.value("largoMax").isEmpty())
                formField.insert("largoMax",  "NULL");
            formField.insert("espesorMin",  "NULL");
            formField.insert("espesorMax",  "NULL");
            formField.insert("diametroIntMin",  "NULL");
            formField.insert("diametroIntMax",  "NULL");
            formField.insert("diametroExtMin",  "NULL");
            formField.insert("diametroExtMax",  "NULL");
        }
        else if(formField.value("tipo") == "Tubo")
        {
            formField.insert("espesorMin",  "NULL");
            formField.insert("espesorMax",  "NULL");
            formField.insert("diametroMin",  "NULL");
            formField.insert("diametroMax",  "NULL");
            if(formField.value("largoMin").isEmpty())
                formField.insert("largoMin",  "NULL");
            if(formField.value("largoMax").isEmpty())
                formField.insert("largoMax",  "NULL");
            if(formField.value("diametroIntMin").isEmpty())
                formField.insert("diametroIntMin",  "NULL");
            if(formField.value("diametroIntMax").isEmpty())
                formField.insert("diametroIntMax",  "NULL");
            if(formField.value("diametroExtMin").isEmpty())
                formField.insert("diametroExtMin",  "NULL");
            if(formField.value("diametroExtMax").isEmpty())
                formField.insert("diametroExtMax",  "NULL");
        }
        else if(formField.value("tipo") == "Disco")
        {
            if(formField.value("diametroMin").isEmpty())
                formField.insert("diametroMin",  "NULL");
            if(formField.value("diametroMax").isEmpty())
                formField.insert("diametroMax",  "NULL");
            if(formField.value("espesorMin").isEmpty())
                formField.insert("espesorMin",  "NULL");
            if(formField.value("espesorMax").isEmpty())
                formField.insert("espesorMax",  "NULL");
            formField.insert("largoMin",  "NULL");
            formField.insert("largoMax",  "NULL");
            formField.insert("diametroIntMin",  "NULL");
            formField.insert("diametroIntMax",  "NULL");
            formField.insert("diametroExtMin",  "NULL");
            formField.insert("diametroExtMax",  "NULL");
        }
    }
    //Sanitation check of user' input
    MainWindow::sanitationUserInput(formField);
    return EXIT_SUCCESS;
}
void AddSupplier::resetFields(QString tab)
{
    if(tab == "empresa")
    {
        //Clear QMap values
        formField["empresa"].clear();
        formField["holding"].clear();
        formField["actividad"].clear();
        formField["web"].clear();
        formField["panjiba"].clear();
        formField["maps"].clear();
        formField["pais"].clear();
        formField["ciudad"].clear();
        formField["postcode"].clear();
        formField["moq"].clear();
        formField["notasEmpresa"].clear();
        formField["formaPago"].clear();

        //Clear form values using JavaScript
        emit clearFormFields(tab);
    }
    else if(tab == "contactos")
    {
        //Clear QMap values
        formField["nombre"].clear();
        formField["apellido"].clear();
        formField["email"].clear();
        formField["telefono"].clear();
        formField["movil"].clear();
        formField["notasContacto"].clear();
        formField["area"].clear();
        formField["puesto"].clear();

        //Clear form values using JavaScript
        emit clearFormFields(tab);
    }
    else if(tab == "productos")
    {
        //Clear QMap values
        formField["tipo"].clear();
        formField["material"].clear();
        formField["serie"].clear();
        formField["aleacion"].clear();
        formField["temple"].clear();
        formField["acabado"].clear();
        formField["diametroMinBarra"].clear();
        formField["diametroMaxBarra"].clear();
        formField["largoMinBarra"].clear();
        formField["largoMaxBarra"].clear();
        formField["anchoBobina"].clear();
        formField["espesorMinBobina"].clear();
        formField["espesorMaxBobina"].clear();
        formField["diametroIntBobina"].clear();
        formField["tipoChapa"].clear();
        formField["espesorMinChapa"].clear();
        formField["espesorMaxChapa"].clear();
        formField["diametroMinDisco"].clear();
        formField["diametroMaxDisco"].clear();
        formField["espesorMinDisco"].clear();
        formField["espesorMaxDisco"].clear();
        formField["diametroIntMinTubo"].clear();
        formField["diametroIntMaxTubo"].clear();
        formField["diametroExtMinTubo"].clear();
        formField["diametroExtMaxTubo"].clear();
        formField["largoMinTubo"].clear();
        formField["largoMaxTubo"].clear();


        //Clear form values using JavaScript
        emit clearFormFields(tab);
    }
}

//PUBLIC SLOTS
bool AddSupplier::onAceptarButton(QString tab)
{
    PRINT_FUNCTION_NAME
    qDebug() << "TAB: " << tab << " ---- <QMAPS> " << formField;

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
        QString idActividad = QString::number (actividadList.indexOf(formField.value("actividad")) +1);
        QString idPais = QString::number (paisList.indexOf(formField.value("pais")) +1);
        QString idFormaPago = QString::number (formaPagoList.indexOf(formField.value("formaPago")) +1);

        //OPTION #1: Stored Procedures
        QString sqlQuery = "CALL insert_Supplier(";
        sqlQuery.append("'").append(formField.value("empresa")).append("', '")
        .append(formField.value("holding")).append("', ")
        .append(idActividad).append(", '") //number, sin ' '
        .append(formField.value("web")).append("', '")
        .append(formField.value("panjiba")).append("', '")
        .append(formField.value("maps")).append("', ")
        .append(idPais).append(", '")//number, sin ' '
        .append(formField.value("ciudad")).append("', '")
        .append(formField.value("postcode")).append("', '") //varchar
        .append(formField.value("moq")).append("', '")  //varchar
        .append(formField.value("notasEmpresa")).append("', ")
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
    else if (tab == "contactos")
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
        QString idArea = QString::number (areaList.indexOf(formField.value("area")) + 1);
        QString idPuesto = QString::number (puestoList.indexOf(formField.value("puesto")) + 1);

        //OPTION #1: Stored Procedures
        QString sqlQuery = "CALL insert_Contact(";
        sqlQuery.append("'").append(formField.value("empresa")).append("', '")
        .append(formField.value("nombre")).append("', '")
        .append(formField.value("apellido")).append("', '")
        .append(formField.value("email")).append("', '")
        .append(formField.value("telefono")).append("', '")
        .append(formField.value("movil")).append("', ")
        .append(idArea).append(", ") //number, sin ' '
        .append(idPuesto).append(", '") //number, sin ' '
        .append(formField.value("notasContacto")).append("');");

        qDebug() << "Stored Procedure: " << sqlQuery;
        if(MainWindow::executeForwardSql(sqlQuery, MAIN_DB_CONNECTION_NAME) == EXIT_SUCCESS)
        {
            resetFields(tab);
            qDebug() << "Maps values: " << formField;
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }
    else if (tab == "productos")
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
        QString idTipo = QString::number (tipoList.indexOf(formField.value("tipo")) + 1);
        QString idMaterial = QString::number (materialList.indexOf(formField.value("material")) + 1);

        //Retrieve id_supplier (para no tener que buscarlo en cada Query)
        QString idSupplier;
        QSqlQuery result; //sirve para todas las consultas
        QString sqlQuery = "CALL get_IdFromRelatedTable('supplier', 'company', ";
        sqlQuery.append("'").append(formField.value("empresa")).append("');");
        qDebug() << "Stored Procedure: " << sqlQuery;
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result);
        while(result.next())
        {
            idSupplier.append(result.value(0).toString()); //QString instead of QStringList pues solo puede haber 1
        }
        qDebug() << "idSupplier: " << idSupplier;

       //Retrieve indexes from ComboCheckBoxes
        QString idAleacion, idTemple, idAcabado, idDiametroInterior, idAncho, idLargo;
        for (auto aleacion : aleacionSelectionList)
            idAleacion.append(QString::number (aleacionListCompleta.indexOf(aleacion) + 1)).append(","); //la QString tiene que terminar con ','
         for(auto temple : templeSelectionList)
             idTemple.append(QString::number (templeListCompleta.indexOf(temple) + 1)).append(",");
       for(auto acabado : acabadoSelectionList)
           idAcabado.append(QString::number (acabadoListCompleta.indexOf(acabado) + 1)).append(",");

       if(formField.value("tipo") == "Bobina")
       {
           idLargo="NULL";
           for(auto formato : formatoBobinaSelectionList)
               idAncho.append(formato).append(",");

           for(auto diametroInterior : idBobinaSelectionList)
                idDiametroInterior.append(QString::number (idBobinaList.indexOf(diametroInterior) + 1)).append((","));
       }

       else if (formField.value("tipo") == "Chapa" || formField.value("tipo") == "Plancha")
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

       else if (formField.value("tipo") == "Barra")
       {
           idAncho="NULL";
           idLargo="NULL";
           idDiametroInterior="NULL";
       }

       else if (formField.value("tipo") == "Tubo")
       {
           idAncho="NULL";
           idLargo="NULL";
           idDiametroInterior="NULL";
       }

       else if (formField.value("tipo") == "Disco")
       {
           idAncho="NULL";
           idLargo="NULL";
           idDiametroInterior="NULL";
       }

       //SQL Query
        sqlQuery = "CALL insert_ProductList(";
        sqlQuery.append(idSupplier).append(", ") //number
        .append(idTipo).append(", ")  //number
        .append(idMaterial).append(", ") //number
        .append("'").append(idAleacion).append("'").append(", ") //varchar (array)
        .append("'").append(idTemple).append("'").append(", ") //varchar (array)
        .append("'").append(idAcabado).append("'").append(", ") //varchar (array)
        .append("'").append(idDiametroInterior).append("'").append(", ") //varchar (array) - ⌀interior (bobinas)
        .append("'").append(idAncho).append("'").append(", ") //varchar (array) - Ancho (chapas, bobinas)
        .append("'").append(idLargo).append("'").append(", ")  //varchar (array) - Largo (chapas)
        .append(formField.value("espesorMin")).append(", ") //Espesor min (chapas, bobinas, discos)
        .append(formField.value("espesorMax")).append(", ") //Espesor max (chapas, bobinas, discos)
        .append(formField.value("diametroMin")).append(", ") //⌀min (discos, barras)
        .append(formField.value("diametroMax")).append(", ") //⌀max (discos, barras)
        .append(formField.value("largoMin")).append(", ") //Largo min (tubos, barras)
        .append(formField.value("largoMax")).append(", ") //Largo max (tubos, barras)
        .append(formField.value("diametroIntMax")).append(", ") //⌀interior min (tubos)
        .append(formField.value("diametroIntMax")).append(", ") //⌀interior max (tubos)
        .append(formField.value("diametroExtMin")).append(", ") //⌀exterior min (tubos)
        .append(formField.value("diametroExtMax")).append(");"); //⌀exterior max (tubos)
        qDebug() << sqlQuery;

        if(MainWindow::executeForwardSql(sqlQuery, MAIN_DB_CONNECTION_NAME) == EXIT_FAILURE)
        {
            QMessageBox::information(Q_NULLPTR, "Database", "ohhhh shiiiiiiiiiiit !!!",QMessageBox::Ok);
            return EXIT_FAILURE;
        }

        QMessageBox::information(Q_NULLPTR, "Database", "Se han añadido los registros a la Database.",QMessageBox::Ok);
        return EXIT_SUCCESS;
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
void AddSupplier::onFormFieldUpdated(QString fieldName)
{
    if(fieldName == "tipo" || fieldName == "material")
        fillDependentComboBoxFromDb(fieldName);
    else fillDependentComboCheckBoxFromDb(fieldName); //serie
}

//SETTERS & GETTERS


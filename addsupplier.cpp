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

        /* DEPRECATED:
         * Hemos encontrado otras maneras + sencillas, pero lo dejo pues explica como conectar los signals/slots
        Connect C++ to QML Signals / Slots
        engine->rootObjects() solo recupera los objetos instanciados con load (si utilizamos component.create() no funciona)
        Solo funciona para SLOTS definidos en archivo .qml que cargamos mediante engine->load
        QObject *contactosTabObject = engine->rootObjects().value(typeId)->findChild<QObject*> ("ContactosTabForm");
        connect(uniqueInstance, SIGNAL(clearFormFields(QVariant)), contactosTabObject, SLOT(onClearContactosFields(QVariant)));
        QObject *productosTabObject = engine->rootObjects().value(typeId)->findChild<QObject*> ("ProductosTabForm");
        connect(uniqueInstance, SIGNAL(clearFormFields(QVariant)), productosTabObject, SLOT(onClearProductosFields(QVariant)));

        Connect QML to C++ Signals/Slots
        connect(engine->rootObjects().value(typeId), SIGNAL(closing(CloseEvent)), uniqueInstance, SLOT(closeEvent(QCloseEvent*)));
        connect(engine->rootObjects().value(typeId), SIGNAL(closing(CloseEvent)), uniqueInstance, SLOT(onCloseEventCaller())); */

        qDebug() << "***** FINAL CREATE_COMPONENT ADDSUPPLIER *****";
    }
    else
    {
        //Load QML component
        engine = new QQmlApplicationEngine;
        engine->load(QUrl(QStringLiteral("qrc:/qml/NewProveedor.qml")));
    }
}
void AddSupplier::textValueToBackEnd(QString key, QString value)
{
    //Guarda todos los valores de los formFields: comboBoxes y textFields
    formField.insert(key, value); //no puede haber 2 key iguales en el QMap
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
void AddSupplier::fillComboBoxWithCheckBoxFromDb(void) //PENDING
{
    QSqlQuery result;

    QString sqlQuery = "CALL get_DropDownMenusData('norm', 'aisi')"; //table, column
    MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
    QStringList alloyList;
    while(result.next())
    {
        alloyList.append(result.value(0).toString());
    }
    qDebug() << "AISI list: " << alloyList;

    //auto alloyItemList = new checkBoxList(&alloyList, this);
    //ui->alloyComboBox->setModel(alloyItemList);

//    qDebug() << alloyItemList->rowCount();
//    qDebug() << alloyItemList->data(alloyItemList->index(3), Qt::DisplayRole).toString();
//    qDebug() << alloyItemList->data(alloyItemList->index(3), Qt::CheckStateRole).toString();

    //QStyle checkBoxComboStyle;

//    modelo = new QStandardItemModel(4, 1, this);
//    //ui->alloyComboBox->setModel(modelo);
//    //ui->alloyComboBox->setStyle(QStyleFactory::create("windows"));

//    iItem1 = new QStandardItem(QIcon::fromTheme("document-open"), "Abrir documento");
//    modelo->setItem(0,0, iItem1);
//    iItem1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    iItem1->setData(Qt::Unchecked, Qt::CheckStateRole);

//    iItem2 = new QStandardItem(QIcon::fromTheme("document-save"), "Guardar documento");
//    modelo->setItem(1,0, iItem2);
//    iItem2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    iItem2->setData(Qt::Unchecked, Qt::CheckStateRole);
//    //ui->alloyComboBox->setView(new QListView);
}
void AddSupplier::fillComboBoxesFromDb(QString tab)
{
    qDebug() << "Se ha llamado a la función: " << __FUNCTION__ <<"(" << tab << ")";
    //Fill drop-down menus with database values
    QSqlQuery result; //sirve para todas las consultas

    if(tab == "empresa") //Se carga desde el constructor
    {
        QString sqlQuery = "CALL get_DropDownMenusData('country', 'country')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            paisList.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenusData('activity', 'activity')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            actividadList.append(result.value(0).toString());
        }
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenusData('payment', 'payment')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            formaPagoList.append(result.value(0).toString());
        }
    }
    else if (tab == "contactos") //Se llama desde JS, al actualizarse el TabBar
    {
        QString sqlQuery = "CALL get_DropDownMenusData('department', 'department')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            areaList.append(result.value(0).toString());
        }
        emit areaListChanged();
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenusData('position', 'position')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            puestoList.append(result.value(0).toString());
        }
        emit puestoListChanged();
    }
    else if(tab == "productos")
    {
        QString sqlQuery = "CALL get_DropDownMenusData('type', 'type')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            formatoList.append(result.value(0).toString());
        }
        emit formatoListChanged();
        //qDebug() << "formatoList: " << formatoList;
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenusData('metal', 'metal')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            materialList.append(result.value(0).toString());
        }
        emit materialListChanged();
        //qDebug() << "materialList: " << materialList;
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenusData('treatment', 'treatment')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            tratamientoList.append(result.value(0).toString());
        }
        emit tratamientoListChanged();
        //qDebug() << "tratamientoList: " << tratamientoList;
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenusData('alloy', 'aisi')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            aleacionList.append(result.value(0).toString());
        }
        emit aleacionListChanged();
        //qDebug() << "aleacionList: " << aleacionList;
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenusData('temper', 'temper')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            templeList.append(result.value(0).toString());
        }
        emit templeListChanged();
        //qDebug() << "templeList: " << templeList;
        ////////////////////////////////////////////////////////////////
        sqlQuery = "CALL get_DropDownMenusData('finition', 'finition')";
        MainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
        while(result.next())
        {
            acabadoList.append(result.value(0).toString());
        }
        emit acabadoListChanged();
        //qDebug() << "acabadoList: " << acabadoList;
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
    else if (tab == "contacto")
    {
        //Checking key fields & numeric fields are not empty
        if(formField.value("empresa").isEmpty() || //Hay que controlarlo en todas las tabs
            formField.value("nombre").isEmpty()     ||
            formField.value("email").isEmpty()     ||
            formField.value("area").isEmpty()       ||
            formField.value("puesto").isEmpty())
            return EXIT_FAILURE;
    }
    //Sanitation check of user' input
    MainWindow::sanitationUserInput(formField);
    return EXIT_SUCCESS;
}
void AddSupplier::resetFields(QString tab)
{
    if(tab == "empresa")
    {
        QString xx = nullptr;
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
//SETTERS & GETTERS


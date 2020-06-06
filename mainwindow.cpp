#include "mainwindow.h"
#include "basic_headers.h"
#include "addsupplier.h"
#include "logindialog.h"

//PUBLIC MEMBERS
void MainWindow::createComponent(QQmlApplicationEngine *engine)
{
    if(uniqueInstance == Q_NULLPTR)
    {
        uniqueInstance = new MainWindow;
        registerSingleton();

        //Load QML component
        engine->load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));

        //Connect C++ to QML Signals / Slots
        //engine->rootObjects() solo recupera los objetos instanciados con load -no funciona para: component.create()-
        //Solo funciona para SLOTS definidos en archivo .qml que cargamos mediante engine->load
        //connect(uniqueInstance, SIGNAL(closeQmlInstance()), engine->rootObjects().value(typeId), SLOT(onCloseQmlInstance()));
    }
}
MainWindow::~MainWindow()
{
    PRINT_FUNCTION_NAME

    uniqueInstance = Q_NULLPTR;
}
bool MainWindow::executeForwardSql(const QString &sqlQuery, const QString &connectionName)
{
    //Execute SQL query without retrieving any values
    try
    {
        auto db = QSqlDatabase::database(connectionName);

         //Open db connection
        if (!db.open())
            throw(db.lastError()); //Exit through catch

        QSqlQuery tmpQuery(db);
        tmpQuery.setForwardOnly(true); //Attention !!
        if(!tmpQuery.exec(sqlQuery))
            throw (tmpQuery.lastError());
        return EXIT_SUCCESS;
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
        return EXIT_FAILURE;
    }
    catch (const QString &e)
    {
        EXCEPTION_HANDLER
        return EXIT_FAILURE;
    }
}
bool MainWindow::executeForwardSqlException(const QString &sqlQuery, const QString &connectionName)
{
    //Same as executeForwardSql() but without the -try/catch- to avoid endless loop when called from exceptions

    auto db = QSqlDatabase::database(connectionName);

     //Open db connection
    if (!db.open())
        return EXIT_FAILURE;

    QSqlQuery tmpQuery(db);
    tmpQuery.setForwardOnly(true); //Attention !!
    if(!tmpQuery.exec(sqlQuery))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
bool MainWindow::executeForwardSqlWithReturn(const QString &sqlQuery, const QString &connectionName, QSqlQuery &query)
{
    //Execute SQL query and returns result by reference (&query)
    try
    {
        auto db = QSqlDatabase::database(connectionName);

         //Open db connection
        if (!db.open())
            throw(db.lastError()); //Exit through catch

        QSqlQuery tmpQuery(db);
        tmpQuery.setForwardOnly(true); //Attention !!
        tmpQuery.exec(sqlQuery);
        if(!tmpQuery.isActive())
            throw (tmpQuery.lastError());
        query = tmpQuery; //return by reference
        return EXIT_SUCCESS;
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
        return EXIT_FAILURE;
    }
    catch (const QString &e)
    {
        EXCEPTION_HANDLER
        return EXIT_FAILURE;
    }
}
bool MainWindow::createMainDbConnection(const QMap<QString, QString>& connectionDetails)
{
    //Only for PSQL and MYSQL -SQLite has createInnerDbConnection() instead
    try
    {
        auto db(QSqlDatabase::addDatabase(MAIN_DB_TYPE, MAIN_DB_CONNECTION_NAME));

        /* Refactoring (cambio por la linea superior)
        QSqlDatabase db;
        if(connectionDetails["type"] == "QMYSQL")
        {
            QSqlDatabase dbTmp = QSqlDatabase::addDatabase("QMYSQL", DB_QMYSQL_CONNECTION_NAME);
            db = dbTmp;
        }
        else
        {
            QSqlDatabase dbTmp = QSqlDatabase::addDatabase("QPSQL", DB_QPSQL_CONNECTION_NAME);
            db = dbTmp;
        }
        */

        //Create and open connection to db
        db.setDatabaseName(connectionDetails["database"]);
        db.setUserName(connectionDetails["username"]);
        db.setPassword(connectionDetails["password"]);
        db.setHostName(connectionDetails["serverurl"]);
        if (!db.open())
            throw(db.lastError()); //Exit through catch
        return EXIT_SUCCESS;
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
        return EXIT_FAILURE;
    }
    catch (const QString &e)
    {
        EXCEPTION_HANDLER
        return EXIT_FAILURE;
    }
}
void MainWindow::sanitationUserInput(QMap<QString, QVariant>&userFields)
{
    //Comprobar que el usuario no haya escrito simbolos que puedan romper la consulta SQL
    for (auto &itr : userFields ) //pasar x referencia si vamos a modificar los valores del rango
    {
        itr.toString().remove(QChar('\"'));
        itr.toString().remove(QChar('\''));
    }
    /*DEPRECATED
    for (QMap<QString, QString>::iterator itr = userFields.begin(); itr != userFields.end(); ++itr)
    {
        itr.value().remove(QChar('\"'));
        itr.value().remove(QChar('\''));
    }
 */
}

//PRIVATE MEMBERS
MainWindow::MainWindow(QObject *parent) : QObject(parent) //PENDING StatusBar
{
    PRINT_FUNCTION_NAME
    //Retrieve persistent data from last user's sesion
   if(this->readUserSettings() == QSettings::AccessError)
        windowSize = this->get_screenResolution();
    //statusBar()->showMessage(QObject::tr("Ready"), 1500);
    }
void MainWindow::registerSingleton(void)
{
    qmlRegisterSingletonType<MainWindow>("MainClass", 1, 0, "MainWindowType",
        [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(scriptEngine)
        Q_UNUSED(engine)
        return uniqueInstance;
            });
}
void MainWindow::createInterDbConnection(void)
{
    try
    {
        //Create db connection with SQLite at start-up
         QSqlDatabase innerDb = QSqlDatabase::addDatabase("QSQLITE", DB_QSQLITE_CONNECTION_NAME);
         QString dbPath;
         dbPath.append(APPLICATION_PATH).append(SQLITE_RELATIVE_PATH); //absolute path for persistent SQLite database
          innerDb.setDatabaseName(dbPath); //databaseName

         //Open db connection
        if (!innerDb.open())
            throw(innerDb.lastError()); //Exit through catch

        //Create table and columns -only for the 1ft time-
        if(innerDb.tables().isEmpty())
        {
            QSqlQuery query(innerDb);
            //Importante: en SQLite3 si queremos que sea Auto-increment hay que definir el type como integer (no sirve int !!)
            query.exec("create table connection (selection int(1), id_connection integer primary key, "
                       "type varchar(20), username varchar(50), database varchar(50), serverurl varchar(50))");
            if(!query.isActive())
                throw (query.lastError());

            query.exec("create table exception (id_exception integer primary key, username varchar(50),"
                        "hostname varchar(100), operativesystem varchar(100), archivo varchar(50),"
                        "funcion varchar(100), line int, errortime varchar(100) , description text)");
            if(!query.isActive())
                throw (query.lastError());
        }
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
    }
    catch (const QString &e)
    {
        EXCEPTION_HANDLER
    }
}
QSize MainWindow::get_screenResolution(void)
{
    //Retrieve parameters from user's screen configuration
    QList <QScreen *> screenList = QGuiApplication::screens();
    if (screenList.count()== 1)
    {
        return screenList.at(0)->size();
    }
    return QSize(0,0);
}
QSettings::Status MainWindow::readUserSettings(void)
{
    PRINT_FUNCTION_NAME
    //Retrieve configuration from the last user's session
    QSettings userSettings(QObject::tr("Fx Team®"), QObject::tr("Sellblaster"));
    userSettings.beginGroup(QObject::tr("mainwindow"));
    windowSize = userSettings.value(QObject::tr("size")).toSize();
    windowPosition = userSettings.value(QObject::tr("position")).toPoint();
    userName = (userSettings.value(QObject::tr("username")).toString());
    userSettings.endGroup();
    return userSettings.status();
}
QSettings::Status MainWindow::writeUserSettings(void)
{
    PRINT_FUNCTION_NAME
    //Store configuration before closing the application
    QSettings userSettings(QObject::tr("Fx Team®"), QObject::tr("Sellblaster"));
    userSettings.beginGroup("mainwindow");
    userSettings.setValue(QObject::tr("size"), windowSize); //QSize
    userSettings.setValue(QObject::tr("position"), windowPosition); //QPoint
    userSettings.setValue(QObject::tr("username"), this->get_usernameFromDb());
    userSettings.endGroup();
    return userSettings.status();
}
QString MainWindow::get_usernameFromDb(void) //MAIN_DB_TYPE
{
    auto tmp = QSqlDatabase::database(MAIN_DB_CONNECTION_NAME); //returns connectionName
    QString user = tmp.userName();
    if(user.isEmpty())
        user = "empty";
    return user;
}

//PUBLIC SLOTS
void MainWindow::onAnadirProveedor(void)
{
    PRINT_FUNCTION_NAME

    //Hack to load comboBoxes from Database
    QPointer <AddSupplier> ptr = AddSupplier::createComponent(); //ptr gets detroyed at the {}
    ptr->fillComboBoxesFromDb("empresa");
}
void MainWindow::onActionExitTriggered(void)
{
//    emit this->close();
}
void MainWindow::onActionAddCompanyTriggered()
{
//    auto *addSupplierWidget = new AddSupplier(this);
//    addSupplierWidget->show();
//    addSupplierWidget->setAttribute(Qt::WA_DeleteOnClose);
}
void MainWindow::onClosingHandler() //PENDING Save before exit
{
    PRINT_FUNCTION_NAME
    writeUserSettings(); //Recupera los datos de Q_Property()
    //Falta que pregunte si hay que guardar los datos antes de salir
}

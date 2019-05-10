#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basic_headers.h"
#include "databasemanagement.h"
#include "addsupplier.h"
#include "logindialog.h"


//CONSTRUCTORS
mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    //Retrieve persistent data from last user's sesion
    if(this->readUserSettings() == QSettings::AccessError)
        this->resize(this->get_screenResolution()); //resize to full-screen

    this->createInterDbConnection();

    statusBar()->showMessage(QObject::tr("Ready"), 1500);

}
mainWindow::~mainWindow()
{
    delete ui;
}

//PUBLIC MEMBERS
bool mainWindow::executeForwardSql(const QString &sqlQuery, const QString &connectionName)
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
bool mainWindow::executeForwardSqlException(const QString &sqlQuery, const QString &connectionName)
{
    //Es idéntica pero sin el handler block -try/catch- pues se utiliza desde exceptions y sino podria entrar en un bucle infinito

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
bool mainWindow::executeForwardSqlWithReturn(const QString &sqlQuery, const QString &connectionName, QSqlQuery &query)
{
    //Execute SQL query and returns result by reference
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
bool mainWindow::createExternDbConnection(const QMap<QString, QString> connectionDetails)
{
    //Only for PSQL and MYSQL -SQLite has createInnerDbConnection() instead
    try
    {
        QSqlDatabase db;
        if(connectionDetails["type"] == "QMYSQL")
        {
            QSqlDatabase dbTmp = QSqlDatabase::addDatabase("QMYSQL", DB_QMYSQL_CONNECTION_NAME);
            db = dbTmp;
        }
        else
        {
            QSqlDatabase dbTmp = QSqlDatabase::addDatabase("QSQLITE", DB_QPSQL_CONNECTION_NAME);
            db = dbTmp;
        }

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
void mainWindow::sanitationUserInput(QMap<QString, QString>&userFields)
{
    for (auto &itr : userFields ) //pasar x referencia si vamos a modificar los valores del rango
    {
        itr.remove(QChar('\"'));
        itr.remove(QChar('\''));
    }
    /*DEPRECATED
    for (QMap<QString, QString>::iterator itr = userFields.begin(); itr != userFields.end(); ++itr)
    {
        itr.value().remove(QChar('\"'));
        itr.value().remove(QChar('\''));
    }
 */
}

//PROTECTED MEMBERS
void mainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->writeUserSettings();
}

//PRIVATE MEMBERS
void mainWindow::createInterDbConnection(void)
{
    try
    {
        //Create db connection with SQLite at start-up
         QSqlDatabase innerDb = QSqlDatabase::addDatabase("QSQLITE", DB_QSQLITE_CONNECTION_NAME);
         QString dbPath;
         dbPath.append(DIRECTORY_PATH).append(SQLITE_RELATIVE_PATH); //absolute path for persistent SQLite database
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
void mainWindow::createLoginDialog(void)
{
    auto login = new loginDialog(this);
    if(login->exec() == QDialog::Accepted)
        this->show();
}
QSize mainWindow::get_screenResolution(void)
{
    //Retrieve parameters from user's screen configuration
    QList <QScreen *> screenList = QGuiApplication::screens();
    if (screenList.count()== 1)
    {
        return screenList.at(0)->size();
    }
    else return QSize(0,0);
}
QSettings::Status mainWindow::readUserSettings(void)
{
    //Retrieve configuration from the last user's session
    QSettings userSettings(QObject::tr("Fx Team®"), QObject::tr("Sellblaster"));
    userSettings.beginGroup(QObject::tr("mainwindow"));
    this->resize(userSettings.value(QObject::tr("size")).toSize());
    this->move(userSettings.value(QObject::tr("position")).toPoint());
    userSettings.value(QObject::tr("fullScreen"));
    userSettings.endGroup();
    return userSettings.status();
}
QSettings::Status mainWindow::writeUserSettings(void)
{
    //Store configuration before closing the application
    QSettings userSettings(QObject::tr("Fx Team®"), QObject::tr("Sellblaster"));
    userSettings.beginGroup("mainwindow");
    userSettings.setValue(QObject::tr("size"), this->size()); //QSize
    userSettings.setValue(QObject::tr("position"), this->pos()); //QPoint
    userSettings.setValue(QObject::tr("fullScreen"), this->isFullScreen()); //bool
    userSettings.setValue(QObject::tr("username"), this->get_usernameFromDb());
    userSettings.endGroup();
    return userSettings.status();
}
QString mainWindow::get_usernameFromDb(void) //MAIN_DB_TYPE
{
    auto tmp = QSqlDatabase::database(MAIN_DB_CONNECTION_NAME); //returns connectionName
    QString user = tmp.userName();
    if(user.isEmpty())
        user = "empty";
    return user;
}
QString mainWindow::get_usernameFromQsettings(void) //static
{
    //Retrieve configuration from the last user's session
    QSettings userSettings(QObject::tr("Fx Team®"), QObject::tr("Sellblaster"));
    userSettings.beginGroup(QObject::tr("mainwindow"));
    QString userName = (userSettings.value(QObject::tr("username")).toString());
    userSettings.endGroup();
    return userName;
}

//PRIVATE SLOTS
void mainWindow::on_actionDatabases_triggered(void)
{
    if(dbManagementWidget.isNull())
        dbManagementWidget = new databaseManagement(this);
    dbManagementWidget->show();
}
void mainWindow::on_actionSalir_triggered(void)
{
    emit this->close();
}

void mainWindow::on_actionA_adir_empresa_triggered()
{
    auto *addSupplierWidget = new addSupplier(this);
    addSupplierWidget->show();
    addSupplierWidget->setAttribute(Qt::WA_DeleteOnClose);
}

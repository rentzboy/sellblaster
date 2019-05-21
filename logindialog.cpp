#include "logindialog.h"
#include "basic_headers.h"
#include "mainwindow.h"
#include <QQuickWindow>

//static initialization
LoginDialog* LoginDialog::uniqueInstance = Q_NULLPTR;
int LoginDialog::typeId = 0;

//PRIVATE CONSTRUCTOR
LoginDialog::LoginDialog(QObject *parent) : QObject(parent),
    errorMsg(QObject::tr("No se ha podido establecer la conexión")), errorVisible(false)
{
    PRINT_FUNCTION_NAME

    //Retrieve username from previous sesions -QSettings-
    this->setUsername(MainWindow::get_usernameFromQsettings());
}

//PRIVATE MEMBERS
void LoginDialog::registerSingleton(void)
{
    typeId = qmlRegisterSingletonType<LoginDialog>("LoginClass", 1, 0, "LoginDialog",
        [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
            Q_UNUSED(scriptEngine)
            Q_UNUSED(engine)
            return uniqueInstance;
            });
}
bool LoginDialog::sanitationCheck()
{
    QString name = getUsername();
    QString pass = getPassword();
    if(getUsername().isEmpty() || getPassword().isEmpty())
        return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}

//PROTECTED MEMBERS

//PUBLIC MEMBERS
void LoginDialog::createComponent(void)
{
    if(uniqueInstance == Q_NULLPTR)
    {
        uniqueInstance = new LoginDialog;
        registerSingleton();
    }

    //Load QML component
    auto *engine = new QQmlApplicationEngine;
    engine->load(QUrl(QStringLiteral("qrc:/qml/Login.qml")));

    //Connect C++ to QML Signals / Slots
    //engine->rootObjects() solo recupera los objetos instanciados con load (si utilizamos component.create() no funcionaria)
    connect(uniqueInstance, SIGNAL(closeQmlInstance()), engine->rootObjects().value(typeId), SLOT(onCloseQmlInstance()));
}

//PUBLIC SLOTS
void LoginDialog::onCancelarClicked(void)
{
    PRINT_FUNCTION_NAME
    QMetaObject::invokeMethod(qGuiApp, "quit", Qt::QueuedConnection);
    //qGuiApp->quit(); No funciona pues la App aun no ha entrado en el main event loop (app.exec())
}
void LoginDialog::onUsernameUpdated(QString value)
{
    PRINT_FUNCTION_NAME
    this->setUsername(value);
}
void LoginDialog::onPasswordUpdated(QString value)
{
    PRINT_FUNCTION_NAME
    this->setPassword(value);

}
void LoginDialog::onAceptarClicked(void) //PENDING ....
{
    PRINT_FUNCTION_NAME
    if(this->sanitationCheck() == EXIT_FAILURE)
        return;

    try
    {
        //Get connection details from SQLite3
        QSqlQuery result;
        QString sqlQuery = "SELECT * FROM connection WHERE type=";
        sqlQuery.append("'").append(MAIN_DB_TYPE).append("'").append(" LIMIT 1;");

        MainWindow::executeForwardSqlWithReturn(sqlQuery, DB_QSQLITE_CONNECTION_NAME, result); //Output arg.
        if(!result.next())
            throw result.lastError();
        int fieldName = result.record().indexOf("name");
        int fieldDb = result.record().indexOf("database");
        int fieldServer = result.record().indexOf("serverurl");

        QMap <QString, QString> connectionDetails;
        connectionDetails.insert("name", result.value(fieldName).toString());
        connectionDetails.insert("database", result.value(fieldDb).toString());
        connectionDetails.insert("serverurl", result.value(fieldServer).toString());
        connectionDetails.insert("username", this->getUsername());
        connectionDetails.insert("password", this->getPassword());
        connectionDetails.insert("type", MAIN_DB_TYPE);

        //Connect to MAIN_DB
        if (MainWindow::createExternDbConnection(connectionDetails) == EXIT_FAILURE)
            this->setErrorVisible(true);
        else
        {
            emit this->closeQmlInstance();
            MainWindow::createComponent();
        }
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
    }
}

//GETTERS & SETTERS
bool LoginDialog::getErrorVisible() const
{
    return errorVisible;
}
void LoginDialog::setErrorVisible(bool value)
{
    if(errorVisible != value)
    {
        errorVisible = value;
        emit errorVisibleChanged();
    }
}
QString LoginDialog::getErrorMsg() const
{
    return errorMsg;
}
void LoginDialog::setErrorMsg(const QString &value)
{
    if(errorMsg != value)
    {
        errorMsg = value;
        emit errorMsgChanged();
    }
}
QString LoginDialog::getPassword() const
{
    return password;
}
void LoginDialog::setPassword(const QString &value)
{
    PRINT_FUNCTION_NAME
    if(value != password)
    {
        password = value;
        emit passwordChanged();
    }
}
QString LoginDialog::getUsername() const
{
    return username;
}
void LoginDialog::setUsername(const QString &value)
{
    PRINT_FUNCTION_NAME
    if(value != username)
    {
        username = value;
        emit usernameChanged();
    }
}

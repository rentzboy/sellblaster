#include "logindialog.h"
#include "basic_headers.h"
#include "mainwindow.h"
#include <QCloseEvent>

//CONSTRUCTORS
LoginDialog::LoginDialog(QObject *parent) : QObject(parent),
    errorMsg(QObject::tr("No se ha podido establecer la conexión")), errorVisible(false)
{
    //Retrieve username from previous sesions -QSettings-
    this->setUsername(MainWindow::get_usernameFromQsettings());
}

//PROTECTED MEMBERS

//PRIVATE MEMBERS
bool LoginDialog::sanitationCheck()
{
    QString name = getUsername();
    QString pass = getPassword();
    if(getUsername().isEmpty() || getPassword().isEmpty())
        return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}

//PUBLIC SLOTS
void LoginDialog::onCancelarClicked(void)
{
    PRINT_FUNCTION_NAME
    QMetaObject::invokeMethod(qGuiApp, "quit", Qt::QueuedConnection);
    //qGuiApp->quit(); No funciona pues la App aun no ha entrado en el main event loop (app.exec())
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
        //PENDING ........else emit this->done(QDialog::Accepted);
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
    if(value != username)
    {
        username = value;
        emit usernameChanged();
    }
}

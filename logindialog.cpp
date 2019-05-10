#include "logindialog.h"
#include "ui_logindialog.h"
#include "basic_headers.h"
#include <QCloseEvent>

//CONSTRUCTORS
loginDialog::loginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    //Hide errorMsg
    ui->errorLabel->hide();
    //Retrieve username from previous sesions -QSettings-
    ui->userLineEdit->setText(mainWindow::get_usernameFromQsettings());
}
loginDialog::~loginDialog()
{
    delete ui;
}

//PROTECTED MEMBERS
void loginDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    ui->errorLabel->hide();

    if(this->result() != QDialog::Accepted)
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
    //qGuiApp->quit(); No funciona pues la App aun no ha entrado en el main event loop (app.exec())
}
void loginDialog::keyPressEvent(QKeyEvent *event)
{
    if(event == QKeySequence::Cancel)
        event->ignore();
}

//PRIVATE MEMBERS
QString loginDialog::get_username(void) const
{
    return ui->userLineEdit->text();
}
QString loginDialog::get_password(void) const
{
    return ui->passLineEdit->text();
}

//PRIVATE SLOTS
void loginDialog::on_buttonBox_rejected(void)
{
    emit this->close(); //NO utilizar done(QDialog::Rejected) pues se cerraria directamente sin pasar x CloseEvent()
}
void loginDialog::on_buttonBox_accepted(void)
{
    try
    {
        //Get connection details from SQLite3
        QSqlQuery result;
        QString sqlQuery = "SELECT * FROM connection WHERE type=";
        sqlQuery.append("'").append(MAIN_DB_TYPE).append("'").append(" LIMIT 1;");

        mainWindow::executeForwardSqlWithReturn(sqlQuery, DB_QSQLITE_CONNECTION_NAME, result); //Output arg.
        if(!result.next())
            throw result.lastError();
        int fieldName = result.record().indexOf("name");
        int fieldDb = result.record().indexOf("database");
        int fieldServer = result.record().indexOf("serverurl");

        QMap <QString, QString> connectionDetails;
        connectionDetails.insert("name", result.value(fieldName).toString());
        connectionDetails.insert("database", result.value(fieldDb).toString());
        connectionDetails.insert("serverurl", result.value(fieldServer).toString());
        connectionDetails.insert("username", this->get_username());
        connectionDetails.insert("password", this->get_password());
        connectionDetails.insert("type", MAIN_DB_TYPE);

        //Connect to MAIN_DB
        if (mainWindow::createExternDbConnection(connectionDetails) == EXIT_FAILURE)
            ui->errorLabel->show();
        else emit this->done(QDialog::Accepted);
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
    }
}

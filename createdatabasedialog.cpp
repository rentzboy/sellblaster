#include "createdatabasedialog.h"
#include "ui_createdatabasedialog.h"
#include "globals.h"
#include "excepciones.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

//CONSTRUCTORS
CreateDatabaseDialog::CreateDatabaseDialog(QWidget *parent) : QDialog(parent), ui(new Ui::createDatabaseDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    //Fill ComboBox with SQL drivers
    ui->typeComboBox->addItems(QSqlDatabase::drivers());
    //Hide errorMsg
    ui->errorLabel->hide();
}
CreateDatabaseDialog::~CreateDatabaseDialog()
{
    delete ui;
}

//PRIVATE MEMBERS
QString CreateDatabaseDialog::get_nameField(void) const
{
    return ui->nameLineEdit->text();
}
QString CreateDatabaseDialog::get_databaseField(void) const
{
    return ui->databaseLineEdit->text();
}
QString CreateDatabaseDialog::get_typeField(void) const
{
    return ui->typeComboBox->currentText();
}
QString CreateDatabaseDialog::get_serverField(void) const
{
    return ui->serverLineEdit->text();
}
bool CreateDatabaseDialog::sanitationCheck(void)
{
    if(this->get_nameField().isEmpty() | this->get_databaseField().isEmpty() | this->get_serverField().isEmpty())
        return  EXIT_FAILURE;
    return EXIT_SUCCESS;
}
bool CreateDatabaseDialog::saveToDb(const QString& connectionName)
{
    try
    {
        auto tmp = QSqlDatabase::database(connectionName);

        if(!tmp.isOpen())
            throw(tmp.lastError());

        QSqlQuery query(tmp);
        query.prepare("INSERT INTO connection (selection, id, type, name, database, serverurl)"
        "VALUES (:selection, :id, :type, :name, :database, :serverurl)");
        query.bindValue(":selection", 0);
        //id row is automatically filled since id int primary key
        query.bindValue(":type", this->get_typeField());
        query.bindValue(":name", this->get_nameField());
        query.bindValue(":database", this->get_databaseField());
        query.bindValue(":serverurl", this->get_serverField());
        if(!query.exec())
            throw(query.lastError());
        return EXIT_SUCCESS;
    }catch(const QSqlError &e)
    {
        EXCEPTION_HANDLER
        return EXIT_FAILURE;

    }catch (QString &e)
    {
        EXCEPTION_HANDLER
        return EXIT_FAILURE;
    }
}

//PRIVATE SLOTS
void CreateDatabaseDialog::on_CancelButton_clicked(void)
{
    emit this->close();
}
void CreateDatabaseDialog::on_okButton_clicked(void)
{
    //Check fields are not empty before
    if(this->sanitationCheck() == EXIT_FAILURE)
    {
        //Mostrar rellenar todos los campos
        ui->errorLabel->show();
        return;
    }
    //Insert data to db
    if(this->saveToDb(DB_QSQLITE_CONNECTION_NAME) == EXIT_FAILURE)
    {
       auto errorMsg = new QErrorMessage(this);
       errorMsg->showMessage(QObject::tr("No se ha podido guardar el registro en la database"));
    }
    else {
        emit this->close();
    }
}

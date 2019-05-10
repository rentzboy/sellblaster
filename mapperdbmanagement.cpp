#include "mapperdbmanagement.h"
#include "ui_mapperdbmanagement.h"
#include <globals.h>
#include "databasemanagement.h"
#include "excepciones.h"
#include <QDebug>
#include <QSqlError>

//CONSTRUCTORS
mapperDbManagement::mapperDbManagement(int row, QWidget *parent) :
    QDialog(parent), ui(new Ui::mapperDbManagement)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    //Fill ComboBox with SQL drivers
    ui->typeComboBox->addItems(QSqlDatabase::drivers());
    //this->setUpSqlTableModel("connection");
    this->mapFields(row);
}
mapperDbManagement::~mapperDbManagement()
{
    delete ui;
}

//PRIVATE MEMBERS
void mapperDbManagement::setUpSqlTableModel(const QString &tableName)
{
    try
    {
        //Retrieve db connectionName
        auto db = QSqlDatabase::database(DB_QSQLITE_CONNECTION_NAME);

        //Construct SQL model
        model = new QSqlTableModel(this, db);
        model->setEditStrategy(QSqlTableModel::OnRowChange); //cuando se actualizan los cambios de la db

        //Sets the database table on which the model operates
        model->setTable(tableName);
        if (model->lastError().isValid())
            throw(model->lastError());

        //Populates the model with data from the table
        model->select();
        if (model->lastError().isValid())
            throw(model->lastError());
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
    }
}
void mapperDbManagement::mapFields(int selectedRow)
{
    QSqlTableModel *model = static_cast<databaseManagement*>(this->parent())->get_model();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->nameLineEdit, model->fieldIndex("name"));
    mapper->addMapping(ui->typeComboBox, model->fieldIndex("type"));
    mapper->addMapping(ui->databaseLineEdit, model->fieldIndex("database"));
    mapper->addMapping(ui->serverLineEdit, model->fieldIndex("serverurl"));
    mapper->setCurrentIndex(selectedRow);

    delegate = new QStyledItemDelegate(model);
    mapper->setItemDelegate(delegate);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
}

void mapperDbManagement::on_PreviousButton_clicked()
{
    mapper->toPrevious();
}
void mapperDbManagement::on_NextButton_clicked()
{
    mapper->toNext();
}

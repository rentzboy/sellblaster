 #include "databasemanagement.h"
#include "ui_databasemanagement.h"
#include "basic_headers.h"
#include "createdatabasedialog.h"
#include "sqlitedelegate.h"
#include "mapperdbmanagement.h"

//CONSTRUCTORS
databaseManagement::databaseManagement(QWidget *parent) : QWidget(parent), ui(new Ui::databaseManagement)
{
    ui->setupUi(this);

    //CASO #1: Para modelos utilizando la clase standard QSqlTableModel
    this->setUpSqlTableModel("connection");
    this->setUpSqlTableView();
    this->refreshTableView("connection");

    //CASO #2: Para subclass de un modelo a partir de QAbstractTableModel -no es para este caso-
    //this->setUpSqliteModel();

    //CASO #3: Añadir delegate propio (para dibujar los checkbox en el TableView)
    delegate = new sqliteDelegate(this);
    ui->tableView->setItemDelegate(delegate);
}
databaseManagement::~databaseManagement()
{
    delete ui;
}

//PROTECTED MEBERS
void databaseManagement::contextMenuEvent(QContextMenuEvent *event)
{
    //Hay que configurar el widget mediante QWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
    event->accept();
    QMenu menu(this);
    menu.addAction(QObject::tr("Delete row"), this, &databaseManagement::deleteRow);
    menu.exec(event->globalPos());
}

//PRIVATE MEMBERS
void databaseManagement::setUpSqlTableModel(const QString &tableName)
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
void databaseManagement::setUpSqlTableView(void)
{
    //Asign a model to the View
    ui->tableView->setModel(model);
    if (model->lastError().isValid())
        throw(model->lastError());

    //Editing triggers(which actions will initiate the Delegate Editor)
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Construct the Selection model
    selection = new QItemSelectionModel(model,  this);
    ui->tableView->setSelectionModel(selection);

    //Enable Sorting using headers + call sortbycolumn()
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0,  Qt::AscendingOrder); //Sorting by Id

    //Selection type (by item, row, column)
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}
void databaseManagement::refreshTableView(const QString &tableName)
{
    try
    {
        //Sets the database table on which the model operates
        model->setTable(tableName);
        if (model->lastError().isValid())
            throw(model->lastError());

        //Populates the model with data from the table
        model->select();
        if (model->lastError().isValid())
            throw(model->lastError());

        //Show table
        ui->tableView->setModel(model);
        if (model->lastError().isValid())
            throw(model->lastError());

        ui->tableView->hideColumn(1); //hide id column
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
    }
}
void databaseManagement::setUpSqliteModel(void) //DEPRECATED
{
    //PROBLEMAS: No permite editar los checboxs, no muestra los headers bien,....
    //No veo lo de reimplementar un modelo a partir de QAbstractTableModel
    //pues se pierden muchas funciones que si tiene QSqlTableModel x ejemplo

    //Create reimplemented model and asign it to a view
    //adaptor = new sqliteModel(this, model);
    //ui->tableView->setModel(adaptor); //QAbstractTableModel no tiene definida lastError() ....

    //Editing triggers(which actions will initiate the Delegate Editor)
//    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::CurrentChanged);

    //Construct the Selection model
//    selection = new QItemSelectionModel(adaptor,  ui->tableView);
//    ui->tableView->setSelectionModel(selection);

    //Set up horizontal header of the view
//    adaptor->setHeaderData(0, Qt::Horizontal, "Selection", Qt::EditRole);
//    adaptor->setHeaderData(1, Qt::Horizontal, "Id", Qt::EditRole);
//    adaptor->setHeaderData(2, Qt::Horizontal, "Name", Qt::EditRole);
//    adaptor->setHeaderData(3, Qt::Horizontal, "Database", Qt::EditRole);
//    adaptor->setHeaderData(4, Qt::Horizontal, "ServerUrl", Qt::EditRole);
//    emit adaptor->headerDataChanged(Qt::Horizontal, 0, 4); //Importante

    //Enable Sorting using headers + call sortbycolumn()
//    ui->tableView->setSortingEnabled(true);
//    ui->tableView->sortByColumn(0,  Qt::AscendingOrder); //Sorting by Id
}

//PUBLIC MEMBERS
QSqlTableModel* databaseManagement::get_model(void) const
{
    return this->model;
}

//PRIVATE SLOTS
void databaseManagement::deleteRow(void)
{
    int row = selection->currentIndex().row();
    int column = 1; //id column

    //Retrieve id value from the selected row
    QString id = model->data(model->index(row, column, QModelIndex()), Qt::DisplayRole).toString();

    QString text = "DELETE FROM connection WHERE id=";
    text.append(id);
    text.append(";");

    //Execute & Refresh view
    mainWindow::executeForwardSql(text, DB_QSQLITE_CONNECTION_NAME);
    this->refreshTableView("connection");
}
void databaseManagement::on_addButton_clicked(void)
{
    auto createDatabaseDialogWidget = new createDatabaseDialog(this);
    createDatabaseDialogWidget->setAttribute(Qt::WA_DeleteOnClose);
    createDatabaseDialogWidget->exec();
    this->refreshTableView("connection");
}
void databaseManagement::on_editButton_clicked(void)
{
    int row = selection->currentIndex().row();
    auto mapper = new mapperDbManagement(row, this);
    mapper->show();
}
void databaseManagement::on_deleteButton_clicked(void)
{
    //Retrieve all selected rows, delete them and refrew view
    QString text = "DELETE FROM connection WHERE selection=1";
    mainWindow::executeForwardSql(text, DB_QSQLITE_CONNECTION_NAME);
    this->refreshTableView("connection");
}

//PUBLIC SLOTS


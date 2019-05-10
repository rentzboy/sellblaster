#include "addsupplier.h"
#include "ui_addsupplier.h"
#include "basic_headers.h"
#include "checkboxlist.h"
#include <QMap>

//CONSTRUCTORS
addSupplier::addSupplier(QWidget *parent) : QDialog(parent), ui(new Ui::addSupplier)
{
    ui->setupUi(this);
    this->fillComboBoxesFromDb();
    //fill ComboBox with checkboxes
    this->fillComboBoxWithCheckBoxFromDb();
    //PENDING

}
addSupplier::~addSupplier()
{
    delete ui;
}

//PROTECTED MEMBERS
void addSupplier::closeEvent(QCloseEvent *event)
{
    event->accept();
}

//PRIVATE MEMBERS
void addSupplier::fillComboBoxWithCheckBoxFromDb(void)
{
    QSqlQuery result;

    QString sqlQuery = "CALL get_DropDownMenusData('norm', 'aisi')"; //table, column
    mainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
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

    modelo = new QStandardItemModel(4, 1, this);
    ui->alloyComboBox->setModel(modelo);
    //ui->alloyComboBox->setStyle(QStyleFactory::create("windows"));

    iItem1 = new QStandardItem(QIcon::fromTheme("document-open"), "Abrir documento");
    modelo->setItem(0,0, iItem1);
    iItem1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    iItem1->setData(Qt::Unchecked, Qt::CheckStateRole);

    iItem2 = new QStandardItem(QIcon::fromTheme("document-save"), "Guardar documento");
    modelo->setItem(1,0, iItem2);
    iItem2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    iItem2->setData(Qt::Unchecked, Qt::CheckStateRole);
    //ui->alloyComboBox->setView(new QListView);
}
void addSupplier::fillComboBoxesFromDb(void)
{
    //Fill drop-down menus with database values
    QSqlQuery result; //sirve para todas las consultas

    QString sqlQuery = "CALL get_DropDownMenusData('country', 'country')";
    mainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
    QStringList paisList; //RAII managed
    while(result.next())
    {
        paisList.append(result.value(0).toString());
    }
    ui->paisComboBox->addItems(paisList);
    ui->paisComboBox->setCurrentIndex(-1);
    ////////////////////////////////////////////////////////////////
    sqlQuery = "CALL get_DropDownMenusData('activity', 'activity')";
    mainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
    QStringList activityList; //RAII managed
    while(result.next())
    {
        activityList.append(result.value(0).toString());
    }
    ui->activityComboBox->addItems(activityList);
    ui->activityComboBox->setCurrentIndex(-1);
    ////////////////////////////////////////////////////////////////
    sqlQuery = "CALL get_DropDownMenusData('department', 'department')";
    mainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
    QStringList areaList; //RAII managed
    while(result.next())
    {
        areaList.append(result.value(0).toString());
    }
    ui->areaComboBox->addItems(areaList);
    ui->areaComboBox->setCurrentIndex(-1);
    ////////////////////////////////////////////////////////////////
    sqlQuery = "CALL get_DropDownMenusData('position', 'position')";
    mainWindow::executeForwardSqlWithReturn(sqlQuery, MAIN_DB_CONNECTION_NAME, result); //Output arg.
    QStringList positionList; //RAII managed
    while(result.next())
    {
        positionList.append(result.value(0).toString());
    }
    ui->puestoComboBox->addItems(positionList);
    ui->puestoComboBox->setCurrentIndex(-1);
}
bool addSupplier::sanitationCheck(QString tag)
{
    if(tag == "empresa")
    {
        //1- Checking some fields are not empty
        if(ui->empresaLineEdit->text().isEmpty() |
            ui->activityComboBox->currentText().isEmpty() |
            ui->paisComboBox->currentText().isEmpty() |
            ui->ciudadLineEdit->text().isEmpty())
            return EXIT_FAILURE;

        //2- Sanitation of user' input
        userDataFields.clear();
        userDataFields.insert("company", ui->empresaLineEdit->text());
        userDataFields.insert("holding", ui->holdingLineEdit->text());
        userDataFields.insert("web", ui->webLineEdit->text());
        userDataFields.insert("panjiba", ui->panjibaLineEdit->text());
        userDataFields.insert("maps", ui->mapsLineEdit->text());
        userDataFields.insert("city", ui->ciudadLineEdit->text());
        userDataFields.insert("description", ui->descripcionTextEdit->toPlainText());
        userDataFields.insert("comments", ui->notasTextEdit->toPlainText());
        mainWindow::sanitationUserInput(userDataFields);
        return EXIT_SUCCESS;
    }
    else if (tag == "contacto")
    {
        //1- Checking some fields are not empty
        if(ui->empresaLineEdit->text().isEmpty() | //Hay que controlarlo en todas las tags
                ui->emailLineEdit->text().isEmpty())
            return EXIT_FAILURE;

        //2- Sanitation of user' input
        userDataFields.clear();
        userDataFields.insert("company", ui->empresaLineEdit->text());
        userDataFields.insert("nombre", ui->nombreLineEdit->text());
        userDataFields.insert("apellido", ui->apellidoLineEdit->text());
        userDataFields.insert("email", ui->emailLineEdit->text());
        userDataFields.insert("telefono", ui->telefonoLineEdit->text());
        userDataFields.insert("movil", ui->movilLineEdit->text());
        userDataFields.insert("notas", ui->contactoNotasTextEdit->toPlainText());
        mainWindow::sanitationUserInput(userDataFields);
        return EXIT_SUCCESS;
    }
    else
    {
        //Checking some fields are not empty
        if(ui->empresaLineEdit->text().isEmpty())  //Hay que controlarlo en todas las tags
            return EXIT_FAILURE;
        else return EXIT_SUCCESS;
    }
}
void addSupplier::empresaApplyButton(void)
{
    if (this->sanitationCheck("empresa") == EXIT_FAILURE)
    {
        errorMessage = new QErrorMessage(this);
        errorMessage->showMessage(QObject::tr("Revise que los campos obligatorios no estén vacios!"));
        errorMessage->resize(400,200);
        return;
    }
    try
    {
        //Retrieve index from ComboBoxes and & Sanitation for numeric values
        QString idActivity, idPayment, moq;
        int fieldValue= ui->activityComboBox->currentIndex();
        fieldValue == -1 ? idActivity = "null" : idActivity = QString::number(fieldValue+1);
        fieldValue= ui->pagoComboBox->currentIndex();
        fieldValue == -1 ? idPayment = "null" : idPayment = QString::number((fieldValue+1));
        ui->moqLineEdit->text().isEmpty() == true ? moq = "null" : moq = ui->moqLineEdit->text();

        //OPTION #1: Stored Procedures
        QString sqlQuery = "CALL insert_Supplier(";
        sqlQuery.append("'").append(userDataFields.value("company")).append("', '")
        .append(userDataFields.value("holding")).append("', ")
        .append(idActivity).append(", '") //number, sin ' '
        .append(userDataFields.value("web")).append("', '")
        .append(userDataFields.value("panjiba")).append("', '")
        .append(userDataFields.value("maps")).append("', '")
        .append(ui->paisComboBox->currentText()).append("', '")
        .append(userDataFields.value("city")).append("', '")
        .append(ui->postalCodeLineEdit->text()).append("', '")
        .append(userDataFields.value("description")).append("', ")
        .append(moq).append(", '")  //number, sin ' '
        .append(userDataFields.value("comments")).append("', ")
        .append(idPayment).append(");"); //number, sin ' '
        qDebug() << "Stored Procedure: " << sqlQuery;
        mainWindow::executeForwardSql(sqlQuery, MAIN_DB_CONNECTION_NAME);

        //OPTION #2: Qt Function
        /*//Database connection
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
    catch(const QSqlError &e)
    {
        EXCEPTION_HANDLER
    }
}
void addSupplier::contactoApplyButton(void)
{
    if(this->sanitationCheck("contacto") == EXIT_FAILURE)
    {
        errorMessage = new QErrorMessage(this);
        errorMessage->showMessage(QObject::tr("Revise que los campos obligatorios no estén vacios!"));
        errorMessage->resize(400,200);
        return;
    }
    try
    {
        //Retrieve index from ComboBoxes and & Sanitation for numeric values
        QString idArea, idPuesto;
        int fieldValue= ui->areaComboBox->currentIndex();
        fieldValue == -1 ? idArea = "null" : idArea = QString::number(fieldValue+1);
        fieldValue= ui->puestoComboBox->currentIndex();
        fieldValue == -1 ? idPuesto = "null" : idPuesto = QString::number((fieldValue+1));

        //OPTION #1: Stored Procedures
        QString sqlQuery = "CALL insert_Contact(";
        sqlQuery.append("'").append(userDataFields.value("company")).append("', '")
        .append(userDataFields.value("nombre")).append("', '")
        .append(userDataFields.value("apellido")).append("', '")
        .append(userDataFields.value("email")).append("', '")
        .append(userDataFields.value("telefono")).append("', '")
        .append(userDataFields.value("movil")).append("', ")
        .append(idArea).append(", ")
        .append(idPuesto).append(", '")
        .append(userDataFields.value("notas")).append("');");
        qDebug() << "Stored Procedure: " << sqlQuery;
        mainWindow::executeForwardSql(sqlQuery, MAIN_DB_CONNECTION_NAME);

        //OPTION #2: Qt Function
        /*//Database connection
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
    catch(const QSqlError &e)
    {
        EXCEPTION_HANDLER
    }
}

//PRIVATE SLOTS
void addSupplier::on_empresaButtonBox_clicked(QAbstractButton *button)
{
    if(ui->empresaButtonBox->standardButton(button) == QDialogButtonBox::Apply)
        this->empresaApplyButton();
    else if(ui->empresaButtonBox->standardButton(button) == QDialogButtonBox::Cancel)
        this->close();
    else //QDialogButtonBox::Save
    {
        this->empresaApplyButton();
        this->close();
    }
}
void addSupplier::on_contactoButtonBox_clicked(QAbstractButton *button)
{
    if(ui->contactoButtonBox->standardButton(button) == QDialogButtonBox::Apply)
        this->contactoApplyButton();
    else if(ui->contactoButtonBox->standardButton(button) == QDialogButtonBox::Cancel)
        this->close();
    else //QDialogButtonBox::Save
    {
        this->contactoApplyButton();
        this->close();
    }
}

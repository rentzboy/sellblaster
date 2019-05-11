#ifndef DATABASEMANAGEMENT_H
#define DATABASEMANAGEMENT_H

#include <QWidget>
class CreateDatabaseDialog;
class QSqlTableModel;
class QTableWidget;
class QItemSelectionModel;
class QErrorMessage;
class SqliteModel;
class SqliteDelegate;
class QTableView;

namespace Ui {class databaseManagement;}

class DatabaseManagement : public QWidget
{
    Q_OBJECT

public:
    //Constructors
    explicit DatabaseManagement(QWidget *parent = Q_NULLPTR);
    ~DatabaseManagement() override ;
    //borra las definiciones automáticas del compilador (también se podrian haber declarado private)
    DatabaseManagement(const DatabaseManagement&) = delete;
    DatabaseManagement& operator =(const DatabaseManagement&) = delete;
    //Members
    QSqlTableModel *get_model(void) const;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    Ui::databaseManagement *ui= Q_NULLPTR;
    QSqlTableModel *model = Q_NULLPTR;
    SqliteModel *adaptor = Q_NULLPTR;
    SqliteDelegate *delegate = Q_NULLPTR;
    QItemSelectionModel *selection = Q_NULLPTR;

    void setUpSqlTableModel(const QString &tableName);
    void refreshTableView(const QString &tableName);
    void executeSqlLiteQuery(const QString &sqlQuery);
    void setUpSqlTableView(void);
    void setUpSqliteModel(void);

private slots:
    void on_addButton_clicked(void);
    void on_editButton_clicked(void);
    void on_deleteButton_clicked(void);
    void deleteRow(void);
};

#endif // DATABASEMANAGEMENT_H

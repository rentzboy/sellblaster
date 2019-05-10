#ifndef MAPPERDBMANAGEMENT_H
#define MAPPERDBMANAGEMENT_H

#include <QWidget>
#include <QDialog>
#include <QDataWidgetMapper>
#include <QSqlTableModel>
#include <QStyledItemDelegate>
#include <QItemSelectionModel>

namespace Ui {class mapperDbManagement;}

class mapperDbManagement : public QDialog
{
    Q_OBJECT

public:
    explicit mapperDbManagement(int row, QWidget *parent = Q_NULLPTR);
    ~mapperDbManagement();

private:
    Ui::mapperDbManagement *ui;
    QSqlTableModel *model = Q_NULLPTR;
    QDataWidgetMapper *mapper = Q_NULLPTR;
    QStyledItemDelegate *delegate = Q_NULLPTR;
    QItemSelectionModel *selection = Q_NULLPTR;
    void mapFields(int selectedRow);
    void setUpSqlTableModel(const QString &tableName);

private slots:
    void on_PreviousButton_clicked(void);
    void on_NextButton_clicked(void);
};

#endif // MAPPERDBMANAGEMENT_H

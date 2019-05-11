#ifndef ADDSUPPLIER_H
#define ADDSUPPLIER_H

#include <QDialog>
#include <QAbstractButton>
#include <QErrorMessage>
#include <QMap>
#include <QStandardItemModel>


namespace Ui {class addSupplier;}

class AddSupplier : public QDialog
{
    Q_OBJECT

public:
    explicit AddSupplier(QWidget *parent = Q_NULLPTR);
    ~AddSupplier();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_empresaButtonBox_clicked(QAbstractButton *button);
    void on_contactoButtonBox_clicked(QAbstractButton *button);

private:
    //Members
    void fillComboBoxWithCheckBoxFromDb(void);
    void fillComboBoxesFromDb(void);
    bool sanitationCheck(QString tag);
    void empresaApplyButton(void);
    void contactoApplyButton(void);
    //Attributes
    QMap <QString, QString> userDataFields;
    QErrorMessage *errorMessage = Q_NULLPTR;
    Ui::addSupplier *ui;

    QStandardItemModel *modelo = Q_NULLPTR;
    QStandardItem *iItem1 = Q_NULLPTR;
    QStandardItem *iItem2 = Q_NULLPTR;
};

#endif // ADDSUPPLIER_H

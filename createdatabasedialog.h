#ifndef CREATEDATABASEDIALOG_H
#define CREATEDATABASEDIALOG_H

#include <QtWidgets>
#include <QDialog>
#include <QErrorMessage>

namespace Ui {
class createDatabaseDialog;
}

class createDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createDatabaseDialog(QWidget *parent = Q_NULLPTR);
    ~createDatabaseDialog() override;
    createDatabaseDialog(const createDatabaseDialog&) = delete;
    createDatabaseDialog& operator =(const createDatabaseDialog&) = delete;

protected:

private:
    Ui::createDatabaseDialog *ui;
    bool sanitationCheck(void);
    bool saveToDb(const QString &connectionName);
    QString get_nameField(void) const;
    QString get_databaseField(void) const;
    QString get_typeField(void) const;
    QString get_serverField(void) const;

private slots:
    void on_CancelButton_clicked(void);
    void on_okButton_clicked(void);
};

#endif // CREATEDATABASEDIALOG_H

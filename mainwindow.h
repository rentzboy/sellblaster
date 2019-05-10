#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QSqlQuery>
#include <QPointer>

#include "databasemanagement.h"
#include "addsupplier.h"

namespace Ui {class mainWindow;}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //constructors
    explicit mainWindow(QWidget *parent = Q_NULLPTR);
    ~mainWindow() override;
    mainWindow(const mainWindow&) = delete;
    mainWindow& operator =(const mainWindow&) = delete;
    //Static members
    static bool executeForwardSql(const QString &sqlQuery, const QString &connectionName);
    static bool executeForwardSqlException(const QString &sqlQuery, const QString &connectionName);
    static bool createExternDbConnection(const QMap <QString, QString> connectionDetails);
    static bool executeForwardSqlWithReturn(const QString &sqlQuery, const QString &connectionName, QSqlQuery &query);
    static void sanitationUserInput(QMap<QString, QString>&userFields);
    static QString get_usernameFromQsettings(void);
    //Non static members
    void createLoginDialog(void);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::mainWindow *ui;
    static void createInterDbConnection(void);
    QSize get_screenResolution(void);
    QSettings::Status readUserSettings(void);
    QSettings::Status writeUserSettings(void);
    QString get_usernameFromDb();
    //members where Qt::WA_DeleteOnClose == false
    QPointer<databaseManagement> dbManagementWidget = Q_NULLPTR;

private slots:
    void on_actionDatabases_triggered(void);
    void on_actionSalir_triggered(void);
    void on_actionA_adir_empresa_triggered();
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QSettings>
#include <QSqlQuery>
#include <QPointer>

#include "databasemanagement.h"
#include "addsupplier.h"

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator =(const MainWindow&) = delete;
    ~MainWindow() override = default;
    static void createComponent(void);

    static bool executeForwardSql(const QString &sqlQuery, const QString &connectionName);
    static bool executeForwardSqlException(const QString &sqlQuery, const QString &connectionName);
    static bool executeForwardSqlWithReturn(const QString &sqlQuery, const QString &connectionName, QSqlQuery &query);
    static bool createExternDbConnection(const QMap <QString, QString> connectionDetails);
    static void createInterDbConnection(void);
    static void sanitationUserInput(QMap<QString, QString>&userFields);
    static QString get_usernameFromQsettings(void);
    explicit MainWindow(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)

protected:
    void closeEvent(QCloseEvent *event);

private:
    static void registerSingleton(void);
    QSize get_screenResolution(void);
    QSettings::Status readUserSettings(void);
    QSettings::Status writeUserSettings(void);
    QString get_usernameFromDb();
    QPointer<DatabaseManagement> dbManagementWidget = Q_NULLPTR;
    static MainWindow *uniqueInstance;
    static int typeId;

public slots:
    void on_actionDatabases_triggered(void);
    void on_actionSalir_triggered(void);
    void on_actionA_adir_empresa_triggered();
};

#endif // MAINWINDOW_H

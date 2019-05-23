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
    Q_PROPERTY(QSize windowSize READ getWindowSize WRITE setWindowSize NOTIFY windowSizeChanged)
    Q_PROPERTY(QPoint windowPosition READ getWindowPosition WRITE setWindowPosition NOTIFY windowPositionChanged)
    Q_PROPERTY(bool windowFullScreen READ getWindowFullScreen WRITE setWindowFullScreen NOTIFY windowFullScreenChanged)
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)

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
    explicit MainWindow(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)

    QSize getWindowSize(void) const;
    void setWindowSize(const QSize &value);
    QPoint getWindowPosition(void) const;
    void setWindowPosition(const QPoint &value);
    bool getWindowFullScreen(void) const;
    void setWindowFullScreen(bool value);
    QString getUserName(void) const;
    void setUserName(const QString &value);

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
    QString userName;
    QSize windowSize;
    QPoint windowPosition;
    bool windowFullScreen;

signals:
    void userNameChanged();
    void windowSizeChanged();
    void windowPositionChanged();
    void windowFullScreenChanged();

public slots:
    void on_actionDatabases_triggered(void);
    void on_actionSalir_triggered(void);
    void on_actionA_adir_empresa_triggered();
};

#endif // MAINWINDOW_H

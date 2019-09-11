#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QSettings>
#include <QSqlQuery>
#include <QPointer>
#include <QQuickView>
#include "addsupplier.h"

class MainWindow : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(QSize windowSize MEMBER windowSize NOTIFY windowSizeChanged)
    Q_PROPERTY(QPoint windowPosition MEMBER windowPosition NOTIFY windowPositionChanged)

public:
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator =(const MainWindow&) = delete;
    ~MainWindow();
    static void createComponent(void);

    static bool executeForwardSql(const QString &sqlQuery, const QString &connectionName);
    static bool executeForwardSqlException(const QString &sqlQuery, const QString &connectionName);
    static bool executeForwardSqlWithReturn(const QString &sqlQuery, const QString &connectionName, QSqlQuery &query);
    static bool createExternDbConnection(const QMap <QString, QString> connectionDetails);
    static void createInterDbConnection(void);
    static void sanitationUserInput(QMap<QString, QVariant> &userFields);

private:
    explicit MainWindow(QQuickView *parent = Q_NULLPTR); //Private construstror (Singleton class)
    static void registerSingleton(void);
    QSize get_screenResolution(void);
    QSettings::Status readUserSettings(void);
    QSettings::Status writeUserSettings(void);
    QString get_usernameFromDb();
    static MainWindow *uniqueInstance;
    static int typeId;
    QString userName;
    QSize windowSize;
    QPoint windowPosition;
    bool windowFullScreen;

signals:
    void closeQmlInstance();
    void userNameChanged(); //no utilizado -pending refactoring-
    void windowSizeChanged(); //deprecated -pending refactoring-
    void windowPositionChanged(); //deprecated -pending refactoring-

public slots:
    void onClosingHandler(void);
    void onAnadirProveedor(void);
    void onActionExitTriggered(void);
    void onActionAddCompanyTriggered();
};

#endif // MAINWINDOW_H

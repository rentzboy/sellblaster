#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QSettings>
#include <QSqlQuery>
#include <QQuickView>
#include "addsupplier.h"


class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSize windowSize MEMBER windowSize NOTIFY windowSizeChanged)
    Q_PROPERTY(QPoint windowPosition MEMBER windowPosition NOTIFY windowPositionChanged)

public:
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator =(const MainWindow&) = delete;
    ~MainWindow();
    static void createComponent(QQmlApplicationEngine *engine);

    static bool executeForwardSql(const QString &sqlQuery, const QString &connectionName);
    static bool executeForwardSqlException(const QString &sqlQuery, const QString &connectionName);
    static bool executeForwardSqlWithReturn(const QString &sqlQuery, const QString &connectionName, QSqlQuery &query);
    static bool createMainDbConnection(const QMap <QString, QString>& connectionDetails);
    static void createInterDbConnection(void);
    static void sanitationUserInput(QMap<QString, QVariant> &userFields);

private:
    explicit MainWindow(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)
    static void registerSingleton(void);
    QSize get_screenResolution(void);
    QSettings::Status readUserSettings(void);
    QSettings::Status writeUserSettings(void);
    QString get_usernameFromDb();
    inline static MainWindow *uniqueInstance = Q_NULLPTR;
    inline static int typeId = 0;
    QString userName;
    QSize windowSize;
    QPoint windowPosition;
    //bool windowFullScreen; No utilizada

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

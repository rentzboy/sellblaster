#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QObject>
#include <QtQml>

class LoginDialog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName MEMBER userName NOTIFY userNameChanged)
    Q_PROPERTY(QString password MEMBER password NOTIFY passwordChanged)
    Q_PROPERTY(QString errorMsg MEMBER errorMsg CONSTANT)
    Q_PROPERTY(bool errorVisible MEMBER errorVisible NOTIFY errorVisibleChanged)

public:
    LoginDialog(const LoginDialog &other) = delete;
    LoginDialog operator=(const LoginDialog &other) = delete;
    ~LoginDialog();
    static void createComponent(void);

private:
    explicit LoginDialog(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)
    static void registerSingleton(void);
    void getUserNameFromQsettings(void);
    bool sanitationCheck(void);

public slots:
    void onAceptarClicked(void);
    void onCancelarClicked(void);

signals:
    //Notify signals
    void userNameChanged();
    void passwordChanged();
    void errorVisibleChanged();
    //Connect signals
    void closeQmlInstance();  //no utilizado

private:
    inline static QQmlApplicationEngine *engine = Q_NULLPTR;
    QString userName;
    QString password;
    QString errorMsg;
    bool errorVisible;
    inline static LoginDialog *uniqueInstance = Q_NULLPTR;
    inline static int typeId;
};

#endif // LOGINDIALOG_H

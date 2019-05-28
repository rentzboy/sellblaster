#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QObject>
#include <QtQml>

class LoginDialog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName MEMBER userName NOTIFY userNameChanged)
    Q_PROPERTY(QString password MEMBER password NOTIFY passwordChanged)
    Q_PROPERTY(QString errorMsg MEMBER errorMsg NOTIFY errorMsgChanged)
    Q_PROPERTY(bool errorVisible MEMBER errorVisible NOTIFY errorVisibleChanged)

public:
    LoginDialog(const LoginDialog &other) = delete;
    LoginDialog operator=(const LoginDialog &other) = delete;
    ~LoginDialog() = default;
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
    void userNameChanged();
    void passwordChanged();
    void errorMsgChanged();
    void errorVisibleChanged();
    void closeQmlInstance();

private:
    QString userName;
    QString password;
    QString errorMsg;
    bool errorVisible;
    static LoginDialog *uniqueInstance;
    static int typeId;
};

#endif // LOGINDIALOG_H

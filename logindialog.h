#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QObject>
#include <QtQml>

class LoginDialog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString errorMsg READ getErrorMsg WRITE setErrorMsg NOTIFY errorMsgChanged)
    Q_PROPERTY(bool errorVisible READ getErrorVisible WRITE setErrorVisible NOTIFY errorVisibleChanged)

public:
    LoginDialog(const LoginDialog &other) = delete;
    LoginDialog operator=(const LoginDialog &other) = delete;
    ~LoginDialog() = default;
    static QObject* createComponent(void);

    QString getUsername() const;
    void setUsername(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
    QString getErrorMsg() const;
    void setErrorMsg(const QString &value);
    bool getErrorVisible() const;
    void setErrorVisible(bool value);

private:
    explicit LoginDialog(QObject *parent = Q_NULLPTR); //Private construstror (Singleton class)
    static void registerSingleton(void);
    bool sanitationCheck(void);

protected:

public slots:
    void onAceptarClicked(void);
    void onCancelarClicked(void);
    void onUsernameUpdated(QString);
    void onPasswordUpdated(QString);

signals:
    void usernameChanged();
    void passwordChanged();
    void errorMsgChanged();
    void errorVisibleChanged();
    void closeQmlInstance();

private:
    QString username;
    QString password;
    QString errorMsg;
    bool errorVisible;
    static LoginDialog *uniqueInstance;
    static int typeId;
};

#endif // LOGINDIALOG_H

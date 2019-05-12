#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QObject>

class LoginDialog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString errorMsg READ getErrorMsg WRITE setErrorMsg NOTIFY errorMsgChanged)
    Q_PROPERTY(bool errorVisible READ getErrorVisible WRITE setErrorVisible NOTIFY errorVisibleChanged)

public:
    explicit LoginDialog(QObject *parent = Q_NULLPTR);

    QString getUsername() const;
    void setUsername(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
    QString getErrorMsg() const;
    void setErrorMsg(const QString &value);
    bool getErrorVisible() const;
    void setErrorVisible(bool value);

private:
    bool sanitationCheck(void);

protected:

public slots:
    void onAceptarClicked(void);
    void onCancelarClicked(void);

signals:
    void usernameChanged();
    void passwordChanged();
    void errorMsgChanged();
    void errorVisibleChanged();

private:
    QString username;
    QString password;
    QString errorMsg;
    bool errorVisible;
};

#endif // LOGINDIALOG_H

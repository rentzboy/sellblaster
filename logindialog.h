#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {class loginDialog;}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = Q_NULLPTR);
    ~loginDialog();

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_buttonBox_rejected(void);
    void on_buttonBox_accepted(void);

private:
    Ui::loginDialog *ui;
    QString get_username(void) const;
    QString get_password(void) const;
};

#endif // LOGINDIALOG_H

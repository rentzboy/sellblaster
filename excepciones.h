#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <QtWidgets>
#include <QDateTime>
#include <QSysInfo>
#include <exception>
#include <QSqlError>
#include <QErrorMessage>
#include <iostream>
#include <memory>

/* IMPORTANTE: Diseñamos esta clase pues no se pueden generar members de la clase base exceptions
 * ya que esta clase úncamente tiene el member what() */

class Excepciones
{
public:
    Excepciones(const std::exception&, const QString&, const QString&, int); //ctror #1
    Excepciones(const QSqlError&, const QString&, const QString&, int);  //ctror #2
    Excepciones(const QString&, const QString&, const QString&, int); //ctror #3
    Excepciones(const Excepciones& e) = default; //throw expression: copy-initialize the expression !!
    Excepciones& operator =(const Excepciones&) = delete;
    ~Excepciones() = default;

private:
    //members
    QString databaseUsername(void);
    void saveExceptionInterface(void);
    bool saveToDb(const QString& dbConnectionName);
    void saveToLogFile(QString method); //Using Qt or STL
    //Attributes
    QStringList logExceptions;
    QString hostName = Q_NULLPTR;
    QString operativeSystem = Q_NULLPTR;
    QDateTime systemTime;
    QString fileName = Q_NULLPTR;
    QString functionName = Q_NULLPTR;
    QString errorDescription = Q_NULLPTR;
    QString userName ;
    int fileLine;
    static QString exceptionMsg;
    static QPointer<QErrorMessage>exceptionMessageBox;
};

#endif // EXCEPCIONES_H

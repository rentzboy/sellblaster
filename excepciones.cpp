#include "excepciones.h"
#include "globals.h"
#include "mainwindow.h"
#include <QSqlError>
#include <QErrorMessage>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <fstream>   //istream
#include <sstream>   //ostringstream

//Static variables initialization
QPointer<QErrorMessage> Excepciones::exceptionMessageBox = Q_NULLPTR;
QString Excepciones::exceptionMsg;

/* CONSTRUCTORS */
Excepciones::Excepciones(const std::exception &e, const QString& _fileName, //std::exception
                                           const QString& _functionName, int _lineNumber)
                                            try : hostName(QSysInfo::machineHostName()),
                                                    operativeSystem(QSysInfo::productVersion()),
                                                    systemTime(QDateTime::currentDateTime()),
                                                    fileName(_fileName), functionName(_functionName),
                                                    errorDescription(e.what()), userName(databaseUsername()),
                                                    fileLine(_lineNumber)
{
    qDebug() << "Se ha llamado a: " << __FUNCTION__ <<"(std::exception)";
    //Show exception to the user
    exceptionMsg = "Error durante la ejecución del proceso: ";
    exceptionMsg.append(e.what());
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);

    //Save exception to Db
    this->saveExceptionInterface();
}catch(const std::exception &ex)
{
    exceptionMsg = "Error en el constructor de excepciones: ";
    exceptionMsg.append(ex.what());
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);

    exit(EXIT_FAILURE); //termina el programa.
}catch(...)
{
    exceptionMsg = "Error desconocido en el constructor de excepciones!!";
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);

    exit(EXIT_FAILURE); //termina el programa.
}

Excepciones::Excepciones(const QSqlError &e, const QString& _fileName, //QSqlError
                                           const QString& _functionName, int _lineNumber)
                                           try : hostName(QSysInfo::machineHostName()),
                                                   operativeSystem(QSysInfo::productVersion()),
                                                   systemTime(QDateTime::currentDateTime()),
                                                   fileName(_fileName), functionName(_functionName),
                                                   errorDescription(e.databaseText()), userName(databaseUsername()),
                                                   fileLine(_lineNumber)
{
    qDebug() << "Se ha llamado a: " << __FUNCTION__ <<"(QSqlError)";
    //Show exception to the user
    exceptionMsg = "Error durante la ejecución del proceso: ";
    exceptionMsg.append(e.databaseText());
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);
    //Save exception to Db
    saveExceptionInterface();
}catch(const std::exception &ex)
{
    exceptionMsg = "Error en el constructor de excepciones: ";
    exceptionMsg.append(ex.what());
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);

    exit(EXIT_FAILURE); //termina el programa.
}catch(...)
{
    exceptionMsg = "Error desconocido en el constructor de excepciones!!";
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);

    exit(EXIT_FAILURE); //termina el programa.
}

Excepciones::Excepciones(const QString& errorMsg, const QString& _fileName, //QString
                                          const QString& _functionName, int _lineNumber)
                                           try : hostName(QSysInfo::machineHostName()),
                                                   operativeSystem(QSysInfo::productVersion()),
                                                   systemTime(QDateTime::currentDateTime()),
                                                   fileName(_fileName), functionName(_functionName),
                                                   errorDescription(errorMsg), userName(databaseUsername()),
                                                   fileLine(_lineNumber)
{
    qDebug() << "Se ha llamado a: " << __FUNCTION__ <<"(QString)";
    //Show exception to the user
    exceptionMsg = "Error durante la ejecución del proceso: ";
    exceptionMsg.append(errorMsg);
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);
    //Save exception to Db
    this->saveExceptionInterface();
}catch(const std::exception &ex)
{
    exceptionMsg = "Error en el constructor de excepciones: ";
    exceptionMsg.append(ex.what());
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);

    exit(EXIT_FAILURE); //termina el programa.
}catch(...)
{
    exceptionMsg = "Error desconocido en el constructor de excepciones!!";
    exceptionMessageBox = new QErrorMessage();
    exceptionMessageBox->showMessage(exceptionMsg);
    exceptionMessageBox->raise();
    exceptionMessageBox->resize(400, 250);

    exit(EXIT_FAILURE); //termina el programa.
}

/* PRIVATE MEMBERS */
QString Excepciones::databaseUsername(void)
{
    auto tmp = QSqlDatabase::database(MAIN_DB_CONNECTION_NAME); //returns connectionName
    QString user = tmp.userName();

    if(user.isEmpty())
    {
        tmp = QSqlDatabase::database(DB_QPSQL_CONNECTION_NAME);
        user = tmp.userName();
        if(user.isEmpty())
            user = "empty";
    }
    return user;
}
void Excepciones::saveExceptionInterface(void)
{
    /* Al generarse una exception se intenta guardar en la Db, pero si se genera
     * una exception en saveToLogTable(), este caso se intenta guardar
     *  en un archivo de texto. Si da fallo también aqui se muestra un qCritical() */
    /* Importante: Yo en saveToLogFile() quiero guardar la exception inicial,
     * no la que se ha generado en saveToLogTable(), pues si veo que se ha guardado
     * la exception en saveToLogFile() ya doy por hecho que ha fallado saveToLogTable() */
    /* Podria eliminar saveExceptionInterface() y llamar a las 2 funciones directamente
     * desde los constructors, pero resulta más fácil hacer los cambios asi */

#ifdef PRODUCTION
    if(this->saveToDb(MAIN_DB_CONNECTION_NAME) == EXIT_FAILURE)
    {
        this->saveToSqliteDb();
        this->saveToLogFile("STL");
    }
#elif DEBUG
    this->saveToDb(MAIN_DB_CONNECTION_NAME);
    //this->saveToDb(DB_QSQLITE_CONNECTION_NAME);
    this->saveToLogFile("STL");
#endif
}
bool Excepciones::saveToDb(const QString& dbConnectionName)
{
    try
    {
        qDebug() << "Se ha llamado a: " << __FUNCTION__ <<"(" << dbConnectionName << ")";

        //Sanitation check
        QMap <QString, QString> exceptionFields;
        exceptionFields.insert("hostname",this->hostName);
        exceptionFields.insert("operativesystem", this->operativeSystem);
        exceptionFields.insert("file", this->fileName);
        exceptionFields.insert("function", this->functionName);
        exceptionFields.insert("time", this->systemTime.toString());
        exceptionFields.insert("description", this->errorDescription);
        MainWindow::sanitationUserInput(exceptionFields);

        if(dbConnectionName == MAIN_DB_CONNECTION_NAME)
        {
            QString sqlQuery = "CALL insert_Exception(";
            sqlQuery.append("'").append(this->userName).append("', '")
            .append(exceptionFields.value("hostname")).append("', '")
            .append(exceptionFields.value("operativesystem")).append("', '")
            .append(exceptionFields.value("file")).append("', '")
            .append(exceptionFields.value("function")).append("', ")
            .append(this->fileLine).append(", '")
            .append(exceptionFields.value("time")).append("', '")
            .append(exceptionFields.value("description")).append("');");
            qDebug() << "Stored procedure: " << sqlQuery;
            return MainWindow::executeForwardSqlException(sqlQuery, MAIN_DB_CONNECTION_NAME);
        }
        else //DB_QSQLITE_CONNECTION_NAME
        {
            //Database connection
            auto db = QSqlDatabase::database(dbConnectionName);
            if(!db.isOpen())
                throw(db.lastError());

            QString text = "INSERT INTO exception (username, hostname, operativesystem,"
                                    "archivo, funcion, line, errortime, description)"
                                    "VALUES (:username, :hostname, :operativesystem,"
                                    ":file, :function, :line, :errortime, :description)";

            QSqlQuery query(db);
            query.prepare(text);
            query.bindValue(":username", this->userName);
            query.bindValue(":hostname", this->hostName);
            query.bindValue(":operativesystem", this->operativeSystem );
            query.bindValue(":file", this->fileName);
            query.bindValue(":function", this->functionName);
            query.bindValue(":line", this->fileLine);
            query.bindValue(":errortime", this->systemTime.toString());
            query.bindValue(":description", this->errorDescription);
            //qDebug() << "Query executed: " << query.lastQuery();
            if(!query.exec())
                throw(query.lastError());
            return EXIT_SUCCESS;
        }
    }
    catch(const QSqlError &e)
    {
        //Recuperar el error con text (genérico) pues hay 3 error types: query, database y driver
        exceptionMsg = "Error en el constructor de excepciones al guardar en la DB: ";
        exceptionMsg.append((e.text()));
        exceptionMessageBox = new QErrorMessage();
        exceptionMessageBox->showMessage(exceptionMsg);
        exceptionMessageBox->raise();
        exceptionMessageBox->resize(400, 250);

        return EXIT_FAILURE; //no exit() !!
    }
    catch (QString &e)
    {
        exceptionMsg = "Error en el constructor de excepciones al guardar en la DB: ";
        exceptionMsg.append((e));
        exceptionMessageBox = new QErrorMessage();
        exceptionMessageBox->showMessage(exceptionMsg);
        exceptionMessageBox->raise();
        exceptionMessageBox->resize(400, 250);

        return EXIT_FAILURE; //no exit() !!
    }
}
void Excepciones::saveToLogFile(QString method)
{
    try
    {
        qDebug() << "Se ha llamado a saveToLogFile()";

        if(method == "STL") //OPCION #1: STL
        {
            std::string logPath;
            logPath.append(DIRECTORY_PATH).append(LOG_FILE_RELATIVE_PATH);
            std::string fileUrl (logPath);
            std::ofstream outputFile(fileUrl, std::ios_base::out | std::ios_base::app);
            outputFile.exceptions(std::ios_base::badbit | std::ios_base::failbit); //Activar las excepciones
            outputFile.is_open(); //si no se puede abrir salta la exception directamente

            qDebug() << "Volcando excepción al archivo.....";
            outputFile << QObject::tr("Time: ").toStdString() << systemTime.toString().toStdString() << "\n"
                       << QObject::tr("System Operative: ").toStdString() << operativeSystem.toStdString() << "\n"
                      << QObject::tr("Hostname: ").toStdString() << hostName.toStdString() << "\n"
                       << QObject::tr("User: ").toStdString() << userName.toStdString() << "\n"
                       << QObject::tr("File: ").toStdString() << fileName.toStdString() << "\n"
                       << QObject::tr("Function name: ").toStdString() << functionName.toStdString() << "\n"
                       << QObject::tr("Line: ").toStdString() << QString::number(fileLine).toStdString() << "\n"
                       << QObject::tr("Error Description: ").toStdString() << errorDescription.toStdString() << "\n\n\n";
                qDebug() << QObject::tr("Se ha grabado (STL) un error al archivo de texto");
        }
        else //OPCION #2: Qt
        {
            QString logPath;
            logPath.append(DIRECTORY_PATH).append(LOG_FILE_RELATIVE_PATH);
            QFile logFile(logPath);
             if (!logFile.open(QFile::WriteOnly | QFile::Append))
                 throw(QObject::tr("No se ha podido abrir (Qt) el archivo de excepcionts.txt !"));

             logExceptions << QObject::tr("Time: ") << systemTime.toString() << "\n"
                                      << QObject::tr("System Operative: ") << operativeSystem << "\n"
                                     << QObject::tr("Hostname: ") << hostName << "\n"
                                      << QObject::tr("User: ") << userName << "\n"
                                      << QObject::tr("File: ") << fileName << "\n"
                                      << QObject::tr("Function name: ") << functionName << "\n"
                                      << QObject::tr("Line: ") << QString::number(fileLine) << "\n"
                                      << QObject::tr("Error Description: ") << errorDescription << "\n\n\n";

             qDebug() << "Volcando excepción al archivo.....";
             QTextStream out(&logFile);
             QString iterator;
             foreach(iterator, logExceptions)
                 out << iterator;
             if(out.status() !=QTextStream::Ok)
                 throw(QObject::tr("Eror al grabar (Qt) el archivo de excepcionts.txt !"));

             qDebug() << (QObject::tr("Se ha grabado (Qt) un error al archivo de texto"));
        }
    }catch(const std::ios_base::failure &e)
    {
        exceptionMsg = "Error en el constructor de excepciones al guardar en el archivo de texto !!";
        exceptionMsg.append((e.what()));
        exceptionMessageBox = new QErrorMessage();
        exceptionMessageBox->showMessage(exceptionMsg);
        exceptionMessageBox->raise();
        exceptionMessageBox->resize(400, 250);

        exit(EXIT_FAILURE); //termina el programa.
    }catch (const QString &e)
    {
        exceptionMsg = "Error en el constructor de excepciones al guardar en el archivo de texto !!";
        exceptionMsg.append((e));
        exceptionMessageBox = new QErrorMessage();
        exceptionMessageBox->showMessage(exceptionMsg);
        exceptionMessageBox->raise();
        exceptionMessageBox->resize(400, 250);
        exit(EXIT_FAILURE); //termina el programa.
    }
}

/* PUBLIC MEMBERS */

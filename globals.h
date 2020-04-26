#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtWidgets>

//En este archivo solo hay que indicar el si es DEBUG / PRODUCTION y la MAIN_DB_TYPE

/* DEFINES */
#define DEBUG                                           1  //Switch DEBUG - PRODUCTION (hay que indicarlo)
#define EXCEPTION_HANDLER              Excepciones ex(e, basename(__FILE__), __FUNCTION__,  __LINE__);
#define PRINT_FUNCTION_NAME          qDebug() << "Se ha llamado a la función: " << __FUNCTION__;

/* GLOBAL VARIABLES */
const QByteArray DB_QSQLITE_CONNECTION_NAME ("innerDb");
const QByteArray MAIN_DB_TYPE ("QMYSQL");  //or "QPSQL" (hay que indicarselo)

const QByteArray DB_QPSQL_CONNECTION_NAME ("psqlDb");
const QByteArray DB_QMYSQL_CONNECTION_NAME ("mysqlDb");
const QByteArray MAIN_DB_CONNECTION_NAME (MAIN_DB_TYPE == "QMYSQL" ? DB_QMYSQL_CONNECTION_NAME : DB_QPSQL_CONNECTION_NAME);
const QByteArray AUXILIARY_DB_CONNECTION_NAME (MAIN_DB_TYPE == "QMYSQL" ?DB_QPSQL_CONNECTION_NAME : DB_QMYSQL_CONNECTION_NAME);

const QByteArray APPLICATION_PATH (QDir::homePath().toUtf8().append("/Qt/Proyectos"));
const QByteArray LOG_FILE_RELATIVE_PATH ("/Q_Sellblaster/logs/exceptions.txt");
const QByteArray SQLITE_RELATIVE_PATH ("/Q_Sellblaster/logs/innerdb.sqlite3");

/*Deprecated
#define DB_QSQLITE_CONNECTION_NAME       "innerDb"
#define DB_QPSQL_CONNECTION_NAME           "psqlDb"
#define DB_QMYSQL_CONNECTION_NAME       "mysqlDb"
#define MAIN_DB_TYPE                                           "QMYSQL" //or "QPSQL"
#define MAIN_DB_CONNECTION_NAME             DB_QMYSQL_CONNECTION_NAME

//#define APPLICATION_PATH                                   QCoreApplication::applicationDirPath()
#define APPLICATION_PATH                                   "/home/renton/Qt/Proyectos" //OJO --> renti  (X300) / renton (X220)
#define LOG_FILE_RELATIVE_PATH                     "/Q_Sellblaster/logs/exceptions.txt"
#define SQLITE_RELATIVE_PATH                          "/Q_Sellblaster/logs/innerdb.sqlite3"

#define STATUSBAR_MESSAGE(msg, timeout)          static_cast<mainWindow*>(this->parent())->statusBar()->showMessage(QObject::tr(msg), timeout);

#define CATCH_STD_EXCEPTION        excepciones catchedException (e, __FILE__, __FUNCTION__,  __LINE__); \

#define THROW_EXCEPCION(msg)       excepciones throwedException (__FILE__, __FUNCTION__,  __LINE__, #msg); \
                                                                     throw throwedException; //continuación de la linea anterior
                                                                     */

#endif // GLOBALS_H


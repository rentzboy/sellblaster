#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtWidgets>

/* GLOBAL VARIABLES */

/* DEFINES */
#define DEBUG                                                           1  //Switch DEBUG - PRODUCTION

#define DB_QSQLITE_CONNECTION_NAME       "innerDb"
#define DB_QPSQL_CONNECTION_NAME           "psqlDb"
#define DB_QMYSQL_CONNECTION_NAME       "mysqlDb"
#define MAIN_DB_TYPE                                           "QMYSQL" //or "QPSQL"
#define MAIN_DB_CONNECTION_NAME             DB_QMYSQL_CONNECTION_NAME

//#define DIRECTORY_PATH                                     QCoreApplication::applicationDirPath()
#define DIRECTORY_PATH                                      "/home/renti/Proyectos"
#define LOG_FILE_RELATIVE_PATH                     "/Q_Sellblaster/logs/exceptions.txt"
#define SQLITE_RELATIVE_PATH                          "/Q_Sellblaster/logs/innerdb.sqlite3"

#define EXCEPTION_HANDLER                              Excepciones ex(e, basename(__FILE__), __FUNCTION__,  __LINE__);
#define PRINT_FUNCTION_NAME                          qDebug() << "Se ha llamado a la función: " << __FUNCTION__;


/*Deprecated
#define STATUSBAR_MESSAGE(msg, timeout)          static_cast<mainWindow*>(this->parent())->statusBar()->showMessage(QObject::tr(msg), timeout);

#define CATCH_STD_EXCEPTION        excepciones catchedException (e, __FILE__, __FUNCTION__,  __LINE__); \

#define THROW_EXCEPCION(msg)       excepciones throwedException (__FILE__, __FUNCTION__,  __LINE__, #msg); \
                                                                     throw throwedException; //continuación de la linea anterior
                                                                     */

#endif // GLOBALS_H


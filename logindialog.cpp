#include "logindialog.h"
#include "basic_headers.h"
#include "mainwindow.h"
#include <QQuickWindow>
#include "addsupplier.h"

//PRIVATE MEMBERS
LoginDialog::LoginDialog(QObject *parent) : QObject(parent)
{
    PRINT_FUNCTION_NAME

    //Retrieve username from previous sesions -QSettings-
    this->getUserNameFromQsettings();
}
void LoginDialog::registerSingleton(void)
{
    typeId = qmlRegisterSingletonType<LoginDialog>("LoginClass", 1, 0, "LoginType",
        [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
            Q_UNUSED(scriptEngine)
            Q_UNUSED(engine)
            return uniqueInstance;
            });
}
bool LoginDialog::sanitationCheck()
{
    if(userName.isEmpty() || password.isEmpty())
        return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
void LoginDialog::getUserNameFromQsettings(void)
{
    //Retrieve configuration from the last user's session
    QSettings userSettings(QObject::tr("Fx Team®"), QObject::tr("Sellblaster"));
    userSettings.beginGroup(QObject::tr("mainwindow"));
    userName = userSettings.value(QObject::tr("username")).toString();
    userSettings.endGroup();
}

//PUBLIC MEMBERS
void LoginDialog::createComponent(QQmlApplicationEngine *engine)
{
    if(uniqueInstance == Q_NULLPTR)
    {
        uniqueInstance = new LoginDialog;
        registerSingleton(); //para poder utilizarla con QML

        //Hay que crear la conexión con la Db SQLite3 -necesario para Login.qml-
        MainWindow::createInterDbConnection();

        //Load QML component
        engine->load(QUrl(QStringLiteral("qrc:/qml/Login.qml")));

        //Connect Signals(C++) to Slots(QML)
        //engine->rootObjects() solo recupera los objetos instanciados con load (si utilizamos component.create() no funcionaria)
        //connect(uniqueInstance, SIGNAL(closeQmlInstance()), engine->rootObjects().value(typeId), SLOT(onCloseQmlInstance()));
    }
}
LoginDialog::~LoginDialog()
{
    PRINT_FUNCTION_NAME

    //delete uniqueInstance; --> Si lo descomento entra en bucle ........
    uniqueInstance = Q_NULLPTR;
}

//PUBLIC SLOTS
void LoginDialog::onCancelarClicked(void)
{
    PRINT_FUNCTION_NAME

    //Al cerrar la última ventana QML cierra la app automáticamente
    emit closeQmlInstance(); //trowing in C++, catching in QML

    //QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
    //qGuiApp->quit(); No funciona pues la App aun no ha entrado en el main event loop (app.exec())
}
void LoginDialog::onAceptarClicked(void)
{
    PRINT_FUNCTION_NAME

    if(this->sanitationCheck() == EXIT_FAILURE)
        return;

    try
    {
        //Get connection details from SQLite3
        QSqlQuery result;
        QString sqlQuery = "SELECT * FROM connection WHERE type=";
        sqlQuery.append("'").append(MAIN_DB_TYPE).append("'").append(" LIMIT 1;");

        MainWindow::executeForwardSqlWithReturn(sqlQuery, DB_QSQLITE_CONNECTION_NAME, result); //Output arg.
        if(!result.next())
            throw result.lastError();
        //int fieldName = result.record().indexOf("name");
        int fieldDb = result.record().indexOf("database");
        int fieldServer = result.record().indexOf("serverurl");

        QMap <QString, QString> connectionDetails;
        //connectionDetails.insert("name", result.value(fieldName).toString());
        connectionDetails.insert("database", result.value(fieldDb).toString());
        connectionDetails.insert("serverurl", result.value(fieldServer).toString());
        connectionDetails.insert("username", userName);
        connectionDetails.insert("password", password);
        connectionDetails.insert("type", MAIN_DB_TYPE);
        //qDebug() << connectionDetails;

        //Connect to MAIN_DB
        if (MainWindow::createMainDbConnection(connectionDetails) == EXIT_FAILURE)
        {
            errorVisible = true;
            emit errorVisibleChanged();
        }
        else
        {
            /* DEPRECATED
             * opcion #1
             * QObject *object = engine->rootObjects().value(LoginDialog::typeId);
             * QMetaObject::invokeMethod(object, "close");
             * opcion #2
             * engine->deleteLater --> delete QML file + engine --> ~Login() --> delete uniqueInstance
             * se ejecuta al volver al loop principial (sino no se ejecutaria el codigo de abajo)*/

            //Load MainWindow.qml
            emit closeQmlInstance(); //solo cierra el Qml, pero no llama al dtror de C++ ni del engine
            //Probablemente podríamos utilizar un nuevo engine como en AddSupplier y destruir el de LoginDialog
            QQmlApplicationEngine *engine = qobject_cast<QQmlApplicationEngine*>(qmlEngine(uniqueInstance));
            MainWindow::createComponent(engine);
        }
    }
    catch (const QSqlError &e)
    {
        EXCEPTION_HANDLER
    }
}

#include "mainwindow.h"
#include "globals.h"
#include "logindialog.h"
#include "excepciones.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    try
    {
        QApplication app(argc, argv); //Por ahora utilizamos QErrorMessage asi que necesitamos QApplication
        //QGuiApplication app(argc, argv); //Cambiar x la linea superior cuando ya no utilicemos QWidgets
        app.setAttribute(Qt::AA_EnableHighDpiScaling);

        //Hay que crear la conexión con la Db SQLite3 -necesario para Login.qml-
        MainWindow::createInterDbConnection();

        //Load first QML page
        LoginDialog::createComponent();

        //SOLO PARA PROBAR COMPONENTES (Load QML component)
//        auto *engine = new QQmlApplicationEngine;
//        engine->load(QUrl(QStringLiteral("qrc:/qml/Login.qml")));

        return app.exec();
    }
    catch (std::exception &e)
    {
        EXCEPTION_HANDLER
    }
    catch (QString &e)
    {
        EXCEPTION_HANDLER
    }
}

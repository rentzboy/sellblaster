#include "globals.h" //lo primero de todo para que no haya problemas.
#include "mainwindow.h"
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


        //Load first QML page
        QQmlApplicationEngine engine; //Same for all the qml we load
        LoginDialog::createComponent(&engine);

        /* ========== SOLO PARA PROBAR COMPONENTES (Load QML component) ==========
        auto *engine = new QQmlApplicationEngine;
        MainWindow::createComponent();
        engine->load(QUrl(QStringLiteral("qrc:/qml/EmpresaTab.qml")));*/

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

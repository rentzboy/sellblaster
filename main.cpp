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
        QApplication app(argc, argv);
        //QGuiApplication app(argc, argv);
        app.setAttribute(Qt::AA_EnableHighDpiScaling);

        qmlRegisterType<LoginDialog>("LoginClass", 1, 0, "LoginDialog");

        MainWindow w;
        w.hide(); //la mostramos despues del login

//        QQuickView view;
//        view.setResizeMode(QQuickView::SizeRootObjectToView);
//        view.setSource(QUrl("qrc:///app.qml"));
//        view.show();

        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/qml/login.qml")));
        if (engine.rootObjects().isEmpty())
            return -1;
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

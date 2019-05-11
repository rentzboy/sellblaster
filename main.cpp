#include "mainwindow.h"
#include "globals.h"
#include "logindialog.h"
#include "excepciones.h"
#include <QApplication>
#include <QQmlApplicationEngine>
//#include <QGuiApplication>
//#include <QQuickStyle>

int main(int argc, char *argv[])
{
    try
    {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication a(argc, argv);

        //MainWindow w;
        //w.hide(); //la mostramos despues del login

        qmlRegisterType<LoginDialog>("LoginClass", 1, 0, "LoginDialog");

//        QQuickView view;
//        view.setResizeMode(QQuickView::SizeRootObjectToView);
//        view.setSource(QUrl("qrc:///app.qml"));
//        view.show();

        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/qml/login.qml")));
        if (engine.rootObjects().isEmpty())
            return -1;
        return a.exec();
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

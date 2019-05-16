#include "mainwindow.h"
#include "globals.h"
#include "logindialog.h"
#include "excepciones.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    try
    {
        QApplication app(argc, argv);
        //QGuiApplication app(argc, argv);
        app.setAttribute(Qt::AA_EnableHighDpiScaling);

        qmlRegisterSingletonType<LoginDialog>("LoginClass", 1, 0, "LoginDialog",
            [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
                Q_UNUSED(scriptEngine)
                return LoginDialog::createSingletonLoginDialog(engine);
        });

        MainWindow w;
        w.hide(); //la mostramos despues del login

//        QQuickView view;
//        view.setResizeMode(QQuickView::SizeRootObjectToView);
//        view.setSource(QUrl("qrc:///app.qml"));
//        view.show();

        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/qml/Login.qml")));
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

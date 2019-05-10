#include "mainwindow.h"
#include "globals.h"
#include "excepciones.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        mainWindow w;
        w.hide(); //la mostramos despues del login
        w.createLoginDialog();
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

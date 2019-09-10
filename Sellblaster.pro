#-------------------------------------------------
#
# Project created by QtCreator 2019-02-12T09:51:40
#
#-------------------------------------------------

QT  += core sql quick quickcontrols2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sellblaster
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER  = precompiled_header.h

#Indicamos la versión del compilador a la que tiene que llamar (si no queremos el predeterminado x Linux)
#No es suficiente con indicarlo en Options > Kit
#QMAKE_CXX = ccache g++-9

#To allow build executable to be recognized by the the OS (https://stackoverflow.com/a/45332687)
QMAKE_LFLAGS += -no-pie

#Indicar la versión de C++
CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        excepciones.cpp \
        logindialog.cpp \
        addsupplier.cpp

HEADERS += \
        mainwindow.h \
        precompiled_header.h \
        excepciones.h \
        globals.h \
        logindialog.h \
        addsupplier.h \
        basic_headers.h

RESOURCES += \
    resources.qrc \
    qml.qrc

DISTFILES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

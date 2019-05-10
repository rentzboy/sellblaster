#-------------------------------------------------
#
# Project created by QtCreator 2019-02-12T09:51:40
#
#-------------------------------------------------

QT       += core gui sql quick quickcontrols2

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
QMAKE_CXX = g++-8
#Indicar la versión de C++
CONFIG += c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        databasemanagement.cpp \
        excepciones.cpp \
        createdatabasedialog.cpp \
        sqlitemodel.cpp \
        sqlitedelegate.cpp \
        mapperdbmanagement.cpp \
        logindialog.cpp \
        addsupplier.cpp \
        checkboxlist.cpp

HEADERS += \
        mainwindow.h \
        precompiled_header.h \
        databasemanagement.h \
        createdatabasedialog.h \
        excepciones.h \
        globals.h \
        sqlitemodel.h \
        sqlitedelegate.h \
        mapperdbmanagement.h \
        logindialog.h \
        addsupplier.h \
        basic_headers.h \
        checkboxlist.h \
        qchecklist.h

FORMS += \
        mainwindow.ui \
        databasemanagement.ui \
        createdatabasedialog.ui \
        mapperdbmanagement.ui \
        logindialog.ui \
        addsupplier.ui

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

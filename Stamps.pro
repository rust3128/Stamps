#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T15:45:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Stamps
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    connectdialog.cpp \
    regionsdialog.cpp \
    usersdialog.cpp \
    storagedialog.cpp \
    documentsdialog.cpp \
    changedoctypedialog.cpp \
    docnewdialog.cpp \
    vlasnikdialog.cpp \
    rrolistdialog.cpp \
    modelrrodialog.cpp

HEADERS += \
        mainwindow.h \
    database.h \
    connectdialog.h \
    regionsdialog.h \
    usersdialog.h \
    storagedialog.h \
    documentsdialog.h \
    changedoctypedialog.h \
    docnewdialog.h \
    vlasnikdialog.h \
    rrolistdialog.h \
    modelrrodialog.h

FORMS += \
        mainwindow.ui \
    connectdialog.ui \
    regionsdialog.ui \
    usersdialog.ui \
    storagedialog.ui \
    documentsdialog.ui \
    changedoctypedialog.ui \
    docnewdialog.ui \
    vlasnikdialog.ui \
    rrolistdialog.ui \
    modelrrodialog.ui

RESOURCES += \
    resource.qrc

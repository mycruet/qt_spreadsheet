#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T10:26:50
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spreadsheet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    finddialog.cpp \
    gotocelldialog.cpp

HEADERS  += mainwindow.h \
    finddialog.h \
    gotocelldialog.h

FORMS    += mainwindow.ui \
    finddialog.ui \
    gotocelldialog.ui

RESOURCES += \
    spreadsheet.qrc

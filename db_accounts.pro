#-------------------------------------------------
#
# Project created by QtCreator 2014-02-09T12:34:53
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = db_accounts
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbaccess.cpp

HEADERS  += mainwindow.h \
    dbaccess.h \
    baseStruct.h

FORMS    += mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T11:20:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableViewTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mymodel.cpp

HEADERS  += mainwindow.h \
    mymodel.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    notes.txt

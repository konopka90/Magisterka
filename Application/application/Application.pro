ROOT_DIR = ..
!include($$ROOT_DIR/build.conf) {
    message("ups")
}

## Qwt

INCLUDEPATH       += $$QWT_INCLUDEPATH
LIBS		  += $$QWT_LIBS

## Boost

INCLUDEPATH       += $$BOOST_INCLUDEPATH

QT       += core gui

TARGET = Application
TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    Table.cpp \
    FileDialog.cpp \
    WindowManager.cpp \
    Window.cpp \
    TableModel.cpp \
    TableColumn.cpp \
    Plot.cpp \
    PlotLine.cpp \
    Exceptions.cpp \
    TableView.cpp \
    PlotDialog.cpp \
    PlotHistogram.cpp


HEADERS  += \
    MainWindow.h \
    Table.h \
    FileDialog.h \
    WindowManager.h \
    Window.h \
    TableModel.h \
    TableColumn.h \
    Plot.h \
    PlotLine.h \
    Exceptions.h \
    TableView.h \
    PlotDialog.h \
    PlotHistogram.h

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui


Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui


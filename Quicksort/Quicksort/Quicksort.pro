#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T13:24:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quicksort
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    quicksortarray.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    quicksortarray.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

QMAKE_CXXFLAGS += -std=c++11

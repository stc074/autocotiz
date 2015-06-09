#-------------------------------------------------
#
# Project created by QtCreator 2015-05-14T23:57:23
#
#-------------------------------------------------

QT       += core gui
QT      += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = auto-entrepreneur
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmldom.cpp \
    record.cpp \
    declaration.cpp \
    archive.cpp

HEADERS  += mainwindow.h \
    xmldom.h \
    record.h \
    declaration.h \
    archive.h

FORMS    += mainwindow.ui

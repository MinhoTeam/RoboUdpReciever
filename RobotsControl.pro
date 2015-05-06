#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T21:04:50
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobotsControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialport.cpp \
    udpcom.cpp

HEADERS  += mainwindow.h \
    serialport.h \
    udpcom.h

FORMS    += mainwindow.ui

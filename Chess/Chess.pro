#-------------------------------------------------
#
# Project created by QtCreator 2017-03-22T18:21:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pieces.cpp \
    board.cpp \
    player.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    pieces.h \
    board.h \
    player.h \
    controller.h

FORMS    += mainwindow.ui

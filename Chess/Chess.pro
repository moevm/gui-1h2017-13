#-------------------------------------------------
#
# Project created by QtCreator 2017-03-22T18:21:01
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pieces.cpp \
    board.cpp \
    player.cpp \
    controller.cpp \
    tile.cpp \
    boardvision.cpp

HEADERS  += mainwindow.h \
    pieces.h \
    board.h \
    player.h \
    controller.h \
    tile.h \
    db.h \
    boardvision.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
wince {
    CONFIG(debug, debug|release):sqlPlugins.files = $$QT_BUILD_TREE/plugins/sqldrivers/*d4.dll
    CONFIG(release, debug|release):sqlPlugins.files = $$QT_BUILD_TREE/plugins/sqldrivers/*[^d]4.dll
    sqlPlugins.path = sqldrivers
    INSTALLS += sqlPlugins
}

DISTFILES += \
    ../build-Chess-Desktop_Qt_5_8_0_MinGW_32bit-Debug/chess.db


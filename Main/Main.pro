#-------------------------------------------------
#
# Project created by QtCreator 2018-04-07T10:32:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app
#SUBDIRS = Main Test

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compilse if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        game.cpp \
    tile.cpp \
    player.cpp \
    node.cpp \
    board.cpp \
    humanplayer.cpp \
    aiplayer.cpp \
    playerdisplayhandler.cpp \
    playerdashboard.cpp \
    welcomescreen.cpp \
    resourcewidget.cpp \
    scoreboardwidget.cpp \
    dicerollnumber.cpp \
    wall.cpp \
    building.cpp


HEADERS += \
        game.h \
    tile.h \
    resource.h \
    player.h \
    node.h \
    board.h \
    humanplayer.h \
    aiplayer.h \
    playerdisplayhandler.h \
    playerdashboard.h \
    welcomescreen.h \
    resourcewidget.h \
    building.h \
    scoreboardwidget.h \
    dicerollnumber.h \
    wall.h \
    building.h \
    buildingenums.h \
    move.h

FORMS += \
        game.ui \
    welcomescreen.ui

RESOURCES += \
    resources.qrc

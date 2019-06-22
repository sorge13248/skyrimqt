#-------------------------------------------------
#
# Project created by QtCreator 2019-06-20T12:03:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skyrim-qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    console.cpp \
    qtgame.cpp \
    basic.cpp \
    Enemy/enemy.cpp \
    Enemy/animal.cpp \
    Enemy/ghost.cpp \
    Enemy/raider.cpp \
    Enemy/raiderboss.cpp \
    player.cpp \
    qcontainer.cpp \
    Item/weapon.cpp \
    Item/item.cpp \
    Item/shield.cpp \
    matchwindow.cpp \
    qtsupport.cpp \
    inventoryitem.cpp

HEADERS += \
        mainwindow.h \
    console.h \
    qtgame.h \
    basic.h \
    Enemy/enemy.h \
    Enemy/animal.h \
    Enemy/ghost.h \
    Enemy/raider.h \
    Enemy/raiderboss.h \
    exceptions.h \
    core.h \
    player.h \
    qcontainer.h \
    Item/weapon.h \
    Item/item.h \
    Item/shield.h \
    matchwindow.h \
    qtsupport.h \
    inventoryitem.h

FORMS += \
        mainwindow.ui \
    matchwindow.ui \
    inventoryitem.ui

RESOURCES += \
    image.qrc

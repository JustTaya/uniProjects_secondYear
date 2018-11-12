#-------------------------------------------------
#
# Project created by QtCreator 2018-11-05T13:38:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab2
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
    timerlistitem.cpp \
    addtimerdialog.cpp \
    timeralarm.cpp \
    alarmlistitem.cpp \
    addalarmdialog.cpp \
    logmaker.cpp

HEADERS += \
        mainwindow.h \
    timerlistitem.h \
    addtimerdialog.h \
    timeralarm.h \
    alarmlistitem.h \
    addalarmdialog.h \
    logmaker.h

FORMS += \
        mainwindow.ui \
    timerlistitem.ui \
    addtimerdialog.ui \
    timeralarm.ui \
    alarmlistitem.ui \
    addalarmdialog.ui

greaterThan(QT_MAJOR_VERSION, 4) {
        QT += widgets
        QT += widgets multimedia
        DEFINES += HAVE_QT5
    }

RESOURCES += \
    icons/icons.qrc \
    sounds/sounds.qrc

DISTFILES += \
    Settings_Log.txt \
    AlarmsLog.txt \
    TimersLog.txt

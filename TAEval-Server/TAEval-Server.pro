#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T12:46:09
#
#-------------------------------------------------

QT       += core network sql

QT       -= gui

TARGET = TAEval-Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    connectionserver.cpp \
    connectionthread.cpp \
    dbcoordinator.cpp \
    tamanager.cpp \
    instructormanager.cpp \
    dataaccessmanager.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../TAEvalCommons/release/ -lTAEvalCommons
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../TAEvalCommons/debug/ -lTAEvalCommons
else:symbian: LIBS += -lTAEvalCommons
else:unix: LIBS += -L$$PWD/../TAEvalCommons/ -lTAEvalCommons

INCLUDEPATH += $$PWD/../TAEvalCommons
DEPENDPATH += $$PWD/../TAEvalCommons

HEADERS += \
    connectionserver.h \
    connectionthread.h \
    dbcoordinator.h \
    tamanager.h \
    instructormanager.h \
    dataaccessmanager.h

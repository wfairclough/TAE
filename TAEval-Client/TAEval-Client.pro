#-------------------------------------------------
#
# Project created by QtCreator 2013-09-10T12:45:39
#
#-------------------------------------------------

QT       += core gui network

TARGET = TAEval-Client
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    connectionclient.cpp \
    apiwindow.cpp \
    instructorcontrol.cpp

HEADERS  += loginwindow.h \
    connectionclient.h \
    apiwindow.h \
    instructorcontrol.h

FORMS    += loginwindow.ui \
    apiwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../TAEvalCommons/release/ -lTAEvalCommons
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../TAEvalCommons/debug/ -lTAEvalCommons
else:symbian: LIBS += -lTAEvalCommons
else:unix: LIBS += -L$$PWD/../TAEvalCommons/ -lTAEvalCommons

INCLUDEPATH += $$PWD/../TAEvalCommons
DEPENDPATH += $$PWD/../TAEvalCommons

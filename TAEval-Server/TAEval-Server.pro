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
    server.cpp \
    clientsocket.cpp \
    databasemanager.cpp \
    connectionthread.cpp \
    authenticationmanager.cpp

HEADERS += \
    server.h \
    clientsocket.h \
    databasemanager.h \
    connectionthread.h \
    authenticationmanager.h

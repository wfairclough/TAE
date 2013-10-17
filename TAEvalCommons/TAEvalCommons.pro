#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T18:31:54
#
#-------------------------------------------------

QT       -= gui

TARGET = TAEvalCommons
TEMPLATE = lib

DEFINES += TAEVALCOMMONS_LIBRARY

SOURCES += taevalcommons.cpp \
    instructor.cpp \
    teachingassistant.cpp \
    task.cpp \
    evaluation.cpp \
    administrator.cpp \
    user.cpp \
    course.cpp \
    persistable.cpp

HEADERS += taevalcommons.h\
        TAEvalCommons_global.h \
    instructor.h \
    teachingassistant.h \
    task.h \
    evaluation.h \
    administrator.h \
    user.h \
    course.h \
    persistable.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xECE0016F
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = TAEvalCommons.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

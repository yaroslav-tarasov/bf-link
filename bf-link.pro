#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T14:48:54
#
#-------------------------------------------------

QT       += network xml

QT       -= gui

TARGET = bf-link
TEMPLATE = lib

DEFINES += BFLINK_LIBRARY

SOURCES += bflink.cpp

HEADERS += bflink.h\
        bf-link_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE10DE810
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = bf-link.dll
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

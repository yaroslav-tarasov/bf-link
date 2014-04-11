#-------------------------------------------------
#
# Project created by QtCreator 2014-04-09T14:48:54
#
#-------------------------------------------------

QT       += network xml

QT       -= gui

TARGET = bf-link
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++0x

DEFINES += BFLINK_LIBRARY

SOURCES += bflink.cpp \
           netlink_socket.cpp

HEADERS += bflink.h\
        bf-link_global.h\
        netlink_socket.h

INCLUDEPATH += ../bf-ko

DESTDIR = ../../lib

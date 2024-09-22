# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Server

QT = core network
CONFIG += console

HEADERS = \
   $$PWD/server.h \
   messagehistory.h

SOURCES = \
   $$PWD/main.cpp \
   $$PWD/server.cpp \
   messagehistory.cpp

INCLUDEPATH = \
    $$PWD/. \
    ../Shared

#DEFINES = 


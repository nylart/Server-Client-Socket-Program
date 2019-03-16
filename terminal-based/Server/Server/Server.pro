QT += core
QT += network
QT += xmlpatterns
QT += xml
QT -= gui

CONFIG += c++11

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    xmlprocessor.cpp \
    validator.cpp \
    logoutput.cpp \
    receiver.cpp


HEADERS += \
    server.h \
    xmlprocessor.h \
    validator.h \
    global.h \
    logoutput.h \
    receiver.h

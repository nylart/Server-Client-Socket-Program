QT += core
QT += network
QT += xml
QT -= gui

CONFIG += c++11

TARGET = Client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    validator.cpp \
    logoutput.cpp

HEADERS += \
    client.h \
    validator.h \
    logoutput.h \
    global.h

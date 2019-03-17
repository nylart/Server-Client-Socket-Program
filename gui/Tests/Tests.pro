QT       += testlib
QT       += gui
QT       += network
QT       += xmlpatterns
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Tests
CONFIG   += console
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += ../SocketProgram
DEPENDPATH += $${INCLUDEPATH} # force rebuild if the headers change

#_SocketProgram = ../SocketProgram

#LIBS += -L../SocketProgram -lSocketProgram

SOURCES += \
    tst_tests.cpp \
    ../SocketProgram/server.cpp \
    ../SocketProgram/validator.cpp \
    ../SocketProgram/receiver.cpp \
    ../SocketProgram/xmlprocessor.cpp \
    ../SocketProgram/client.cpp


HEADERS += \
    ../SocketProgram/global.h \
    ../SocketProgram/server.h \
    ../SocketProgram/validator.h \
    ../SocketProgram/receiver.h \
    ../SocketProgram/xmlprocessor.h \
    ../SocketProgram/client.h


DISTFILES += \
    ../default.pri


#LIBS += \
#    += ../SocketProgram \
#    += -L / lib / x86_64-linux-gnu / -lz
#PRE_TARGETDEPS += ../SocketProgram

#DEFINES += SRCDIR=\\\"$$PWD/\\\"

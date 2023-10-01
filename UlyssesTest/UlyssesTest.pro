include(gtest_dependency.pri)
QT       += core
TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt
DEPENDPATH += . ../UlyssesApp
INCLUDEPATH += ../UlyssesApp
LIBS += -L../build-UlyssesApp-Desktop_Qt_6_4_0_GCC_64bit-Debug -lUlyssesApp

SOURCES += \
        main.cpp         tst_jsonttest.cpp

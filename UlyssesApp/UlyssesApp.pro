QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = UlyssesApp
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TEMPLATE = app
SOURCES += \
    event.cpp \
    eventedit.cpp \
    eventhandler.cpp \
    executionmanager.cpp \
    listitemwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    startupmode.cpp \
    type.cpp

HEADERS += \
    event.h \
    eventedit.h \
    eventhandler.h \
    executionmanager.h \
    listitemwidget.h \
    mainwindow.h \
    startupmode.h \
    type.h

DEFINES += ULYSSESAPP_LIBRARY

FORMS += \
    eventedit.ui \
    listitemwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

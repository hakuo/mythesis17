TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    CameraMgr.cpp

HEADERS += \
    CameraMgr.h

LIBS += `pkg-config opencv --cflags --libs`

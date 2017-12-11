TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    taskthread.cpp

LIBS+=`pkg-config opencv --cflags --libs`
LIBS+=-lpthread

HEADERS += \
    taskthread.h \
    common.h

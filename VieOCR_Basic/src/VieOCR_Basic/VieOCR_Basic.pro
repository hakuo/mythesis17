TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ocr.cpp \
    tts.cpp

LIBS+=`pkg-config opencv --cflags --libs`

HEADERS += \
    ocr.h \
    tts.h \
    common.h

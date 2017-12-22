TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    debug.c \
    UnitSelector.cpp \
    TTS.cpp \
    TextObjectTTS.cpp \
    Sound.cpp

HEADERS += \
    debug.h \
    config.h \
    UnitSelector.h \
    TTS.h \
    TextObjectTTS.h \
    Sound.h

INCLUDEPATH += /usr/include/glib-2.0/ \
    /usr/lib/x86_64-linux-gnu/glib-2.0/include/

LIBS += -lasound -lglib-2.0

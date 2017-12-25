TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    HunspellCorrector.cpp

HEADERS += \
    HunspellCorrector.h

LIBS += -lhunspell-1.6

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tcpserver.cpp \
    tcpsocket.cpp

HEADERS += \
    tcpserver.h \
    tcpsocket.h

INCLUDEPATH += /home/cuongdh8/workspace/lib/boost_1_66_0

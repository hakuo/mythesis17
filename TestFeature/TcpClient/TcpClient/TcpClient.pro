TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    TcpUtils/TcpUltis.cpp \
    main.cpp \
    tcpclient.cpp

HEADERS += \
    TcpUtils/TcpUtils.h \
    tcpclient.h


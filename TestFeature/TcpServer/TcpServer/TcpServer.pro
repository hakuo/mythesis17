TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    TcpServer/TcpServer.cpp \
    TcpUtils/TcpUtils.cpp \
    main.cpp

HEADERS += \
    TcpServer/TcpServer.h \
    TcpUtils/TcpUtils.h

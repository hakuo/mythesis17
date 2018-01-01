TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    TcpClient/TcpClient.cpp \
    TcpUtils/TcpUtils.cpp \
    main.cpp


HEADERS += \
    TcpClient/TcpClient.h \
    TcpUtils/TcpUtils.h



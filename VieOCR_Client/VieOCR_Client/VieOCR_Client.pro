TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    CameraMgr/CameraMgr.cpp \
    Sound/Sound.cpp \
    Task/CameraTask.cpp \
    Task/SpeakerTask.cpp \
    Task/Task.cpp \
    Task/TaskThread.cpp \
    Task/TcpClient_Task.cpp \
    Task/TcpServer_Task.cpp \
    TCP/TcpClient/TcpClient.cpp \
    TCP/TcpUtils/TcpUtils.cpp \
    ConsoleMenu.cpp \
    main.cpp

HEADERS += \
    CameraMgr/CameraMgr.h \
    Sound/Sound.h \
    Task/CameraTask.h \
    Task/SpeakerTask.h \
    Task/Task.h \
    Task/TaskThread.h \
    Task/TcpClient_Task.h \
    Task/TcpServer_Task.h \
    TCP/TcpClient/TcpClient.h \
    TCP/TcpUtils/TcpUtils.h \
    common.h \
    ConsoleMenu.h


LIBS += `pkg-config opencv --cflags --libs`
LIBS += -lpthread
LIBS += -lrt        # Message Queue
LIBS += -lasound

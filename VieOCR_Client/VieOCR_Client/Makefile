# Makefile for VieOCR client
APP = VieOCR_Client
all: $(APP)

CC = g++
CFLAGS = `pkg-config opencv --cflags`
CFLAGS += -Wall -std=c++11

LIBS = `pkg-config opencv --libs`
LIBS += -lpthread -lrt -lasound

SRCS = CameraMgr/CameraMgr.cpp \
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

INCS = -I. \

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(INCS)

$(APP): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCS) $(LIBS)

.PHONY: clean

clean:
	find . -name "*.o" -delete
	rm -f $(APP)


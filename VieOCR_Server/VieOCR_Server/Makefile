# Makefile for VieOCR client
APP = VieOCR_Server
all: $(APP)

CC = g++

SRCS = main.cpp \
    OCR/OCR_Utils/src/ocr_hmm_decoder.cpp \
    OCR/OCR_Utils/src/ocr_holistic.cpp \
    OCR/OCR_Utils/src/ocr_tesseract.cpp \
    OCR/DnnOCR.cpp \
    OCR/ImageProcessing.cpp \
    OCR/OCR.cpp \
    OCR/OCR_Factory.cpp \
    OCR/TesseractOCR.cpp \
    Task/OCR_Task.cpp \
    Task/Task.cpp \
    Task/TaskThread.cpp \
    Task/TcpClient_Task.cpp \
    Task/TcpServer_Task.cpp \
    Task/TTS_Task.cpp \
    TCP/TcpClient/TcpClient.cpp \
    TCP/TcpUtils/TcpUtils.cpp \
    TTS/TTS_Utils/Sound.cpp \
    TTS/TTS_Utils/TextObjectTTS.cpp \
    TTS/TTS_Utils/UnitSelector.cpp \
    TTS/TTS.cpp \


CFLAGS = `pkg-config opencv --cflags`
CFLAGS += -Wall -std=c++11

LIBS = `pkg-config opencv --libs`
LIBS += -lpthread -lrt -lasound -lhunspell-1.6 -ltesseract -lglib-2.0

INCS = -I. \
	-I/usr/include/glib-2.0/ \
	-I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ \

DEFINES += -DHAVE_TESSERACT

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(INCS) $(DEFINES)

$(APP): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	find . -name "*.o" -delete
	rm -f $(APP)


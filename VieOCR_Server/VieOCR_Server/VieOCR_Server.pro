TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
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
    TTS/TTS_Utils/debug.c

LIBS += -lpthread -ltesseract
LIBS += `pkg-config opencv --cflags --libs`
LIBS += -lasound -lglib-2.0
LIBS += -lrt        # Message Queue
LIBS += -lhunspell-1.6


INCLUDEPATH += /usr/include/glib-2.0/ \
    /usr/lib/x86_64-linux-gnu/glib-2.0/include/ \

DEFINES += HAVE_TESSERACT

HEADERS += \
    OCR/OCR_Utils/include/text/erfilter.hpp \
    OCR/OCR_Utils/include/text/ocr.hpp \
    OCR/OCR_Utils/include/text/textDetector.hpp \
    OCR/OCR_Utils/include/precomp.hpp \
    OCR/OCR_Utils/include/text.hpp \
    OCR/DnnOCR.h \
    OCR/ImageProcessing.h \
    OCR/OCR.h \
    OCR/OCR_Factory.h \
    OCR/TesseractOCR.h \
    Task/OCR_Task.h \
    Task/Task.h \
    Task/TaskThread.h \
    Task/TcpClient_Task.h \
    Task/TcpServer_Task.h \
    Task/TTS_Task.h \
    TCP/TcpClient/TcpClient.h \
    TCP/TcpUtils/TcpUtils.h \
    TTS/TTS_Utils/config.h \
    TTS/TTS_Utils/debug.h \
    TTS/TTS_Utils/Sound.h \
    TTS/TTS_Utils/TextObjectTTS.h \
    TTS/TTS_Utils/UnitSelector.h \
    TTS/TTS.h \
    common.h

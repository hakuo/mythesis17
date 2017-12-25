#-------------------------------------------------
#
# Project created by QtCreator 2017-12-19T17:26:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VieOCR_Basic_GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OCR/OCR_Utils/src/erfilter.cpp \
    OCR/OCR_Utils/src/ocr_beamsearch_decoder.cpp \
    OCR/OCR_Utils/src/ocr_hmm_decoder.cpp \
    OCR/OCR_Utils/src/ocr_holistic.cpp \
    OCR/OCR_Utils/src/ocr_tesseract.cpp \
    OCR/OCR_Utils/src/text_detectorCNN.cpp \
    OCR/DnnOCR.cpp \
    OCR/ImageProcessing.cpp \
    OCR/OCR.cpp \
    OCR/OCR_Factory.cpp \
    OCR/TesseractOCR.cpp \
    Task/OCR_Task.cpp \
    Task/TaskThread.cpp \
    Task/TcpServer_Task.cpp \
    Task/TTS_Task.cpp \
    TCP/TcpServer/TcpServer.cpp \
    TTS/TTS_Utils/Sound.cpp \
    TTS/TTS_Utils/TextObjectTTS.cpp \
    TTS/TTS_Utils/UnitSelector.cpp \
    TTS/TTS.cpp \
    main.cpp \
    mainwindow.cpp \
    TTS/TTS_Utils/debug.c \
    TCP/TcpClient/TcpClient.cpp \
    TCP/TcpUtils/TcpUtils.cpp


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
    Task/TaskThread.h \
    Task/TcpServer_Task.h \
    Task/TTS_Task.h \
    TCP/TcpServer/TcpServer.h \
    TCP/TcpUtils/TcpUtils.h \
    TTS/TTS_Utils/config.h \
    TTS/TTS_Utils/debug.h \
    TTS/TTS_Utils/Sound.h \
    TTS/TTS_Utils/TextObjectTTS.h \
    TTS/TTS_Utils/UnitSelector.h \
    TTS/TTS.h \
    common.h \
    mainwindow.h \
    TCP/TcpClient/TcpClient.h


FORMS += \
        mainwindow.ui

LIBS += -lpthread -ltesseract
LIBS += `pkg-config opencv --cflags --libs`
LIBS += -lasound -lglib-2.0
LIBS += -lrt        # Message Queue
LIBS += -lhunspell-1.6

INCLUDEPATH += /usr/include/glib-2.0/ \
    /usr/lib/x86_64-linux-gnu/glib-2.0/include/ \
    /home/cuongdh8/workspace/lib/boost_1_66_0 \

DEFINES += HAVE_TESSERACT

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
    ocr/bkocr.cpp \
    ocr/imageprocessing.cpp \
    ocr/ocr.cpp \
    ocr/ocrfactory.cpp \
    ocr/tesseractocr.cpp \
    task/ocrtask.cpp \
    task/taskthread.cpp \
    task/tcpservertask.cpp \
    task/ttstask.cpp \
    tcp_server/tcpserver.cpp \
    tesseract/src/erfilter.cpp \
    tesseract/src/ocr_beamsearch_decoder.cpp \
    tesseract/src/ocr_hmm_decoder.cpp \
    tesseract/src/ocr_holistic.cpp \
    tesseract/src/ocr_tesseract.cpp \
    tesseract/src/text_detectorCNN.cpp \
    tts/tts.cpp \
    main.cpp \
    mainwindow.cpp



HEADERS += \
    ocr/bkocr.h \
    ocr/imageprocessing.h \
    ocr/ocr.h \
    ocr/ocrfactory.h \
    ocr/tesseractocr.h \
    task/ocrtask.h \
    task/taskthread.h \
    task/tcpservertask.h \
    task/ttstask.h \
    tcp_server/tcpserver.h \
    tesseract/include/text/erfilter.hpp \
    tesseract/include/text/ocr.hpp \
    tesseract/include/text/textDetector.hpp \
    tesseract/include/precomp.hpp \
    tesseract/include/text.hpp \
    tts/tts.h \
    common.h \
    mainwindow.h




FORMS += \
        mainwindow.ui

LIBS += -lpthread -ltesseract
LIBS += `pkg-config opencv --cflags --libs`

DEFINES += HAVE_TESSERACT

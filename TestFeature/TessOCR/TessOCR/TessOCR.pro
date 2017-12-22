TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    tesseract/src/erfilter.cpp \
    tesseract/src/ocr_beamsearch_decoder.cpp \
    tesseract/src/ocr_hmm_decoder.cpp \
    tesseract/src/ocr_holistic.cpp \
    tesseract/src/ocr_tesseract.cpp \
    tesseract/src/text_detectorCNN.cpp \
    main.cpp \
    tessocr.cpp

HEADERS += \
    tesseract/include/text/erfilter.hpp \
    tesseract/include/text/ocr.hpp \
    tesseract/include/text/textDetector.hpp \
    tesseract/include/precomp.hpp \
    tesseract/include/text.hpp \
    tessocr.h

LIBS += `pkg-config opencv --cflags --libs`
LIBS += -ltesseract

DEFINES += HAVE_TESSERACT

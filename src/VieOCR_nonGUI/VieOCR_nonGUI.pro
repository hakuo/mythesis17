TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    image_processing_util.cpp

# Add OpenCV lib
CONFIG += link_pkgconfig
PKGCONFIG += opencv

HEADERS += \
    common.h \
    image_processing_util.h

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

# Add OpenCV lib
CONFIG += link_pkgconfig
PKGCONFIG += opencv


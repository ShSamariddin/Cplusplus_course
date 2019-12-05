TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    array_list.cpp \
    counted.cpp

HEADERS += \
    array_list.h \
    counted.h

QMAKE_CXXFLAGS += -Wall -pedantic

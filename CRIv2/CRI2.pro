#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T12:44:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CRI2
TEMPLATE = app


SOURCES += main.cpp\
        cri.cpp \
    Spectrum.cpp

HEADERS  += cri.h \
    defines.h \
    Spectrum.h

FORMS    += cri.ui
QMAKE_CXXFLAGS += -std=c++11

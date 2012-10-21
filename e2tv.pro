#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T10:25:58
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = e2tv
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    demand.cpp \
    search.cpp \
    details.cpp \
    sources.cpp \
    source.cpp \
    netflixsource.cpp \
    trailersource.cpp \
    torrentsource.cpp \
    dailysource.cpp \
    youtubesource.cpp

HEADERS += \
    demand.h \
    search.h \
    details.h \
    sources.h \
    source.h \
    netflixsource.h \
    trailersource.h \
    torrentsource.h \
    dailysource.h \
    youtubesource.h

QMAKE_CXXFLAGS += -std=c++11

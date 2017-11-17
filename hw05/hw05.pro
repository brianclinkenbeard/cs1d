TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    patient.cpp \
    compare.cpp

HEADERS += \
    patient.h \
    listpriorityqueue.h \
    compare.h

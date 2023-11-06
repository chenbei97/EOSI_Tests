QT += core gui widgets
SOURCES += demoqt.cpp
HEADERS += demoqt.h \
            toupcam.h
LIBS += -l$$PWD/bin/toupcam

CONFIG += utf8_source
DESTDIR += $$PWD/bin

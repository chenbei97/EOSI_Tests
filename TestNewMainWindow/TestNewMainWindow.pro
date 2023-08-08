QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG   += utf8_source
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    gradienthiddenanimation.cpp \
    gradienthiddenwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    pattern.cpp \
    scanconfigdata.cpp \
    scancreateconfig.cpp \
    scanexperimentconfig.cpp \
    scanpatternconfig.cpp \
    scanpatternpreview.cpp \
    scanplanconfig.cpp \
    scansettingconfig.cpp \
    scantimeconfig.cpp \
    scantypeconfig.cpp \
    scanvesselconfig.cpp \
    scanvesselsummary.cpp \
    sqldbquerypanel.cpp \
    sqldbquerytable.cpp \
    sqldbquerytree.cpp \
    sqlqueryconsole.cpp\
    scandescriptionconfig.cpp

HEADERS += \
    Constant.h \
    Style.h \
    button.h \
    core.h \
    gradienthiddenanimation.h \
    gradienthiddenwidget.h \
    mainwindow.h \
    pattern.h \
    scanconfigdata.h \
    scancreateconfig.h \
    scanexperimentconfig.h \
    scanpatternconfig.h \
    scanpatternpreview.h \
    scanplanconfig.h \
    scansettingconfig.h \
    scantimeconfig.h \
    scantypeconfig.h \
    scanvesselconfig.h \
    scanvesselsummary.h \
    sqldbquerypanel.h \
    sqldbquerytable.h \
    sqldbquerytree.h \
    sqlqueryconsole.h\
    scandescriptionconfig.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

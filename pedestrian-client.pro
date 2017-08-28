#-------------------------------------------------
#
# Project created by QtCreator 2017-08-12T13:35:22
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG+=c++11
TARGET = pedestrian-client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    yuvrender.cpp

HEADERS  += mainwindow.h \
    client.h \
    camera.h \
    config.h \
    common.h \
    yuvrender.h \
    protocol.h

FORMS    += mainwindow.ui
INCLUDEPATH +=/usr/include
LIBS +=   -lopencv_core  -lopencv_highgui  -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video

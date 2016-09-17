QT += core
QT -= gui
QT += widgets

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/hdf5/serial/include
INCLUDEPATH += /usr/local/cuda/include
INCLUDEPATH += /home/jun/caffe-segnet/include

LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_videoio
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_imgcodecs

LIBS += -L/usr/lib/x86_64-linux-gnu/hdf5/serial
LIBS += -lhdf5

LIBS += -L/home/jun/caffe-segnet/build/lib
LIBS += -lcaffe

LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -lboost_system
LIBS += -lglog

LIBS += -llcm

TARGET = front_camera
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    classification.cpp \
    frontcameradialog.cpp \
    csocket.cpp \
    CLabel/CLabel.cpp \
    CMission/CMission.cpp \
    CImage_Thread/CImage_Thread.cpp \
    CLCM/CLCM.cpp

FORMS += \
    front_camera_detection.ui

HEADERS += \
    classification.hpp \
    frontcameradialog.h \
    csocket.h \
    CLabel/CLabel.h \
    CLabel/Label_Def.h \
    CMission/CMission.h \
    CImage_Thread/CImage_Thread.h \
    CLCM/CLCM.h \
    eurecar/vision_front_cam.hpp \
    eurecar/vision_lane.hpp

DISTFILES +=



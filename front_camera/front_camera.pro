QT += core
QT -= gui
QT += widgets

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/hdf5/serial/include
INCLUDEPATH += /usr/local/cuda/include
INCLUDEPATH += /home/winner/caffe-segnet/include

LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_videoio
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_imgcodecs

LIBS += -L/usr/lib/x86_64-linux-gnu/hdf5/serial
LIBS += -lhdf5

LIBS += -L/home/winner/caffe-segnet/build/lib
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
    CLabel/CLabel.cpp \
    CMission/CMission.cpp \
    CImage_Thread/CImage_Thread.cpp \
    CLCM/CLCM.cpp \
    CNetImg/CNetImg.cpp \
    CNetImg/csocket.cpp \
    CSaveImg/CSaveImg.cpp \
    CMission/CLenet/CLenet.cpp \
    CMission/CLogisticFnc/CLogisticFnc.cpp

FORMS += \
    front_camera_detection.ui

HEADERS += \
    classification.hpp \
    frontcameradialog.h \
    CLabel/CLabel.h \
    CLabel/Label_Def.h \
    CMission/CMission.h \
    CImage_Thread/CImage_Thread.h \
    CLCM/CLCM.h \
    eurecar/vision_front_cam.hpp \
    eurecar/vision_lane.hpp \
    CNetImg/CNetImg.h \
    CNetImg/csocket.h \
    CSaveImg/CSaveImg.h \
    CMission/CLenet/CLenet.hpp \
    CMission/CLogisticFnc/CLogisticFnc.h

DISTFILES +=


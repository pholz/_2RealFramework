#-------------------------------------------------
#
# Project created by QtCreator 2014-02-06T11:09:24
#
#-------------------------------------------------

QT       += opengl xml

TARGET = UnitTestBundle
TEMPLATE = lib

DEFINES += UNITTESTBUNDLE_LIBRARY _UNIX

INCLUDEPATH += ../../../../../kernel/src

SOURCES += \
    ../../../src/BlockInletWidget.cpp \
    ../../../src/BlockOutletWidget.cpp \
    ../../../src/BlockUnitTestWidget.cpp \
    ../../../src/BundleUnitTestWidget.cpp \
    ../../../src/QFileDialogWidget.cpp \
    ../../../src/QGlSkeletonWidget.cpp \
    ../../../src/QGlTextureImage.cpp \
    ../../../src/QPointWidget.cpp

HEADERS += \
    ../../../src/BlockInletWidget.h \
    ../../../src/BlockOutletWidget.h \
    ../../../src/BlockUnitTestWidget.h \
    ../../../src/BundleUnitTestWidget.h \
    ../../../src/QFileDialogWidget.h \
    ../../../src/QGlSkeletonWidget.h \
    ../../../src/QGlTextureImage.h \
    ../../../src/QPointWidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../../../../../kernel/lib/ -l_2RealFrameworkD

INCLUDEPATH += $$PWD/../../../../../kernel
DEPENDPATH += $$PWD/../../../../../kernel

QMAKE_CXXFLAGS += `pkg-config --cflags eigen3` -fPIC -std=c++11

unix:!macx: LIBS += -L$$PWD/../../../../../../../../../../usr/lib/x86_64-linux-gnu/ -lQGLViewer

INCLUDEPATH += $$PWD/../../../../../../../../../../usr/include/QGLViewer
DEPENDPATH += $$PWD/../../../../../../../../../../usr/include/QGLViewer

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../../../../../usr/lib/x86_64-linux-gnu/libQGLViewer.a

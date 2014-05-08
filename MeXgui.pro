#-------------------------------------------------
#
# Project created by QtCreator 2013-12-12T14:26:28
#
#-------------------------------------------------

QT       += core gui widgets multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeXgui
TEMPLATE = app
CONFIG += c++11 static

#include($$PROJECTROOT/src/libQtAV.pri)

SOURCES += core/gui/MeXgui.cpp\
        core/gui/MainForm.cpp \
    core/gui/PreviewEditor.cpp \
    core/gui/VideoPlayer.cpp \
    core/gui/globals.cpp \
    core/gui/editor.cpp \
    core/gui/Dialog.cpp \
    core/gui/editor/finddialog.cpp \
    core/gui/editor/findform.cpp \
    core/gui/editor/findreplacedialog.cpp \
    core/util/QTFFmpegWrapper/QAudioDecoderF.cpp \
    core/util/QTFFmpegWrapper/QVideoDecoder.cpp \
    core/util/QTFFmpegWrapper/QVideoEncoder.cpp \
    core/util/importexport.cpp \
    core/util/sql.cpp \
    core/util/error.cpp \
    core/gui/Encoder.cpp \
    core/gui/editor/FindReplace.cpp

HEADERS  += core/gui/MainForm.h \
    core/gui/PreviewEditor.h \
    core/gui/VideoPlayer.h \
    core/gui/globals.h \
    core/gui/editor.h \
    core/gui/Dialog.h \
    core/gui/editor/finddialog.h \
    core/gui/editor/findform.h \
    core/gui/editor/findreplace_global.h \
    core/gui/editor/findreplacedialog.h \
    core/gui/ffmpeg.h \
    core/util/QTFFmpegWrapper/QAudioDecoderF.h \
    core/util/QTFFmpegWrapper/QVideoDecoder.h \
    core/util/QTFFmpegWrapper/QVideoEncoder.h \
    core/util/importexport.h \
    core/util/sql.h \
    core/util/error.h \
    core/gui/Encoder.h \
    core/gui/editor/FindReplace.h

FORMS    +=  core/gui/forms/MainForm.ui\
    core/gui/forms/PreviewEditor.ui \
    core/gui/forms/VideoPlayer.ui \
    core/gui/forms/Encoder.ui \
    core/gui/forms/Editor.ui \
    core/gui/editor/FindReplace.ui
    

#FFMPEG includepaths -> Must be ffmped static build
INCLUDEPATH += "D:/Kirjastot/ffmpeg/include"
LIBS += -L"D:/Kirjastot/ffmpeg/lib"
LIBS += -lavutil \
        -lavcodec \
        -lavformat \
        -lswscale \
        -lavdevice \
        -lavfilter \
        -lpostproc

#QtAV includepaths -> Must be dynamic build
INCLUDEPATH += "D:/Kirjastot/QtAV/include"
LIBS += -L"D:/Kirjastot/QtAV/lib"
LIBS += -lQtAV1

#QtAV portaudio -> Must be static build
INCLUDEPATH += "D:/Kirjastot/portaudio/include"
LIBS += -L"D:/Kirjastot/portaudio/lib"
LIBS += -lportaudio

SUBDIRS += \
    core/gui/CuteNotes/CuteNotes.pro

RESOURCES += \
    core/gui/editor/icons.qrc

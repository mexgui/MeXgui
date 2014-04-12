#-------------------------------------------------
#
# Project created by QtCreator 2013-12-12T14:26:28
#
#-------------------------------------------------

QT       += core gui widgets phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeXgui
TEMPLATE = app

SOURCES += core/gui/MeXgui.cpp\
        core/gui/MainForm.cpp \
    core/gui/PreviewEditor.cpp

HEADERS  += core/gui/MainForm.h \
    core/gui/PreviewEditor.h

FORMS    += core/gui/MainForm.ui core/gui/PreviewEditor.ui \


/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Nov 16 17:17:29 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <phonon/seekslider.h>
#include <phonon/videoplayer.h>
#include <phonon/volumeslider.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    Phonon::SeekSlider *seek;
    Phonon::VolumeSlider *volume;
    QPushButton *open;
    QPushButton *play;
    QPushButton *left;
    QPushButton *right;
    QPushButton *fullscreen;
    Phonon::VideoPlayer *videoPlayer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(320, 315);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        seek = new Phonon::SeekSlider(centralWidget);
        seek->setObjectName(QString::fromUtf8("seek"));
        seek->setGeometry(QRect(10, 270, 301, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(seek->sizePolicy().hasHeightForWidth());
        seek->setSizePolicy(sizePolicy1);
        seek->setIconVisible(false);
        volume = new Phonon::VolumeSlider(centralWidget);
        volume->setObjectName(QString::fromUtf8("volume"));
        volume->setGeometry(QRect(213, 240, 101, 29));
        open = new QPushButton(centralWidget);
        open->setObjectName(QString::fromUtf8("open"));
        open->setGeometry(QRect(10, 240, 51, 21));
        play = new QPushButton(centralWidget);
        play->setObjectName(QString::fromUtf8("play"));
        play->setGeometry(QRect(70, 240, 51, 21));
        left = new QPushButton(centralWidget);
        left->setObjectName(QString::fromUtf8("left"));
        left->setGeometry(QRect(130, 240, 21, 21));
        right = new QPushButton(centralWidget);
        right->setObjectName(QString::fromUtf8("right"));
        right->setGeometry(QRect(150, 240, 21, 21));
        fullscreen = new QPushButton(centralWidget);
        fullscreen->setObjectName(QString::fromUtf8("fullscreen"));
        fullscreen->setGeometry(QRect(180, 240, 31, 21));
        videoPlayer = new Phonon::VideoPlayer(centralWidget);
        videoPlayer->setObjectName(QString::fromUtf8("videoPlayer"));
        videoPlayer->setGeometry(QRect(0, 0, 321, 231));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MeXGui preview", 0, QApplication::UnicodeUTF8));
        open->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        play->setText(QApplication::translate("MainWindow", "Play", 0, QApplication::UnicodeUTF8));
        left->setText(QString());
        right->setText(QString());
        fullscreen->setText(QApplication::translate("MainWindow", "FC", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

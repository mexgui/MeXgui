#include "VideoPlayer.h"
#include "ui_VideoPlayer.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#ifndef QT_NO_OPENGL
//#include <QtOpenGL/QGLWidget>
#endif

using namespace globals;

VideoPlayer::VideoPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);

}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

/*void VideoPlayer::doSetup(QThread &cThread)
{
    connect(&cThread,SIGNAL(started()),this,SLOT(doThread()));
    this->moveToThread(&cThread);
}*/

void VideoPlayer::init()
{
    //qDebug() << i;

    //mediaPlayer = new AVPlayer;
    //videoItem = new GraphicsItemRenderer;
    //videoItem->resizeRenderer(430, 320);
    //videoItem->setOutAspectRatioMode(VideoRenderer::RendererAspectRatio);


    //this->thread(msleep(countRate))
    /*
    QGraphicsScene * scene = new QGraphicsScene(this);
        scene->addItem(videoItem);

    ui->videoRect->setScene(scene);
    ui->videoRect->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
#if 0
    #ifndef QT_NO_OPENGL
    QGLWidget *glw = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    glw->setAutoFillBackground(false);
    ui->videoRect->setCacheMode(QGraphicsView::CacheNone);
    ui->videoRect->setViewport(glw);
    #endif
    #endif //0

    mediaPlayer->setFile(InputPath);
    //connect(ui->Play, SIGNAL(clicked()), SLOT(play()));
    mediaPlayer->setRenderer(videoItem);
    */

}

void VideoPlayer::on_Play_clicked()
{
    /*if (!isPlaying) {
        mediaPlayer->play();
        isPlaying = true;
        ui->Play->setText("Stop");
    }
    else {
        mediaPlayer->pause(true);
        isPlaying = false;
        ui->Play->setText("Play");

    }*/
}

void VideoPlayer::on_Wind_pressed()
{
    //mediaPlayer->seek(w);
}

void VideoPlayer::on_Wind_clicked()
{
    //mediaPlayer->seekForward();
}
void VideoPlayer::on_ReWind_pressed()
{
    //mediaPlayer->seek(r);
}

void VideoPlayer::on_ReWind_clicked()
{
    //mediaPlayer->seekBackward();
}

void VideoPlayer::changeEvent(QEvent *e)
{
     QWidget::changeEvent(e);
     switch (e->type()) {
     case QEvent::LanguageChange:
         ui->retranslateUi(this);
         break;
     default:
         break;
     }
}

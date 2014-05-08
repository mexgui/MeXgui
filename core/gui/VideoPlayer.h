#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QtAV/AVPlayer.h>
#include <QtAV/GraphicsItemRenderer.h>
#include "globals.h"

using namespace QtAV;

namespace Ui {

        class VideoPlayer;

}

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();
   void doSetup(QThread &cThread);
   QSize sizeHint() const { return QSize(430, 320); }

private:
    Ui::VideoPlayer *ui;
    //AVPlayer *mediaPlayer;
    //GraphicsItemRenderer *videoItem;
    QString file;
    qreal w = 0.10; //forward
    qreal r = -0.10; //backward
    bool isPlaying = false;
signals:

public slots:


private slots:

    void init();
    void on_Play_clicked();
    void on_Wind_pressed();
    void on_Wind_clicked();
    void on_ReWind_pressed();
    void on_ReWind_clicked();

protected:
    void changeEvent(QEvent *e);
};




#endif // VIDEOPLAYER_H

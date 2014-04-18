#include "PreviewEditor.h"
#include "ui_PreviewEditor.h"
#define Vplayer ui->videoPlayer

PreviewEditor::PreviewEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewEditor)
{
    ui->setupUi(this);

}
PreviewEditor::~PreviewEditor()
{
    delete ui;
}
void PreviewEditor::videoFile(QString filepath) {
    MediaPath = filepath;
    Vplayer->load(MediaPath);
    media = Vplayer->mediaObject();
    audio = Vplayer->audioOutput();
    Phonon::createPath(media, audio);
    media->setTickInterval(1);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    ui->Seek->setMediaObject(media);
    ui->Volume->setAudioOutput(audio);
    //connect(Vplayer, currentTime (), ui->Time, currentTime ());



}

void PreviewEditor::tick(qint64 time)
{
    QTime displayTime((time / 360000), (time / 60000) % 60, (time / 1000) % 60, (time / 100) % 60);
    ui->Time->setTime(displayTime); //toString("hh:mm:ss.zz")
    //setWindowTitle(QString("%1[%2]").arg(fname).arg(displayTime.toString("mm:ss")));
}

void PreviewEditor::on_Play_clicked()
{
    if (Vplayer->isPlaying()) {
        Vplayer->pause();
        ui->Play->setText("Play");
    }
    else {

        Vplayer->play();
        ui->Play->setText("Pause");
    }

}

void PreviewEditor::on_Wind_pressed()
{
    Vplayer->seek(1);
}

void PreviewEditor::on_Wind_clicked()
{
    Vplayer->seek(10);
}
void PreviewEditor::on_ReWind_pressed()
{
    //seek bac
    Vplayer->seek(-1);
}

void PreviewEditor::on_ReWind_clicked()
{
    //one frame back
    Vplayer->seek(-10);
}

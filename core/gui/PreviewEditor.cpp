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
    media->setTickInterval(1000);

    Phonon::createPath(media, audio);
    //ui->Volume->setVolume(Vplayer->volume());
    //connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    //connect(media, SIGNAL(currentSourceChanged(Phonon::MediaSource)),this, SLOT(sourceChanged(Phonon::MediaSource)));
    //connect(media, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));
    connect(media, SIGNAL(setAudioOutput()), Vplayer, SLOT(audioOutput()));

    ui->Seek->setMediaObject(media);
    ui->Volume->setAudioOutput(audio);
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

#include "PreviewEditor.h"
#include "ui_PreviewEditor.h"
#include <QThread>
#include "VideoPlayer.h"
#include "Dialog.h"

PreviewEditor::PreviewEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewEditor)
{
    ui->setupUi(this);

    //QThread videoThread;
    //Setup Videoplayer to separate thread for HD movies and detaching to another window
    //videoThread.setObjectName("MeXgui VideoPlayer");
    videoWidget = new VideoPlayer(this);

    //videoWidget->doSetup(videoThread);
    //videoThread.start();
    ui->PreviewLayout->addWidget(videoWidget);
    videoWidget->show();

    textEditor = new Editor(this);
    ui->textEditorLayout->addWidget(textEditor);
    textEditor->show();
}
 PreviewEditor::~PreviewEditor()
{
    delete ui;
}
void PreviewEditor::changeEvent(QEvent *e)
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

void PreviewEditor::on_tabWidget_tabBarDoubleClicked(int index)
{
    //Fetch tabindex and tab name
    QString tabName = ui->tabWidget->tabText(index);

    if (tabName == "Preview") {

        //Remove Preview and close the tab
        ui->PreviewLayout->removeWidget(videoWidget);
        ui->tabWidget->removeTab(index);

        //Using custom Dialog class that emits close() signal when QDialog is closed
        Dialog * mediaPlayer = new Dialog(this);
        mediaPlayer->setWindowTitle("MeXgui previewplayer");

        //Setup layout for detached window
        QHBoxLayout * mediaLayout = new QHBoxLayout;
        mediaLayout->setMargin(0);
        mediaLayout->setSizeConstraint(QLayout::SetNoConstraint);
        mediaLayout->addWidget(videoWidget);

        //Finally setup dialog and display it
        mediaPlayer->setLayout(mediaLayout);
        mediaPlayer->show();

        //Connect Mediaplayer closeEvent to PreviewEditor function to rebuild tabs
        connect(mediaPlayer,SIGNAL(closed()),this,SLOT(PreviewDialogClosed()));

    }
}

void PreviewEditor::PreviewDialogClosed()
{
    //We construct the tabWidget back to normal
    ui->tabWidget->insertTab(0,ui->Preview,tr("Preview"));
    ui->PreviewLayout->addWidget(videoWidget);
    videoWidget->show();
}

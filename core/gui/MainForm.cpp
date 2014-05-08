#include "MainForm.h"
#include "ui_MainForm.h"
#include "PreviewEditor.h"
#include <QFileDialog>
#include <QFile>
#include <QString>
#include "globals.h"
#include <QMessageBox>
#include "../util/importexport.h"

using namespace globals;
using namespace core::util;

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    db->setDatabaseName("MeXgui.db");
    try {
        if (!db.open()) throw QString("Cannot open database");

    }
    catch (QString thisError) {
        QMessageBox::critical(this,"MeXgui",thisError + ". Please check if MeXgui.db is in MeXgui installed folder.",QMessageBox::Ok);
        ~MainForm();
    }

}

MainForm::~MainForm()
{
    db.close();
    delete ui;
}

void MainForm::changeEvent(QEvent *e)
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

void MainForm::on_PreviewEditorButton_clicked() {  

        //Veditor->videoFile(InputPath);
     if (!PreviewWindow) {
        PreEditor = new PreviewEditor(this);
        ui->mainLayout->addWidget(PreEditor,0,6,0,3);

        PreEditor->show();
        //quint16 GuiWidth = ui->centralwidget->width() + Veditor->width();
        //ui->centralwidget->setMinimumSize(1280,0);
        this->adjustSize();
        ui->PreviewEditorButton->setText("Close PreviewEditor");
        PreviewWindow = true;
    }
    else {
        PreEditor->hide();
        ui->mainLayout->removeWidget(PreEditor);
        delete PreEditor;
        this->adjustSize();
        ui->PreviewEditorButton->setText("Open PreviewEditor");
        PreviewWindow = false;
     }

}



void MainForm::on_Vopenavs_clicked()
{
    InputPath = QFileDialog::getOpenFileName(this,tr("Open video file"));
    QFile f(InputPath);
    InputFileName = f.fileName();
    QStringList parts = InputFileName.split(".");
    InputExtension = parts.at(parts.size()-1);

    ui->VinputText->setText(InputFileName);
    ui->VoutputText->setText(parts.at(parts.size()-2) + ".mkv");
    ui->PreviewEditorButton->setEnabled(true);

}


void MainForm::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About MeXgui"),
             tr("The <b>MeXgui</b> is MeGUI like program with new features like "
                "sclite database, mutiple formats encoding/transcoding "
                "and easy gui layout"));
}

//We consider this that audio cannot dragged because program needs both video and audio
//Todo: add audio dragging later
void MainForm::dragEnterEvent(QDragEnterEvent *e)
{

    QString path = e->mimeData()->text().remove("file:///");
    QFile file(path);
    QStringList parts = file.fileName().split(".");
    QString ext = parts.at(parts.size()-1);
    if (ext == "avs" || ext == "mpg" || ext == "avi" || ext == "mpeg" || ext == "mp4" || ext == "mkv") {
        e->acceptProposedAction();
    }

}


void MainForm::dragDrop(QDropEvent *e)
{
    QString path = e->mimeData()->text().remove("file:///");
    QFile file(path);
    QStringList parts = file.fileName().split(".");
    QString ext = parts.at(parts.size()-1);
    InputFileName = file.fileName();
    InputPath = path;
    InputExtension = ext;
}

void MainForm::on_actionAudio_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Import Megui XML audio profiles"),QApplication::applicationDirPath(),"XML files (*.xml)");
    importExport * ia = new importExport(this);

    foreach(QString str, fileNames)
    {
        QFile input = str;
        ia->importAudioProfile(input);
    }
    delete ia;

}

void MainForm::on_actionVideo_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Import Megui XML video profiles"),QApplication::applicationDirPath(),"XML files (*.xml)");
    importExport * iv = new importExport(this);

    foreach(QString str, fileNames)
    {
        QFile input = str;
        iv->importVideoProfile(input);
    }
    delete iv;
}

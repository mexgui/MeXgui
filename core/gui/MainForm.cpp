#include "MainForm.h"
#include "ui_MainForm.h"
#include "previeweditor.h"
#include <QFileDialog>
#include <QFile>
#include <QString>




MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_PreviewEditorButton_clicked() {  

    PreviewEditor * Veditor = new PreviewEditor();
        Veditor->videoFile(InputPath);
     if (ui->PreviewEditorButton->text() == "Open PreviewEditor") {
        ui->gridLayout_main->addWidget(Veditor,0,6,0,2);
        Veditor->show();
        //quint16 GuiWidth = ui->centralwidget->width() + Veditor->width();
        ui->centralwidget->setMinimumSize(1280,0);
        this->adjustSize();
        ui->PreviewEditorButton->setText("Close PreviewEditor");
    }
    else {
        //ui->gridLayout_main->removeWidget(Veditor);
        ui->gridLayout_main->removeWidget(Veditor);
        delete Veditor;
        ui->centralwidget->setMinimumSize(0,0);
        this->adjustSize();
        ui->PreviewEditorButton->setText("Open PreviewEditor");
     }

}


void MainForm::on_Vopenavs_clicked()
{
    InputPath = QFileDialog::getOpenFileName(this,tr("Open video file"));
    QFile f(InputPath);
    QString str = f.fileName();
    QStringList parts = str.split("/");
    FileName = parts.at(parts.size()-1);

    ui->VinputText->setText(FileName);
    ui->PreviewEditorButton->setEnabled(true);

}

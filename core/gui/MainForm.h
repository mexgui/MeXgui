#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QtGui>
//#include <Phonon>
#include <QString>
#include <QMimeData>
#include "previeweditor.h"
#include "globals.h"

namespace Ui {

       class MainForm;

}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();


private slots:

    void on_PreviewEditorButton_clicked();

    void on_Vopenavs_clicked();


    void on_actionAbout_triggered();

    void on_actionAudio_triggered();

    void on_actionVideo_triggered();

private:
    //QString InputPath;
   Ui::MainForm *ui;
   bool PreviewWindow = false;
   PreviewEditor * PreEditor;

protected:
    virtual void changeEvent(QEvent *e);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragDrop(QDropEvent *e);

};

#endif // MAINFORM_H

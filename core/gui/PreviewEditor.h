#ifndef PREVIEWEDITOR_H
#define PREVIEWEDITOR_H

#include <QWidget>
#include <QString>
#include "VideoPlayer.h"
#include "Editor.h"
#include <QThread>
#include <QMutex>

//using namespace MeXgui::core::details;
//using namespace MeXgui::core::gui;
//using namespace MeXgui::core::plugins::interfaces;
//using namespace MeXgui::core::util;

namespace Ui {
       class PreviewEditor;
}

class PreviewEditor : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewEditor(QWidget *parent = 0);
    ~PreviewEditor();
    void videoFile(QString filepath);

private:
    QString MediaPath;
    VideoPlayer * videoWidget;
    Editor * textEditor;
    Ui::PreviewEditor *ui;
    QMutex *mutex;

protected:
    void changeEvent(QEvent *e);

public slots:

private slots:
    void on_tabWidget_tabBarDoubleClicked(int index);
    void PreviewDialogClosed();

};


#endif // PREVIEWEDITOR_H

#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QDropEvent>
#include <QKeyEvent>
#include <QMimeData>
#include "editor/findreplace.h"


namespace Ui {
class Editor;
}

class Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);
    ~Editor();
protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void dragDrop(QDropEvent *e);

private slots:
    void on_actionUpdate_triggered();

    void on_actionUndo_triggered();

    void on_actionSave_triggered();

    void on_actionSearch_triggered();

    void on_actionReplace_triggered();

    void on_actionRedo_triggered();

    int on_actionSave_As_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_textEdit_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Editor *ui;
    FindReplace *find;
    FindReplace *findReplace;

    void loadFile(const QString &filename);
    void initTextEditor();
protected:
    void changeEvent(QEvent *e);

};

#endif // EDITOR_H

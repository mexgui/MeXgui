#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <Phonon>
#include <QString>



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

private:
    Ui::MainForm *ui;
    QString FileName;
    QString InputPath;
};

#endif // MAINFORM_H

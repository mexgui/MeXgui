#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void CenterToScreen();
signals:
    void closed();
public slots:
    virtual void closeEvent(QCloseEvent *e);

};

#endif // DIALOG_H

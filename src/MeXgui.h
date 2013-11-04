#ifndef MEXGUI_H
#define MEXGUI_H
 
#include "ui_main.h"
 
 
class MeXgui : public QWidget, private Ui::MeXguiDLG
{
    Q_OBJECT
 
public:
    MeXgui(QWidget *parent = 0);
 
 
public slots:
    void getPath();
    void doSomething();
    void clear();
    void about();
};
 
 
#endif
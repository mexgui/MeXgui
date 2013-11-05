#ifndef MEXGUI_H
#define MEXGUI_H
 
#include "ui_mexgui.h"
 
 
class mexgui : public QWidget, private Ui::mexguiDLG
{
    Q_OBJECT
 
public:
    mexgui(QWidget *parent = 0);
 
 
public slots:
    void getPath();
    void doSomething();
    void clear();
    void about();
};
 
 
#endif

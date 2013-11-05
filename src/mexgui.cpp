#include <QtGui>
#include "mexgui.h"
 
// if we include <QtGui> there is no need to include every class used: <QString>, <QFileDialog>,...
 
mexgui::mexgui(QWidget *parent)
{
    setupUi(this); // this sets up GUI
 
    // signals/slots mechanism in action
    connect( Vopenavs, SIGNAL( clicked() ), this, SLOT( getPath() ) );
    connect( pushButton_do, SIGNAL( clicked() ), this, SLOT( doSomething() ) );
    connect( pushButton_clear, SIGNAL( clicked() ), this, SLOT( clear() ) );
    connect( pushButton_about, SIGNAL( clicked() ), this, SLOT( about() ) );
}
 
 

 
 
void mexgui::about()
{
    QMessageBox::about(this,"About MeXgui",
                "MeXgui - Cross enviroment Megui port.\n"
                "Number 1 is: " + QString::number(spinBox1->value()) + "\n\n"
                "Bye.\n");
}

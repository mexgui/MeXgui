#include <QApplication>
 
#include "mexgui.h"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mexgui *dialog = new mexgui;
 
    dialog->show();
    return app.exec();
}

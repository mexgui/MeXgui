#include "Dialog.h"
#include <QDesktopWidget>
#include <QApplication>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
}

Dialog::~Dialog(){}

/*
** Here we override basic closeEvent handler and emit signal to add possibility
** to handle some codein parent class.
*/
void Dialog::closeEvent(QCloseEvent *e)
{
 if (e) emit closed();
}

void Dialog::CenterToScreen() {
  QDesktopWidget* m = QApplication::desktop();
  QRect desk_rect = m->screenGeometry(m->screenNumber(QCursor::pos()));
  int desk_x = desk_rect.width();
  int desk_y = desk_rect.height();
  int x = this->width();
  int y = this->height();
  this->move(desk_x / 2 - x / 2 + desk_rect.left(), desk_y / 2 - y / 2 + desk_rect.top());
}

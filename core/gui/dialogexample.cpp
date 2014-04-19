#include "dialogexample.h"
#include "ui_dialogexample.h"

DialogExample::DialogExample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExample)
{
    ui->setupUi(this);
}

DialogExample::~DialogExample()
{
    delete ui;
}

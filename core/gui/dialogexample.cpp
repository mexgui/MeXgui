#include "dialogexample.h"
#include "ui_dialogexample.h"

Dialogexample::Dialogexample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogexample)
{
    ui->setupUi(this);
}

Dialogexample::~Dialogexample()
{
    delete ui;
}

#include "Encoder.h"
#include "ui_Encoder.h"

Encoder::Encoder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Encoder)
{
    ui->setupUi(this);
}

Encoder::~Encoder()
{
    delete ui;
}

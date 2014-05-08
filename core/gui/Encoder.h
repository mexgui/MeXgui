#ifndef ENCODER_H
#define ENCODER_H

#include <QWidget>

namespace Ui {
class Encoder;
}

class Encoder : public QWidget
{
    Q_OBJECT

public:
    explicit Encoder(QWidget *parent = 0);
    ~Encoder();

private:
    Ui::Encoder *ui;
};

#endif // ENCODER_H

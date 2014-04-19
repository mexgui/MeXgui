#ifndef DIALOGEXAMPLE_H
#define DIALOGEXAMPLE_H

#include <QDialog>

namespace Myapp {
    namespace core {
        namespace gui {
            class DialogExample;
        }
    }
}

class DialogExample : public QDialog
{
    Q_OBJECT

public:
    explicit DialogExample(QWidget *parent = 0);
    ~DialogExample();

private:
    DialogExample::DialogExample *ui;
};

#endif // DIALOGEXAMPLE_H

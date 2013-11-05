#include <QtGui>
#include "mexgui.h"

void mexgui::Vopenavs()
{
    QString path;

    path = QFileDialog::getOpenFileName(
        this,
        "Choose a AVS file to open",
        "/home",
        tr("AVS Files (*.avs)"));

    //TODO: AVS handling and Windows/Unix code

    lineEdit->setVavsText( path );
}

void mexgui::Vpath()
{
    QString path;

    path = QFileDialog::getOpenFileName(
        this,
        "Choose a file name",
        "/home",
        "");

    lineEdit->setVoutputText( path );
}

void mexgui::doSomething()
{
    int value1, value2;
    Qt::CheckState state;
    QString str;

    textEdit->append( "Path to file: " + lineEdit->text() );

    value1 = spinBox1->value();
    value2 = spinBox2->value();

    textEdit->append( "Number 1 value: " + QString::number(value1) );
    textEdit->append( "Number 2 value: " + QString::number(value2) );

    state = checkBox->checkState();

    str = "Checkbox says: ";
    if ( state == Qt::Checked ) str += "yes";
    else str += "no";
    textEdit->append( str );

    textEdit->append( "ComboBox current text: " + comboBox->currentText() );
    textEdit->append( "ComboBox current item: " + QString::number(comboBox->currentIndex()) );
}


void mexgui::Clear()
{
    textEdit->clear();
}

/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */
#include "findreplacedialog.h"


FindReplaceDialog::FindReplaceDialog(QWidget *parent) {

}

FindReplaceDialog::~FindReplaceDialog()
{
    delete ui;
}



void FindReplaceDialog::setTextEdit(QsciScintilla *textEdit) {
    setTextEdit(textEdit);
}

void FindReplaceDialog::writeSettings(QSettings &settings, const QString &prefix) {
    this->writeSettings(settings, prefix);
}

void FindReplaceDialog::readSettings(QSettings &settings, const QString &prefix) {
    this->readSettings(settings, prefix);
}

void FindReplaceDialog::findNext() {
    this->findReplace->findNext();
}

void FindReplaceDialog::findPrev() {
    this->findPrev();
}

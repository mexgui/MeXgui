/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#include "finddialog.h"


FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent)
{
    hideReplaceWidgets();
    setWindowTitle(tr("Find"));
}

FindDialog::~FindDialog()
{
}

void FindDialog::writeSettings(QSettings &settings, const QString &prefix) {
    this->writeSettings(settings, prefix);
}

void FindDialog::readSettings(QSettings &settings, const QString &prefix) {
    this->readSettings(settings, prefix);
}

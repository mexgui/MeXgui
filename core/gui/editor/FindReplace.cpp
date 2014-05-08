/*
 * Copyright (C) 2014  Jeremi Roivas <jeremi.roivas@gmail.com>
 * See COPYING file that comes with this distribution
 */

#include "FindReplace.h"
#include "ui_findreplace.h"

#include <QDialog>
#include <QRegExp>
#include <QSettings>
#include <QDebug>



#define TEXT_TO_FIND "textToFind"
#define TEXT_TO_REPLACE "textToReplace"
#define DOWN_RADIO "downRadio"
#define UP_RADIO "upRadio"
#define CASE_CHECK "caseCheck"
#define WHOLE_CHECK "wholeCheck"
#define REGEXP_CHECK "regexpCheck"

FindReplace::FindReplace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindReplace), textEdit(0)
{
    ui->setupUi(this);
    ui->errorLabel->setText("");

    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(textToFindChanged()));
    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(validateRegExp(QString)));

    connect(ui->regexCheckBox, SIGNAL(toggled(bool)), this, SLOT(regexpSelected(bool)));

    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(find()));
    connect(ui->closeButton, SIGNAL(clicked()), parent, SLOT(close()));

    connect(ui->replaceButton, SIGNAL(clicked()), this, SLOT(replace()));
    connect(ui->replaceAllButton, SIGNAL(clicked()), this, SLOT(replaceAll()));
}

FindReplace::~FindReplace()
{
    delete ui;
}

void FindReplace::hideReplaceWidgets() {
    if (finddialog == true) {
        ui->replaceLabel->setVisible(false);
        ui->textToReplace->setVisible(false);
        ui->replaceButton->setVisible(false);
        ui->replaceAllButton->setVisible(false);
    }
    else {
        ui->replaceLabel->setVisible(true);
        ui->textToReplace->setVisible(true);
        ui->replaceButton->setVisible(true);
        ui->replaceAllButton->setVisible(true);
    }
}

void FindReplace::setTextEdit(QsciScintilla *textEdit_) {
    textEdit = textEdit_;
    connect(textEdit, SIGNAL(copyAvailable(bool)), ui->replaceButton, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)), ui->replaceAllButton, SLOT(setEnabled(bool)));
}

void FindReplace::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FindReplace::textToFindChanged() {
    ui->findButton->setEnabled(ui->textToFind->text().size() > 0);
}

void FindReplace::regexpSelected(bool sel) {
    if (sel)
        validateRegExp(ui->textToFind->text());
    else
        validateRegExp("");
}

void FindReplace::validateRegExp(const QString &text) {
    if (!ui->regexCheckBox->isChecked() || text.size() == 0) {
        ui->errorLabel->setText("");
        return; // nothing to validate
    }

    QRegExp reg(text,
                (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));

    if (reg.isValid()) {
        showError("");
    } else {
        showError(reg.errorString());
    }
}

void FindReplace::showError(const QString &error) {
    if (error == "") {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600; color:#ff0000;\">" +
                                error +
                                "</spam>");
    }
}

void FindReplace::showMessage(const QString &message) {
    if (message == "") {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600; color:green;\">" +
                                message +
                                "</spam>");
    }
}

void FindReplace::find() {
    find(ui->downRadioButton->isChecked());
}

void FindReplace::find(bool next) {
    if (!textEdit)
        return; // TODO: show some warning?

    //bool result = false;
    QString message;
    // Init search variables
    const QString &toSearch = ui->textToFind->text();
    bool re = false;
    bool wo = false;
    bool cs = false;
    bool wrap = true;
    bool forward = next;
    int line = 0;
    int index = 0;
    bool show = true;
    bool posix = false;

    if (!forward) {
        line = textEdit->lines();
        index = textEdit->lineLength(line);
    }
    if (ui->caseCheckBox->isChecked())
        cs = true;
    if (ui->wholeCheckBox->isChecked())
        wo = true;
    if (ui->selectionCheckBox->isChecked()) {
        line = -1;
        index = -1;
    }


    if (ui->regexCheckBox->isChecked()) {
        QRegExp reg(toSearch,
                    (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));

        message = "searching for regexp: " + reg.pattern();
        re = true;
        }
    else message = "searching for: " + toSearch;

    qDebug() << message;

    if (ui->selectionCheckBox->isChecked()) {
        result = textEdit->findFirstInSelection(toSearch, re, wo, cs, wrap, forward, line, index, show, posix);
    }
    else {
        result = textEdit->findFirst(toSearch, re, wo, cs, wrap, forward, line, index, show, posix);
    }

    if (result) {
        showError("");
    } else {
        showError(tr("no match found"));
        // move to the beginning of the document for the next find
        textEdit->setCursorPosition(0,0);
    }
}

void FindReplace::replace() {
    if (!textEdit->hasSelectedText()) {
        find();
    } else {
        textEdit->replace(ui->textToReplace->text());
        find();
    }
}

void FindReplace::replaceAll() {
    int i=0;
    while (textEdit->hasSelectedText()){
        textEdit->replace(ui->textToReplace->text());
        find();
        i++;
    }
    showMessage(tr("Replaced %1 occurrence(s)").arg(i));
}

void FindReplace::writeSettings(QSettings &settings, const QString &prefix) {
    settings.beginGroup(prefix);
    settings.setValue(TEXT_TO_FIND, ui->textToFind->text());
    settings.setValue(TEXT_TO_REPLACE, ui->textToReplace->text());
    settings.setValue(DOWN_RADIO, ui->downRadioButton->isChecked());
    settings.setValue(UP_RADIO, ui->upRadioButton->isChecked());
    settings.setValue(CASE_CHECK, ui->caseCheckBox->isChecked());
    settings.setValue(WHOLE_CHECK, ui->wholeCheckBox->isChecked());
    settings.setValue(REGEXP_CHECK, ui->regexCheckBox->isChecked());
    settings.endGroup();
}

void FindReplace::readSettings(QSettings &settings, const QString &prefix) {
    settings.beginGroup(prefix);
    ui->textToFind->setText(settings.value(TEXT_TO_FIND, "").toString());
    ui->textToReplace->setText(settings.value(TEXT_TO_REPLACE, "").toString());
    ui->downRadioButton->setChecked(settings.value(DOWN_RADIO, true).toBool());
    ui->upRadioButton->setChecked(settings.value(UP_RADIO, false).toBool());
    ui->caseCheckBox->setChecked(settings.value(CASE_CHECK, false).toBool());
    ui->wholeCheckBox->setChecked(settings.value(WHOLE_CHECK, false).toBool());
    ui->regexCheckBox->setChecked(settings.value(REGEXP_CHECK, false).toBool());
    settings.endGroup();
}

void FindReplace::mode(bool find)
{
    if (find == true) {
        finddialog = true;
        hideReplaceWidgets();
    }
    else {
        finddialog = false;
        hideReplaceWidgets();
    }
}

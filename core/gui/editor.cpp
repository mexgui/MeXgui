#include "editor.h"
#include "ui_editor.h"
#include "globals.h"
#include <QFile>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexeravs.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QMenu>

using namespace globals;

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);

    initTextEditor();

    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->textEdit, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(showContextMenu(const QPoint&)));

    findReplace = new FindReplace(this);
    findReplace->setTextEdit(ui->textEdit);

    ui->textEdit->setEnabled(false);
    loadFile(InputPath);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::changeEvent(QEvent *e)
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


void Editor::on_actionUpdate_triggered()
{

}

void Editor::on_actionSave_triggered()
{
    QString input = InputPath;
    QFile file(input);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, ("MeXgui"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(InputFileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->text();
    QApplication::restoreOverrideCursor();
    file.flush();
    file.close();
    //ui->setCurrentFile(InputFileName);
    //ui->statusBar()->showMessage(tr("File saved"), 2000);

}

int Editor::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return 1;
    InputPath = fileName;
    on_actionSave_triggered();
    return 0;
}

void Editor::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Editor::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Editor::on_actionSearch_triggered()
{
    findReplace->mode(true);
    findReplace->show();
}

void Editor::on_actionReplace_triggered()
{
    findReplace->mode(false);
    findReplace->show();
}

void Editor::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Editor::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Editor::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Editor::keyPressEvent(QKeyEvent *e) {
    if(e->type() == QKeyEvent::KeyPress) {
        if(e->matches(QKeySequence::Copy)) {
            ui->textEdit->copy();
        }
        if(e->matches(QKeySequence::Cut)) {
            ui->textEdit->cut();
        }
        if(e->matches(QKeySequence::Paste)) {
            ui->textEdit->paste();
        }
    }
}
void Editor::dragDrop(QDropEvent *e)
{
    QString path = e->mimeData()->text().remove("file:///");
    QFile file(path);
    QStringList parts = file.fileName().split(".");
    QString ext = parts.at(parts.size()-1);
    InputFileName = file.fileName();
    InputPath = path;
    InputExtension = ext;
    ui->textEdit->setText(file.readAll());
    file.close();
}


void Editor::on_textEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu* menu = new QMenu(this);
    menu->addAction(ui->actionUndo);
    menu->addAction(ui->actionRedo);
    menu->addAction(ui->actionCut);
    menu->addAction(ui->actionCopy);
    menu->addAction(ui->actionPaste);

    if (ui->textEdit->wordAtPoint(pos) == "") {

    }
    menu->popup(ui->textEdit->mapToGlobal(pos));
}

void Editor::loadFile(const QString &fileName)
{
    if (InputExtension == "avs") {

        QFile file(fileName);
        if (!file.open(QFile::ReadOnly)) {
            QMessageBox::warning(this, tr("MeXgui"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
            return;
        }

        QTextStream in(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui->textEdit->setEnabled(true);
        ui->textEdit->setText(in.readAll());
        file.close();
        QApplication::restoreOverrideCursor();
    }
    else ui->textEdit->setEnabled(false);
    //statusBar()->showMessage(tr("File loaded"), 2000);
}

void Editor::initTextEditor()
{
    // Define Caret lines settings
    ui->textEdit->setCaretLineVisible(true);
    ui->textEdit->setCaretLineBackgroundColor(QColor("gainsboro"));

    // Define indetation settings
    ui->textEdit->setAutoIndent(true);
    ui->textEdit->setIndentationGuides(false);
    ui->textEdit->setIndentationsUseTabs(true);
    ui->textEdit->setIndentationWidth(4);
    ui->textEdit->backspaceUnindents();

    // Define margin settings
    ui->textEdit->setMarginsBackgroundColor(QColor("gainsboro"));
    ui->textEdit->setMarginLineNumbers(1, true);
    ui->textEdit->setMarginWidth(1, 50);

    // Define autocompletion settings
    ui->textEdit->setAutoCompletionSource(QsciScintilla::AcsAll);
    ui->textEdit->setAutoCompletionCaseSensitivity(true);
    ui->textEdit->setAutoCompletionReplaceWord(true);
    ui->textEdit->setAutoCompletionUseSingle(QsciScintilla::AcusAlways);
    ui->textEdit->setAutoCompletionThreshold(0);

    // Define Bracing settings
    ui->textEdit->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    ui->textEdit->setMatchedBraceBackgroundColor(Qt::yellow);
    ui->textEdit->setUnmatchedBraceForegroundColor(Qt::blue);

     //Define Avisynth lexer for the module
    QsciLexerAVS * avs = new QsciLexerAVS;
    ui->textEdit->setLexer(avs);
    ui->textEdit->clear();

    // Define paper and font colors
    ui->textEdit->setPaper(Qt::white);
    ui->textEdit->setColor(Qt::black);

}

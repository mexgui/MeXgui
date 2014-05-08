/*
 * Copyright (C) 2014  Jeremi Roivas <jeremi.roivas@gmail.com>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDREPLACE_H
#define FINDREPLACE_H

#include <QDialog>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscidocument.h>
#include <Qsci/qscicommand.h>

namespace Ui {
    class FindReplace;
}

class QSettings;

/*
  * The form for the find/replace dialog.  The form presents the typical
  * widgets you find in standard find/replace dialogs, and it acts on a QsciScintilla.
  *
  * \image html Screenshot-FindReplace.png
  *
  * You need to set the QsciScintilla explicitly, using the method setTextEdit(QsciScintilla *textEdit).
  *
  * For instance
  * \code
  * findReplaceDialog = new FindReplace(this);
  * findReplaceDialog->setTextEdit(ui->textEdit);
  * \endcode
  *
  * There is mode() function available to modify the FindReplace dialog into Find dialog.
  * The true makes it to FindDialog and False is default and is FindReplaceDialog
  *
  * For example
  * \code
  * FindReplaceDialog->mode(true)
  * /endcode
  *
  * This changes the dialog appearance on the fly even if you have the dialog open already.
  *
  * The find functionalities is available even if the find dialog is not shown: if something
  * to search for was already specified, the application can call the methods findNext() and
  * findPrev() (e.g., by connecting them to menu items).
  *
  * In case a regular expression is used as the search term, the form also checks whether the
  * expression is a valid regular expression (You may want to take a look at the syntax of regular expressions:
  * http://doc.trolltech.com/qregexp.html).
  *
  * The form provides also functionalities to save and restore its state using a QSettings object (i.e.,
  * the last word searched for, the options of the form, etc.) via the methods writeSettings()
  * and readSettings().
  *
  * You can take a look at the \ref examples page.
  */
class FindReplace : public QDialog {
    Q_OBJECT
public:
    explicit FindReplace(QWidget *parent = 0);
    virtual ~FindReplace();

    /*
      * Associates the text editor where to perform the search
      * @param textEdit_
      */
    void setTextEdit(QsciScintilla *textEdit_);

    // hides replace widgets from the form
    void hideReplaceWidgets();

    /*
      * Writes the state of the form to the passed settings.
      * @param settings
      * @param prefix the prefix to insert in the settings
      */
    virtual void writeSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

    /*
      * Reads the state of the form from the passed settings.
      * @param settings
      * @param prefix the prefix to look for in the settings
      */
    virtual void readSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

    void mode(bool find = false);

public slots:

    /*
     * performs the find task
     * @param down whether to find the next or the previous
     * occurrence
     */
    void find(bool down);

    /*
     * Finds the next occurrence
     */
    void find();

    /*
     * Finds the next occurrence
     */
    void findNext() { find(true); }

    /*
     * Finds the previous occurrence
     */
    void findPrev() { find(false); }

    /*
      * Replaces the found occurrences and goes to the next occurrence
      */
    void replace();

    /*
      * Replaces all the found occurrences
      */
    void replaceAll();

protected:
    void changeEvent(QEvent *e);

    // shows an error in the dialog
    void showError(const QString &error);

    // shows a message in the dialog
    void showMessage(const QString &message);

protected slots:
    // when the text edit contents changed
    void textToFindChanged();

    // checks whether the passed text is a valid regexp
    void validateRegExp(const QString &text);

    // the regexp checkbox was selected
    void regexpSelected(bool sel);

protected:
    Ui::FindReplace *ui;

    // the text editor (possibly) associated with this form
    QsciScintilla *textEdit;
private:
    bool finddialog = false;
};

#endif // FINDREPLACEFORM_H

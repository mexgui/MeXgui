/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>
#include "findreplace.h"


class QSettings;

/*
  * A find/replace dialog.
  *
  * It relies on a FindReplaceForm object (see that class for the functionalities provided).
  */
class FindReplaceDialog : public FindReplace {
    Q_OBJECT
public:
    FindReplaceDialog(QWidget *parent = 0);
    virtual ~FindReplaceDialog();

    /*
      * Associates the text editor where to perform the search
      * @param textEdit
      */
    void setTextEdit(QsciScintilla *textEdit);


public slots:
    /*
     * Finds the next occurrence
     */
    void findNext();

    /*
     * Finds the previous occurrence
     */
    void findPrev();

protected:
    void changeEvent(QEvent *e);

};

#endif // FINDREPLACEDIALOG_H

#include "sql.h"
#include <QMessageBox>



sql::sql(QObject *parent) :
    QObject(parent)
{
    db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MeXgui.db");
    try {
        if (!db.open()) throw QString("Cannot open database");

    }
    catch (QString thisError) {
        QMessageBox::critical(this,"sql::sql",thisError,QMessageBox::Ok);
        //TODO program close here
    }
}

sql::~sql()
{
    db.close();
    delete this;
}




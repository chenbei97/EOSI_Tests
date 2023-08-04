#ifndef SQLQUERYCONSOLE_H
#define SQLQUERYCONSOLE_H

#include "sqldbquerytree.h"
#include "sqldbquerytable.h"
#include "sqldbquerypanel.h"

class SqlQueryConsole : public QWidget
{
    Q_OBJECT
public:
    explicit SqlQueryConsole(QWidget *parent = nullptr);
    SqlDBQueryTree* tree ;
    SqlDBQueryTable*table;
    SqlDBQueryPanel*panel;
public slots:
    void launchAnalysisDlg();
signals:

};

#endif // SQLQUERYCONSOLE_H

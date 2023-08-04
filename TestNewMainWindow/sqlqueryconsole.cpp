#include "sqlqueryconsole.h"

SqlQueryConsole::SqlQueryConsole(QWidget *parent) : QWidget(parent)
{
    auto tree = new SqlDBQueryTree; // 不要指定this 否则会出问题
    auto table = new SqlDBQueryTable;
    auto panel = new SqlDBQueryPanel;
    tree->setMaximumWidth(300);
    connect(tree,&SqlDBQueryTree::tableShowed,table,&SqlDBQueryTable::showTable); //双击
    connect(tree,&SqlDBQueryTree::schemaShowed,table,&SqlDBQueryTable::showSchema);
    connect(table,&SqlDBQueryTable::queryResult,panel,&SqlDBQueryPanel::showQueryResult);
    connect(table,&SqlDBQueryTable::tableNameFields,panel,&SqlDBQueryPanel::updateCommand); //tableNameFields是showTable发出
    connect(table,&SqlDBQueryTable::tableNameFields,panel,&SqlDBQueryPanel::updateKeywords);
    connect(panel,&SqlDBQueryPanel::queryCommand,table,&SqlDBQueryTable::execQuery);
    connect(panel,&SqlDBQueryPanel::filterField,table,&SqlDBQueryTable::filterTableByField);
    connect(panel,&SqlDBQueryPanel::dateChanged,table,&SqlDBQueryTable::filterTableByTime);
    QHBoxLayout * s = new QHBoxLayout;
    s->addWidget(tree);
    s->addWidget(table);

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addLayout(s);
    lay->addWidget(panel);

    auto act = new QAction(tr("启动分析"));
    connect(act,&QAction::triggered,this,&SqlQueryConsole::launchAnalysisDlg);
    addAction(act);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void SqlQueryConsole::launchAnalysisDlg()
{

}

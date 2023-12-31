﻿#include "mainwindow.h"
#include "sqldbquerytree.h"
#include "sqldbquerytable.h"
#include "sqldbquerypanel.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    auto db = QSqlDatabase::addDatabase("QMYSQL","mysql");
    db.setPort(3306);
    db.setUserName("root");
    db.setHostName("127.0.0.1");
    db.setPassword("199791");
    db.setDatabaseName("dbcontroller");
    db.open();

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
    //QSplitter * s = new QSplitter(Qt::Horizontal);
    QHBoxLayout * s = new QHBoxLayout;
    s->addWidget(tree);
    s->addWidget(table);

//    QSplitter * ss = new QSplitter(Qt::Vertical);
////    ss->setStretchFactor(0,10);
////    ss->setStretchFactor(1,1);
//    ss->addWidget(s);
//    ss->addWidget(panel);

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addLayout(s);
    lay->addWidget(panel);
    resize(1500,1000);
}

MainWindow::~MainWindow()
{
}


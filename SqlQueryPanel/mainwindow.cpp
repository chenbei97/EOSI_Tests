#include "mainwindow.h"
#include "sqldbquerytree.h"
#include "sqldbquerytable.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    connect(tree,&SqlDBQueryTree::tableShowed,table,&SqlDBQueryTable::showTable);
    connect(tree,&SqlDBQueryTree::schemaShowed,table,&SqlDBQueryTable::showSchema);
    QSplitter * s = new QSplitter(Qt::Horizontal);
    s->addWidget(tree);
    s->addWidget(table);
    tree->setMaximumWidth(300);
    setCentralWidget(s);
    resize(1500,1000);
}

MainWindow::~MainWindow()
{
}


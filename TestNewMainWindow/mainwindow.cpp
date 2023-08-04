#include "mainwindow.h"

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

    QMenu * menu1 = new QMenu(tr("文件"));
    QMenu * menu2 = new QMenu(tr("分析"));
    QMenu * menu3 = new QMenu(tr("帮助"));
    QMenu * menu4 = new QMenu(tr("其它"));

//    auto act1 = menu1->addAction(tr("创建实验"));
//    auto act2 = menu2->addAction(tr("查询实验"));
//    auto act3 = menu3->addAction(tr("当前实验"));
    auto act41 = menu4->addAction(tr("版本"));
    auto act42 = menu4->addAction(tr("语言"));
    auto act43 = menu4->addAction(tr("退出"));

    auto menubar = new QMenuBar;
    menubar->addMenu(menu1);
    menubar->addMenu(menu2);
    menubar->addMenu(menu3);
    menubar->addMenu(menu4);
    setMenuBar(menubar);

//    connect(act1,&QAction::triggered,this,&MainWindow::createNewExperments);
//    connect(act2,&QAction::triggered,this,&MainWindow::queryHistoryExperments);
//    connect(act3,&QAction::triggered,this,&MainWindow::viewCurrentExperments);
    connect(act43,&QAction::triggered,this,&MainWindow::close);

    mTab = new QTabWidget(this);
    mQueryPanel = new SqlQueryConsole(this);

    mTab->addTab(new QWidget,tr("创建实验"));
    mTab->addTab(mQueryPanel,tr("查询实验"));
    mTab->addTab(new QWidget,tr("当前实验"));

    setCentralWidget(mTab);
    resize(1000,800);
}

void MainWindow::createNewExperments()
{

}

void MainWindow::queryHistoryExperments()
{

}

void MainWindow::viewCurrentExperments()
{

}

MainWindow::~MainWindow()
{
}


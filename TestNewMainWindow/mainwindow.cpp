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
    auto act41 = menu4->addAction(tr("版本"));
    auto act42 = menu4->addAction(tr("语言"));
    auto act43 = menu4->addAction(tr("退出"));

    auto menubar = new QMenuBar;
    menubar->addMenu(menu1);
    menubar->addMenu(menu2);
    menubar->addMenu(menu3);
    menubar->addMenu(menu4);
    setMenuBar(menubar);

    connect(act43,&QAction::triggered,this,&MainWindow::close);

    mTab = new QTabWidget(this);
    mScanFreConfig = new ScanPlanConfig(this);
    mQueryPanel = new SqlQueryConsole(this);
    //mVesselConfig = new ScanVesselConfig; // 不要this

    www = new GradientHiddenWidget;
    mTab->addTab(mScanFreConfig,tr("创建实验"));
    mTab->addTab(mQueryPanel,tr("查询实验"));
    mTab->addTab(www,tr("当前实验"));

    setCentralWidget(mTab);
    setFont(QFont("Times New Roman",12));
    resize(1000,800);

    connect(mScanFreConfig,&ScanPlanConfig::scanPlanChanged,this,&MainWindow::onScanPlanChanged);
}

void MainWindow::onScanPlanChanged(ScanPlan fre)
{
    mScanPlan = fre;
    auto config = new ScanVesselConfig;
    config->setAttribute(Qt::WA_DeleteOnClose);
    if (fre == ScanPlan::Once)
        config->show();
    else config->show();
}



#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tab = new QTabWidget;
    setCentralWidget(tab);

    auto textedit = new QTextEdit("ahsdbhfsdfn,amsnd");
    auto treeview = new QTreeView;
    auto model = new QStandardItemModel;
    auto scrollarea = new QScrollArea;
    model->setColumnCount(10);
    model->setRowCount(10);
    treeview->setModel(model);

    auto scrollwidget = new QWidget;
    auto box = new QGroupBox;
    auto boxlay = new QVBoxLayout;
    auto w1 = new QTextEdit;
    w1->setMinimumHeight(200);
    auto w2 = new QTextEdit;
    w2->setMinimumHeight(200);
    auto w3 = new QTextEdit;
    w3->setMinimumHeight(200);
    auto w4 = new QTextEdit;
    w4->setMinimumHeight(200);
    auto w5 = new QTextEdit;
    w5->setMinimumHeight(200);
    boxlay->addWidget(w1);
    boxlay->addWidget(w2);
    boxlay->addWidget(w3);
    boxlay->addWidget(w4);
    boxlay->addWidget(w5);
    box->setLayout(boxlay);
    scrollarea->setWidget(box);
    auto scrollay = new QHBoxLayout;
    scrollay->addWidget(box);
    scrollwidget->setLayout(scrollay);


    tab->addTab(new BasicWidgetTab,"Basic");
    tab->addTab(textedit,"Text");
    tab->addTab(treeview,"View");
    tab->addTab(scrollwidget,"Scroll");


    setFixedSize(1200,600);
}

MainWindow::~MainWindow()
{
}


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTableWidget * table = new QTableWidget;
    table->setRowCount(5);
    table->setColumnCount(5);
    for(int i = 0; i <5; ++i)
        table->setColumnWidth(i,100);
    for(int i = 0; i <5; ++i)
        table->setRowHeight(i,100);

    auto delegate = new Table2x2Delegate;

    table->setItemDelegate(delegate);

    // 1. 双击单元格一开始显示文字不显示图片?
    // Table2x2Delegate的代理初始化setItem时设置了文字,但是没设置图片
    // 如果图片也初始化,是可以的
    // 2.
    setCentralWidget(table);
    resize(800,600);
}

MainWindow::~MainWindow()
{
}


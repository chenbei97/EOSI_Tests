#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    btn = new ChannelButton("DAPI");
    setCentralWidget(btn);
}

MainWindow::~MainWindow()
{
}


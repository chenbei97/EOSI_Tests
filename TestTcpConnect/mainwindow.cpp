#include "mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    TcpLoader* instance = &TcpLoader::instance();
    instance->open("127.0.0.1",3000);
    qDebug()<<"instance's addr = "<<instance<<" isOpen? "<< instance->isOpen();

    QPushButton * btn = new QPushButton("查询");
    setCentralWidget(btn);
    connect(btn,&QPushButton::clicked,this,[=]{
        qDebug()<<1;
        TcpQuery query;
        qDebug()<<2;
        while (!query.exec(100)) {
            qDebug()<<query.error();
        }
        qDebug()<<"result = "<<query.result();
    });
}

MainWindow::~MainWindow()
{
}


#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    btn1 = new QPushButton("ok");
    btn2= new Button("yes");
    QSplitter * s = new QSplitter;
    s->addWidget(btn1);
    s->addWidget(btn2);

    setCentralWidget(s);
    resize(800,600);

    QStyleOptionButton option1;
    option1.initFrom(btn1);

    QStyleOptionButton option2;
    option1.initFrom(btn2);

    print(option1);
    qDebug()<<"=========================================";
    print(option2);
}

void MainWindow::print(const QStyleOptionButton& opt)
{
    qDebug()<<"opt.text = "<<opt.text;
    qDebug()<<"opt.icon.name() = "<<opt.icon.name();
    qDebug()<<"opt.iconSize = "<<opt.iconSize;
    qDebug()<<"opt.features = "<<opt.features;

    qDebug()<<"opt.rect = "<<opt.rect;
    qDebug()<<"opt.type = "<<opt.type;
    qDebug()<<"opt.palette = "<<opt.palette;
    qDebug()<<"opt.direction = "<<opt.direction;
    qDebug()<<"opt.version = "<<opt.version;
    qDebug()<<"opt.state = "<<opt.state;
    qDebug()<<"opt.fontMetrics.fontDpi() = "<<opt.fontMetrics.fontDpi();
}

MainWindow::~MainWindow()
{
}



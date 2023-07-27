#include "mainwindow.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    :  QWidget(parent)
{
    GraphicsView * view = new GraphicsView;
    //QGraphicsView * view = new QGraphicsView;

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addWidget(view);
    resize(1000,800);
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *e)
{
//    QGraphicsPathItem * path = new QGraphicsPathItem;
//    QPainterPath  p;
//    p.moveTo(0,0);
//    p.addEllipse(QPoint(0,0),100,100);
//            p.moveTo(0,100);
//    p.lineTo(QPoint(0,-100));
//    p.moveTo(100,0);
//    p.lineTo(-100,0);
//    path->setPath(p);
    QPainter painter(this);
    painter.drawRect(200,200,400,400);
}


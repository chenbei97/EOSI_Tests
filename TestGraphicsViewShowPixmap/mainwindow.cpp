#include "mainwindow.h"
#include "QGraphicsView"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene;
    auto pix = scene->addPixmap(QPixmap());
    auto rec = scene->addEllipse(QRect(50,50,100,100));
    rec->setFlag(QGraphicsItem::ItemIsMovable);
    rec->setZValue(100);
    view = new QGraphicsView;
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setScene(scene);


    //pix->setRotation(30);
    pix->setActive(true);
    //pix->setScale(2);
    pix->setFlag(QGraphicsItem::ItemIsMovable);

    auto pix_ = QPixmap("bin/images/textedit_background.png");
    pix_ = pix_.scaled(size());
    pix->setPixmap(pix_);


    setCentralWidget(view);
    resize(1000,800);
    view->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    view->centerOn(0,0);
    //view->ensureVisible(rect(),0,0);
    view->setSceneRect(50,50,1000,800);
    qDebug()<<size()<<view->size();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    auto pixel = event->angleDelta();
    if (pixel.y() >0) {
        view->scale(1.01,1.01);
    } else view->scale(0.99,0.99);
    //view->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
}

MainWindow::~MainWindow()
{
}


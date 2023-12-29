#include "mainwindow.h"
#include "QGraphicsView"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    pix = scene->addPixmap(QPixmap());
    auto rec = scene->addEllipse(QRect(100,100,200,200));
    qDebug()<<rec->pos()<<rec->scenePos();//(0,0)
    rec->setPos(300,300);
    rec->setFlag(QGraphicsItem::ItemIsMovable);
    rec->setZValue(100);
qDebug()<<rec->mapFromScene(0,0)<<rec->boundingRect()<<rec->pos()<<rec->scenePos();
// QPointF(-300,-300) QRectF(99.5,99.5 201x201) QPointF(300,300)

    view = new QGraphicsView;
    view->setViewport(new QGLWidget);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setScene(scene);

    auto item = scene->addRect(QRect(400,100,50,50),QPen(),Qt::red);
    item->setPos(100,200);
    qDebug()<<item->rect();//QRectF(400,100 50x50)
    qDebug()<<item->pos()<<item->mapFromParent(0,0)<<item->scenePos(); //QPointF(100,200) QPointF(-100,-200) QPointF(100,200)
    scene->setSceneRect(rect());
   // pix->setPos(-100,-100);
   // pix->setPos();
qDebug()<<scene->sceneRect()<<pix->boundingRect();
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
    //view->setSceneRect(50,50,1000,800);
    qDebug()<<size()<<view->size();

    QGraphicsRectItem * item1 = new QGraphicsRectItem(30,30,40,40);
    item1->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    scene->addItem(item1);
    item1->setPos(100,100);

    QGraphicsRectItem * item2 = new QGraphicsRectItem(30,30,40,40);
    item2->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    scene->addItem(item2);
    item2->setPos(120,120);
    qDebug()<<"888888888";
    qDebug()<<item1->mapFromItem(item2,QPointF(20,20)); // QPointF(40,40)
    qDebug()<<item1->mapToItem(item2,QPointF(10,10)); // QPointF(40,40)
    qDebug()<<item1->mapFromItem(item2,QRect(-10,-10,20,20));
    qDebug()<<item1->mapRectFromItem(item2,QRect(-10,-10,20,20)); //QRectF(10,10 20x20)
    qDebug()<<item1->mapFromScene(0,0);//QPointF(-100,-100)
    qDebug()<<item1->mapToScene(0,0);//QPointF(100,100)

    QGraphicsRectItem * item3= new QGraphicsRectItem(30,30,40,40);
    item3->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    scene->addItem(item3);
    item3->setPos(item1->pos()+item1->mapFromItem(item2,QPointF(-15,-15)));

//    auto item11 = new QGraphicsRectItem(30,30,40,40);
//     scene->addItem(item11);
//     item11->setPos(200,200);
//     auto item12 = new QGraphicsRectItem(30,30,40,40);
//      scene->addItem(item12);
//      item12->setPos(220,220);

//     item12->setParentItem(item11);
//     qDebug()<<item12->mapFromParent(QPointF(10,10));

}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    auto pixel = event->angleDelta();
    if (pixel.y() >0) {
        view->scale(1.01,1.01);
    } else view->scale(0.99,0.99);
    //view->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    scene->setSceneRect(rect());
//    auto p = pix->pixmap();
//    p = p.scaled(event->size(),Qt::KeepAspectRatio);
//    pix->setPixmap(p);
//    event->accept();
}

MainWindow::~MainWindow()
{
}


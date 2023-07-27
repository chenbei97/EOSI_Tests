#include "graphicsview.h"
#include <QDebug>

GraphicsView::GraphicsView(QWidget*parent):QGraphicsView(parent)
{
    setAlignment(Qt::AlignCenter);

    setScene(new QGraphicsScene(-400,-400,800,800));
    QGraphicsRectItem * rectitem = new QGraphicsRectItem(QRect(-200,-200,40,40));
QGraphicsEllipseItem * ellipse = new QGraphicsEllipseItem(100,100,100,100);
ellipse->setStartAngle(30*16);
ellipse->setSpanAngle(150*16);

QGraphicsLineItem * line = new QGraphicsLineItem(0,0,400,400);

QGraphicsPathItem * path = new QGraphicsPathItem;
QPainterPath  p;
p.moveTo(0,0);
p.addEllipse(QPoint(0,0),100,100);
        p.moveTo(0,100);
p.lineTo(QPoint(0,-100));
p.moveTo(100,0);
p.lineTo(-100,0);
path->setPath(p);

    scene()->addItem(rectitem);
    scene()->addItem(ellipse);
        scene()->addItem(line);
                scene()->addItem(path);

                path->setFlags(QGraphicsItem::ItemIsMovable);

                path->setPos(300,300);
                path->setBrush(Qt::green);
                path->setOpacity(0.5);
                path->setZValue(1000);

                auto pen = path->pen();
                pen.setColor(Qt::red);
                pen.setWidth(4);
                path->setPen(pen);


//#include <QGraphicsPathItem>
//#include <QGraphicsTextItem>
//#include <QGraphicsLineItem>
//#include <QGraphicsPixmapItem>

//    qDebug()<<"item scene pos = "<<rectitem->scenePos()// (5,5)是item下的坐标,到场景应该是-80+5,-80+5
//           <<" item' point(5,5) = "<<rectitem->mapToScene(QPoint(6,98   ));
//     qDebug()<<rectitem->pos()<<" "<<rectitem->scenePos()<<" "<<
//               rectitem->mapToScene(QRect(-200,-200,40,40))<<" "<<
//               rectitem->mapToScene(QPointF(-50.,-50));
}

//void GraphicsView::paintEvent(QPaintEvent *e)
//{
////    QGraphicsPathItem * path = new QGraphicsPathItem;
////    QPainterPath  p;
////    p.moveTo(0,0);
////    p.addEllipse(QPoint(0,0),100,100);
////            p.moveTo(0,100);
////    p.lineTo(QPoint(0,-100));
////    p.moveTo(100,0);
////    p.lineTo(-100,0);
////    path->setPath(p);
////    QPainter painter(this);
////    painter.drawRect(200,200,400,400);
//}


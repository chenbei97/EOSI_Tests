#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <QGraphicsPathItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>

#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>

#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>

#include <QGraphicsItemAnimation>

#include <QPaintEvent>
#include <QPainter>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget*parent = 0);
//    void paintEvent(QPaintEvent*e) override;
};

#endif // GRAPHICSVIEW_H

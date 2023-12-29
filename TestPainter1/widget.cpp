#include "widget.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    elasped = 0.0;
     QTimer *timer = new QTimer(this);
     connect(timer,&QTimer::timeout,[=]{
         elasped = (qobject_cast<QTimer*>(sender())->interval() % 1000)/1000.0;
         // 0,0.05 ~ 1.0
     });
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate(width()/2,height()/2);
    painter.save();
    painter.drawEllipse(-50,-50,100,100);
    painter.translate(0,100);
    painter.drawRect(-20,-20,40,40);
    painter.restore();
    painter.drawEllipse(-100,-100,200,200);

    painter.translate(-width()/4,-height()/4);
    for(int i = 0; i < 5; ++i) {
        painter.rotate(72);
        auto y = (i) * 100;
        painter.drawRect(QRect(0,y,50,50));
    }
    //painter.rotate(elasped*1000.0);
    event->accept();
}


#include "pattern2x3.h"

Pattern2x3::Pattern2x3(QWidget *parent) : QWidget(parent),mGap(30)
{
    for(int i = 0; i < 6; ++i)
        mSelectedRects.append(false);

    mZoom = 1.0;
//    resize(400,300);
    //setAttribute(Qt::WA_OpaquePaintEvent);
    //setAttribute(Qt::WA_PaintOnScreen);
//    setAttribute(Qt::WA_AcceptTouchEvents);
}

void Pattern2x3::setGap(int gap)
{
    mGap = gap;
}

int Pattern2x3::gap() const
{
    return mGap;
}

//void Pattern2x3::touchEvent(QTouchEvent *event)
//{
//    qDebug()<<event->touchPoints();
//}
void Pattern2x3::mousePressEvent(QMouseEvent *event)
{
    mIsZoom = false;
    auto pos = event->pos();

    int w = width();
    int h = height();
    int cell_w = (w-2*mGap)/3;
    int cell_h = (h-2*mGap) / 2;

    QPointF c11(mGap,mGap);
    QPointF c12(mGap+cell_w,mGap);
    QPointF c13(mGap+2*cell_w,mGap);
    QPointF c14(w-mGap,mGap);
    QPointF c21(mGap,mGap+cell_h);
    QPointF c22(mGap+cell_w,mGap+cell_h);
    QPointF c23(mGap+2*cell_w,mGap+cell_h);
    QPointF c24(w-mGap,mGap+cell_h);
    QPointF c31(mGap,mGap+2*cell_h);
    QPointF c32(mGap+cell_w,mGap+2*cell_h);
    QPointF c33(mGap+2*cell_w,mGap+2*cell_h);
    QPointF c34(w-mGap,mGap+2*cell_h);

    QRectF c1(c11,c22);
    QRectF c2(c12,c23);
    QRectF c3(c13,c24);
    QRectF c4(c21,c32);
    QRectF c5(c22,c33);
    QRectF c6(c23,c34);

    if (c1.contains(pos))
        mRectIdx = RectIndex::c11;
    if (c2.contains(pos))
        mRectIdx = RectIndex::c12;
    if (c3.contains(pos))
        mRectIdx = RectIndex::c13;
    if (c4.contains(pos))
        mRectIdx = RectIndex::c21;
    if (c5.contains(pos))
        mRectIdx = RectIndex::c22;
    if (c6.contains(pos))
        mRectIdx = RectIndex::c23;
    update();
    event->accept();
}

void Pattern2x3::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) mZoom = 1.1;
    else mZoom = 0.9;
    mIsZoom = true;
    update();
    event->accept();
}

void Pattern2x3::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    auto pen = painter.pen();
    pen.setWidth(2);
    painter.setPen(pen);

    int w = width() ;
    int h = height() ;
    if (mIsZoom)
        mGap = mGap / mZoom;

    QPointF topleft(mGap,mGap);
    QPointF topright(w-mGap,mGap);
    QPointF bottomleft(mGap,h-mGap);
    QPointF bottomright(w-mGap,h-mGap);
    painter.drawRect(QRectF(topleft,bottomright));

    int cell_w = (w-2*mGap)/3;
    int cell_h = (h-2*mGap) / 2;
    QPointF leftcenter(mGap,h/2);
    QPointF rightcenter(w-mGap,h/2);
    QPointF topcenterleft(mGap+cell_w,mGap);
    QPointF topcenterright(mGap+2*cell_w,mGap);
    QPointF bottomcenterleft(mGap+cell_w,h-mGap);
    QPointF bottomcenterright(mGap+2*cell_w,h-mGap);
    painter.drawLine(leftcenter,rightcenter);
    painter.drawLine(topcenterleft,bottomcenterleft);
    painter.drawLine(topcenterright,bottomcenterright);

    int radius = cell_w>=cell_h? cell_h/2: cell_w/2; // 选较小的确保圆在矩形内
    QPointF center11(mGap+cell_w/2,mGap+cell_h/2);
    QPointF center12(mGap+3*cell_w/2,mGap+cell_h/2);
    QPointF center13(mGap+5*cell_w/2,mGap+cell_h/2);
    QPointF center21(mGap+cell_w/2,mGap+3*cell_h/2);
    QPointF center22(mGap+3*cell_w/2,mGap+3*cell_h/2);
    QPointF center23(mGap+5*cell_w/2,mGap+3*cell_h/2);

    QPainterPath path;
    path.moveTo(center11);
    path.addEllipse(center11,radius,radius);
    painter.save();
    painter.drawPath(path);
    painter.translate(cell_w,0); //c1->c2
    painter.drawPath(path);
    painter.translate(cell_w,0);//c2->c3
    painter.drawPath(path);
    painter.restore(); // c1
    painter.translate(0,cell_h); // c4
    painter.drawPath(path);
    painter.save();
    painter.translate(cell_w,0);//c4->c5
    painter.drawPath(path);
    painter.translate(cell_w,0);//c4->c6
    painter.drawPath(path);
    painter.restore();//c4

    // 绘制鼠标选择的高亮
    painter.translate(0,-cell_h); // c1
    path.clear();
    switch (mRectIdx) {
        case c11:
            path.moveTo(center11);
            path.addEllipse(center11,radius,radius);
            painter.fillPath(path,QBrush(Qt::green));
            break;
    case c12:
            path.moveTo(center12);
            path.addEllipse(center12,radius,radius);
            painter.fillPath(path,QBrush(Qt::green));
            break;
    case c13:
            path.moveTo(center13);
            path.addEllipse(center13,radius,radius);
            painter.fillPath(path,QBrush(Qt::green));
            break;
    case c21:
            path.moveTo(center21);
            path.addEllipse(center21,radius,radius);
            painter.fillPath(path,QBrush(Qt::green));
            break;
    case c22:
            path.moveTo(center22);
            path.addEllipse(center22,radius,radius);
            painter.fillPath(path,QBrush(Qt::green));
            break;
    case c23:
            path.moveTo(center23);
            path.addEllipse(center23,radius,radius);
            painter.fillPath(path,QBrush(Qt::green));
            break;
    }

    // 把已被选中的都画出来
    path.clear();
    if (mSelectedRects[0]){
        path.moveTo(center11);
        path.addEllipse(center11,radius,radius);
        painter.fillPath(path,QBrush(Qt::blue));
    }
    if (mSelectedRects[1]){
        path.moveTo(center12);
        path.addEllipse(center12,radius,radius);
        painter.fillPath(path,QBrush(Qt::blue));
    }
    if (mSelectedRects[2]){
        path.moveTo(center13);
        path.addEllipse(center13,radius,radius);
        painter.fillPath(path,QBrush(Qt::blue));
    }
    if (mSelectedRects[3]){
        path.moveTo(center21);
        path.addEllipse(center22,radius,radius);
        painter.fillPath(path,QBrush(Qt::blue));
    }
    if (mSelectedRects[4]){
        path.moveTo(center22);
        path.addEllipse(center22,radius,radius);
        painter.fillPath(path,QBrush(Qt::blue));
    }
    if (mSelectedRects[5]){
        path.moveTo(center23);
        path.addEllipse(center23,radius,radius);
        painter.fillPath(path,QBrush(Qt::blue));
    }


    event->accept();
}

void Pattern2x3::setSelectedRect(RectIndex idx, bool isSelected)
{
    mSelectedRects[idx] = isSelected;
}

bool Pattern2x3::isSelected(RectIndex idx) const
{
    return mSelectedRects[idx];
}

void Pattern2x3::setZoom(double zoom)
{
    mZoom = zoom;
}

double Pattern2x3::zoom() const
{
    return mZoom;
}

/***
 * @Author: chenbei97 chenbei_electric@163.com
 * @Date: 2023-10-18 15:40:45
 * @LastEditors: chenbei97 chenbei_electric@163.com
 * @LastEditTime: 2023-10-18 15:42:19
 * @FilePath: \EOS\interface\src\window\viewpattern_paint.cpp
 * @Copyright (c) 2023 by ${chenbei}, All Rights Reserved.
 */

#include "viewpattern.h"

void ViewPattern::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    auto pen = painter.pen();
    pen.setWidth(2);
    painter.setPen(pen);
//    painter.fillRect(rect(),Qt::white);

    auto diameter = width()>=height()?height():width();
    auto groupcolor = mViewInfo[HoleGroupColorField].toString();
    if (!mViewRects[holeID()].isEmpty()) {

        for(auto viewRect: mViewRects[holeID()]) {
            //LOG<<viewRect.rect<<viewRect.flag;
            if (viewRect.flag)
                painter.fillRect(mapToSize(viewRect.rect,getInnerRectTopLeftPoint(),diameter,diameter),groupcolor);
            else painter.fillRect(mapToSize(viewRect.rect,getInnerRectTopLeftPoint(),diameter,diameter),DefaultNativeColor);
        }
    }

    auto radius = width()>=height()?height()/2.0:width()/2.0;
    auto p11 = getInnerRectTopLeftPoint();
    auto p12 = getInnerRectTopRightPoint();
    auto p21 = getInnerRectBottomLeftPoint();
    auto p22 = getInnerRectBottomRightPoint();

    painter.drawEllipse(QPointF(width()/2.0,height()/2.0),radius,radius);
    painter.drawLine(p11,p21);
    painter.drawLine(p12,p22);
    painter.drawLine(p11,p12);
    painter.drawLine(p21,p22);
    pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(Qt::gray);
    painter.setPen(pen);
    auto hor_offset = getInnerRectWidth();
    for (int i = 1; i <= mSize-1; ++i) {
        auto top = p11 + QPointF(i*hor_offset,0);
        auto bottom = p21 + QPointF(i*hor_offset,0);
        painter.drawLine(top,bottom);
    }
    auto ver_offset = getInnerRectHeight(); // 点之间y坐标相差的是小矩形高度
    for (int i = 1; i <= mSize-1; ++i){
        auto top = p11 + QPointF(0,ver_offset*i);
        auto bottom = p12 + QPointF(0,ver_offset*i);
        painter.drawLine(top,bottom);
    }
    pen = painter.pen();
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    if (!mDrapRectF.isEmpty()) {
        auto pen = painter.pen();
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        painter.drawRect(mapToSize(mDrapRectF,getInnerRectTopLeftPoint(),radius*2,radius*2));
        pen.setColor(Qt::black); // 恢复,否则绘制其他的都变颜色了
        painter.setPen(pen);
    }

    event->accept();
}

void ViewPattern::mousePressEvent(QMouseEvent *event)
{ // 左键点击清除框选,计算鼠标点击的小矩形区域坐标
    mMousePos = event->pos();

    // 1.框选后随机点一下要清除框选
    if (event->button() == Qt::LeftButton) {
        mDrapRectF = QRectF();
        update();
    } else if (event->button() == Qt::RightButton) {
        if (mViewInfo[HoleGroupNameField].toString().isEmpty()) {
            applygroupact->setEnabled(false);
            saveviewact->setEnabled(false);
            removeviewact->setEnabled(false);
        } else {
            applygroupact->setEnabled(true);
            saveviewact->setEnabled(true);
            removeviewact->setEnabled(true);
        }
    }
    //LOG<<this->rect().topLeft()<<mMousePos;
    emit previewEvent(mMousePos);
    update();
    event->accept();

}

void ViewPattern::mouseReleaseEvent(QMouseEvent *event)
{ // 拖拽区域点个数为0才是预览事件(这里不能对applyall,applygroup,remove的使能操作)
//    emit previewEvent(mMousePoint);

    update();
    event->accept();
}

void ViewPattern::mouseMoveEvent(QMouseEvent *event)
{ // 绘制拖拽框
    if (event->buttons() & Qt::LeftButton){
        auto end = event->pos(); // 鼠标停下的点
        auto diameter = width()>=height()?height():width();
        // 鼠标形成的矩形框将其等比例缩放到0-1
        mDrapRectF = mapFromSize(QRectF(mMousePos,end),getInnerRectTopLeftPoint(),diameter,diameter);
    }
    update();
    event->accept();
}

double ViewPattern::getCircleRadius() const
{ // 视野圆半径
    return width()>=height()?height()/2.0:width()/2.0;
}

QPointF ViewPattern::getInnerRectTopLeftPoint() const
{// 外接正方形左上角顶点
    if (width()>=height())
        return QPointF(width()/2.0-getCircleRadius(),0.0);
    else
        return QPointF(0.0,height()/2.0-getCircleRadius()); // 左上角x=0
}

QPointF ViewPattern::getInnerRectTopRightPoint() const
{// 外接正方形右上角顶点
     if (width()>=height())
        return QPointF(width()/2.0+getCircleRadius(),0.0);
     else
         return QPointF(width(),height()/2.0-getCircleRadius());
}

QPointF ViewPattern::getInnerRectBottomLeftPoint() const
{// 外接正方形左下角顶点
     if (width()>=height())
        return QPointF(width()/2.0-getCircleRadius(),height());
     else
         return QPointF(0,height()/2.0+getCircleRadius());
}

QPointF ViewPattern::getInnerRectBottomRightPoint() const
{// 外接正方形右下角顶点
    if (width()>=height())
        return QPointF(width()/2.0+getCircleRadius(),height());
     else
        return QPointF(width(),height()/2.0+getCircleRadius());
}

double ViewPattern::getInnerRectWidth() const
{// 小矩形区域的宽度
    return 2 * getCircleRadius() /  mSize *1.0;
}

double ViewPattern::getInnerRectHeight() const
{// 小矩形区域的高度
    return 2 * getCircleRadius() / mSize *1.0;
}

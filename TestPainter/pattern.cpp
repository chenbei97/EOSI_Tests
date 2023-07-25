#include "pattern.h"

Pattern::Pattern(QWidget *parent) : QWidget(parent),mGap(30),mRow(1),mCol(1)
{
     for(int row = 0 ; row < mRow; ++ row) {
         QVector<bool> var;
         for (int col = 0; col < mCol; ++col)
             var.append(false);
         mSelectedRects.append(var);
    }
    mZoom = 1.0;
}

void Pattern::setGap(int gap)
{
    mGap = gap;
}

int Pattern::gap() const
{
    return mGap;
}

void Pattern::mousePressEvent(QMouseEvent *event)
{
    mIsZoom = false;
    auto pos = event->pos();

    int w = width();
    int h = height();
    int cell_w = (w-2*mGap)/mCol;
    int cell_h = (h-2*mGap) / mRow;

    QList<QVector<QPointF>> points;
    for(int row = 0; row < mRow+1; ++row)
    {
        QVector<QPointF> p;
        for(int col = 0; col < mCol+1; ++col)
            p.append(QPointF(mGap+cell_w*col,mGap+cell_h*row));
        points.append(p);
    }

    QList<QVector<QRectF>> rects;
    for(int row = 0; row < mRow; ++row)
    {
        QVector<QRectF> r;
        for(int col = 0; col < mCol; ++col)
        {
            auto topleft = points[row][col];
            auto bottomright = points[row+1][col+1];
            r.append(QRectF(topleft,bottomright));
        }
        rects.append(r);
    }

    for(int row = 0; row < mRow; ++row)
         for(int col = 0; col < mCol; ++col)
             if (rects[row][col].contains(pos))
                 mPos = {row,col};
    update();
    event->accept();
}

void Pattern::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) mZoom = 1.1;
    else mZoom = 0.9;
    mIsZoom = true;
    update();
    event->accept();
}

void Pattern::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    auto pen = painter.pen();
    pen.setWidth(2);
    painter.setPen(pen);


    int w = width() ;
    int h = height() ;
    if (mIsZoom) {
        mGap = mGap / mZoom;
    }

    QPointF topleft(mGap,mGap);
    QPointF topright(w-mGap,mGap);
    QPointF bottomleft(mGap,h-mGap);
    QPointF bottomright(w-mGap,h-mGap);
    painter.drawRect(QRectF(topleft,bottomright));

    int cell_w = (w-2*mGap)/mCol;
    int cell_h = (h-2*mGap) / mRow;

    QList<QVector<QPointF>> points;
    for(int row = 0; row < mRow+1; ++row)
    {
        QVector<QPointF> p;
        for(int col = 0; col < mCol+1; ++col)
            p.append(QPointF(mGap+cell_w*col,mGap+cell_h*row));
        points.append(p);
    }

    QList<QVector<QPointF>> centerPts;
    for(int row = 0; row < mRow; ++row)
    {
        QVector<QPointF> p;
        for(int col = 0; col < mCol; ++col)
            // 中心位置相对起点左上角多了cell_w和cell_h的一半
            p.append(QPointF(mGap+cell_w/2+cell_w*col,mGap+cell_h/2+cell_h*row));
        centerPts.append(p);
    }

    for(int row = 1; row < mRow+1; ++row)
        painter.drawLine(points[row][0],points[row][mCol]);
    for(int col = 1; col < mCol+1; ++col)
        painter.drawLine(points[0][col],points[mRow][col]);


    int radius = cell_w>=cell_h? cell_h/2: cell_w/2; // 选较小的确保圆在矩形内

    QPainterPath path;
    for(int row = 0 ; row < mRow; ++ row)
    {
        for(int col = 0; col < mCol; ++ col)
        {
            auto center = centerPts[row][col];
            painter.drawEllipse(center,radius,radius);
            if (mPos.x() == row && mPos.y() == col)
            {
                path.clear();
                path.moveTo(center);
                path.addEllipse(center,radius,radius);
                painter.fillPath(path,Qt::green);
            }
            if (mSelectedRects[row][col])
            {
                path.clear();
                path.moveTo(center);
                path.addEllipse(center,radius,radius);
                painter.fillPath(path,Qt::blue);
            }

        }
    }
    event->accept();
}

void Pattern::setSelectedRect(int row,int col, bool isSelected)
{
    if (row <0 || row >= mRow) return ;
    if (col <0 || col >= mCol) return ;

    mSelectedRects[row][col] = isSelected;
}

bool Pattern::isSelected(int row,int col) const
{
    if (row <0 || row >= mRow) return false ;
    if (col <0 || col >= mCol) return false;

    return mSelectedRects[row][col];
}

void Pattern::setZoom(double zoom)
{
    mZoom = zoom;
}

double Pattern::zoom() const
{
    return mZoom;
}

void Pattern::setPatternSize(int rows,int cols)
{
    mRow = rows;
    mCol = cols;
    mSelectedRects.clear();
    for(int row = 0 ; row < mRow; ++ row) {
        QVector<bool> var;
        for (int col = 0; col < mCol; ++col)
            var.append(false);
        mSelectedRects.append(var);
   }
    update();
}

void Pattern::setPatternSize(const QSize& size)
{
    mRow = size.width();
    mCol = size.height();
}

QSize Pattern::patternSize() const
{
    return QSize(mRow,mCol);
}

#include "pattern.h"

Pattern::Pattern(QWidget *parent) : QWidget(parent),mRow(1),mCol(1)
{
    init();
}

Pattern::Pattern(int rows, int cols,QWidget *parent)
    : QWidget(parent),mRow(rows),mCol(cols)
{
  init();
}

Pattern::Pattern(const QSize&size,QWidget *parent)
    : QWidget(parent),mRow(size.width()),mCol(size.height())
{
    init();
}

void Pattern::init()
{
    for(int row = 0 ; row < mRow; ++ row) {
        QVector<bool> var;
        for (int col = 0; col < mCol; ++col)
            var.append(false);
        mSelectedRects.append(var);
   }
   mGap = 30;
   mSpace = 10;
   mZoom = 1.0;
   mIsHighlight = false;
   mMouseEvent = false;
   mWheelEvent = false;
   mState = BlankState;
   mMousePos = {-1,-1};
   mSignedPos = {-1,-1};

   INIT_FONT;
   INIT_MINSIZE(600,400);
}

void Pattern::setSpacing(uint32_t space)
{
    mSpace = (double)space;
}

uint32_t Pattern::spacing() const
{
    return (uint32_t)mSpace;
}

void Pattern::setGap(uint32_t gap)
{
    mGap = (double)gap;
}

uint32_t Pattern::gap() const
{
    return (uint32_t)mGap;
}

void Pattern::mousePressEvent(QMouseEvent *event)
{
    if (mMouseEvent) {
        auto pos = event->pos();
        auto rects = getChildRects();

        for(int row = 0; row < mRow; ++row)
             for(int col = 0; col < mCol; ++col)
                 if (rects[row][col].contains(pos))
                     mMousePos = {row,col};
        //LOG<<"mMousePos = "<<mMousePos;
        update();
    }
    event->accept();
}

QPoint Pattern::currentSelectedPos() const
{
    return mMousePos;
}

QVector<QPoint> Pattern::selectedPoints() const
{
    QVector<QPoint> points;
    for(int row = 0; row < mRow; ++row)
         for(int col = 0; col < mCol; ++col)
             if (mSelectedRects[row][col])
                 points.append(QPoint(row,col));
    return points;
}

void Pattern::wheelEvent(QWheelEvent *event)
{
        if (mWheelEvent) {
            if (event->angleDelta().y() > 0) mGap *= 0.9;
            else mGap *= 1.1;
    //        if (mGap < 1.0) mGap = 10.0;
            update();
        }
        event->accept();
}

void Pattern::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    auto pen = painter.pen();
    pen.setWidth(2);
    painter.setPen(pen);

    //drawBorder(painter);
    drawLine(painter);
    drawHeader(painter);
    drawHighlight(painter);
    drawFlag(painter);

    event->accept();
}

void Pattern::drawHeader(QPainter &painter)
{
    auto pointSize = mRow>10? 8:DefaultFontSize;

    auto font = painter.font();
    font.setPointSize(pointSize);
    font.setFamily(DefaultFontFamily);
    painter.setFont(font);

    auto rowpts = getRowHeaderPoints();
    for(int col = 0 ; col < mCol; ++ col)
    {
        auto center = rowpts[col];
        painter.drawText(center,QString::number(col+1));
    }

    auto colpts = getColHeaderPoints();
    for(int row = 0 ; row < mRow; ++ row)
    {
        auto center = colpts[row];
        painter.drawText(center,QChar(row+65));
    }
}

void Pattern::drawFlag(QPainter&painter)
{
    auto cell_size = getChildSize();
    int cell_w = cell_size.width();
    int cell_h = cell_size.height();
    int radius = cell_w>=cell_h? cell_h/2: cell_w/2;

    auto pen = painter.pen();
    pen.setWidth(4);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    auto  centerPts = getCenterPoints();
    for(int row = 0 ; row < mRow; ++ row)
    {
        for(int col = 0; col < mCol; ++ col)
        {
            if (row == mSignedPos.x() && col == mSignedPos.y())
            {
                auto center = centerPts[row][col];
                auto top = center+QPointF(0,-radius);
                auto bottom = center+QPointF(0,radius);
                auto left = center+QPointF(-radius,0);
                auto right = center+QPointF(radius,0);
                auto topleft = center + QPointF(-radius*cos(RadianRate*45),-radius*cos(RadianRate*45));
                auto topright= center + QPointF(radius*cos(RadianRate*45),-radius*cos(RadianRate*45));
                auto bottomleft = center + QPointF(-radius*cos(RadianRate*45),radius*cos(RadianRate*45));
                auto bottomright = center + QPointF(radius*cos(RadianRate*45),radius*cos(RadianRate*45));

                painter.drawLine(top,bottom);
                painter.drawLine(left,right);
                painter.drawLine(topleft,bottomright);
                painter.drawLine(topright,bottomleft);
                painter.drawEllipse(center,radius,radius);
            }
        }
    }
}

void Pattern::drawHighlight(QPainter&painter)
{
    auto cell_size = getChildSize();
    int cell_w = cell_size.width();
    int cell_h = cell_size.height();

    int radius = cell_w>=cell_h? cell_h/2: cell_w/2; // 选较小的确保圆在矩形内

    auto  centerPts = getCenterPoints();
    QPainterPath path;
    for(int row = 0 ; row < mRow; ++ row)
    {
        for(int col = 0; col < mCol; ++ col)
        {
            auto center = centerPts[row][col];
            path.clear();
            path.addEllipse(center,radius,radius);
            painter.fillPath(path,Qt::darkGray);
            //painter.drawEllipse(center,radius,radius);

            if (mMousePos.x() == row && mMousePos.y() == col) // 鼠标不点击mPos={-1,-1}
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
}

void Pattern::drawLine(QPainter&painter)
{
    auto points = getBorderPoints();
    for(int row = 1; row < mRow; ++row) // 首尾2个边的线不再绘制
        painter.drawLine(points[row][0],
                points[row][mCol]);
    for(int col = 1; col < mCol; ++col)
        painter.drawLine(points[0][col],points[mRow][col]);
}

void Pattern::drawBorder(QPainter &painter)
{
    QPointF topleft(mGap,mGap);
    QPointF bottomright(width()-mGap,height()-mGap);
    painter.drawRect(QRectF(topleft,bottomright));
}

QList<QVector<QRectF>> Pattern::getChildRects() const
{
    auto points = getBorderPoints();

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
    return rects;
}

QSize Pattern::getChildSize() const
{
    int w = width() ;
    int h = height() ;
     // 总宽度-2个到边界的gap-圆之间留出的mSpace,边界sapce留出2个,共(mCol-1+2)个
    int cell_w = (w-2*mGap-mSpace*(mCol+1))/mCol;
    int cell_h = (h-2*mGap-mSpace*(mRow+1)) / mRow;
    return  QSize(cell_w,cell_h);
}

QVector<QPointF> Pattern::getRowHeaderPoints()
{
    auto cell_size = getChildSize();
    int cell_w = cell_size.width();
    QVector<QPointF> points;
    for(int col = 0; col < mCol; ++col)
        points.append(QPointF(mGap+mSpace/2+cell_w/2+(cell_w+mSpace)*col,
                              mGap-mSpace/2));
    return points;
}

QVector<QPointF> Pattern::getColHeaderPoints()
{
    auto cell_size = getChildSize();
    int cell_h = cell_size.height();
    QVector<QPointF> points;
    for(int row = 0; row < mRow; ++row)
        points.append(QPointF(mGap-mSpace,
                              mGap+mSpace+cell_h/2+(cell_h+mSpace)*row));
    return points;
}

QList<QVector<QPointF>> Pattern::getBorderPoints() const
{
    auto cell_size = getChildSize();
    int cell_w = cell_size.width();
    int cell_h = cell_size.height();

    QList<QVector<QPointF>> points;
    for(int row = 0; row < mRow+1; ++row) // 4x6,4行5条边
    {
        QVector<QPointF> p;
        for(int col = 0; col < mCol+1; ++col)
            p.append(QPointF(mGap+mSpace/2+(cell_w+mSpace)*col,
                             mGap+mSpace/2+(cell_h+mSpace)*row));
        points.append(p);
    }

    return points;
}

QList<QVector<QPointF>> Pattern::getCenterPoints() const
{
    auto cell_size = getChildSize();
    int cell_w = cell_size.width();
    int cell_h = cell_size.height();

    QList<QVector<QPointF>> centerPts;
    for(int row = 0; row < mRow; ++row)
    {
        QVector<QPointF> p;
        for(int col = 0; col < mCol; ++col)
            // 中心位置相对起点左上角多了cell_w和cell_h的一半,还多了mSpace
            p.append(QPointF(mGap+cell_w/2+mSpace+(cell_w+mSpace)*col,
                             mGap+cell_h/2+mSpace+(cell_h+mSpace)*row));
        centerPts.append(p);
    }

    return centerPts;
}

void Pattern::setSelectedRect(int row,int col, bool isSelected)
{
    if (!mIsHighlight) return;
    if (row <0 || row >= mRow) return ;
    if (col <0 || col >= mCol) return ;

    mSelectedRects[row][col] = isSelected;
    update();
}

void Pattern::clearSelectedRects()
{
    for(int row = 0 ; row < mRow; ++ row) {
        for (int col = 0; col < mCol; ++col)
            mSelectedRects[row][col]=false;
    }
    update();
}

void Pattern::setSelectedRect(const QPoint&point,bool isSelected)
{
    return setSelectedRect(point.x(),point.y(),isSelected);
}

bool Pattern::isRectSelected(int row,int col) const
{
    if (!mIsHighlight) return false;
    if (row <0 || row >= mRow) return false ;
    if (col <0 || col >= mCol) return false;

    return mSelectedRects[row][col];
}

void Pattern::setSignedRect(int row, int col)
{
    mSignedPos = {row,col};
}

void Pattern::enableZoom()

{
    mWheelEvent = true;
}

void Pattern::disableZoom()
{
    mWheelEvent = false;
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

void Pattern::enableClick()
{
    mMouseEvent = true;
}

void Pattern::disableClick()
{
    mMouseEvent = false;
}

void Pattern::enableHighlight()
{
    mIsHighlight = true;
}

void Pattern::disableHighlight()
{
    mIsHighlight = false;
}

void Pattern::toggleState(PatternState state)
{
    mState = state;
    switch (mState) {
        case BlankState:
            disableClick();
            disableZoom();
            disableHighlight();
            break;
    case TickState:
            enableClick();
            enableZoom();
            enableHighlight();
            break;
    case MoveState:
            disableClick();
            disableZoom();
            enableHighlight();
            break;
    }
}

Pattern::PatternState Pattern::state() const
{
    return mState;
}


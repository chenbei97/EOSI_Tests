#include "pattern.h"
#define SCREEN_2560X1600 0

Pattern::Pattern() :mRow(1),mCol(1)
{
    init();
}

Pattern::Pattern(int rows, int cols):mRow(rows),mCol(cols)
{
  init();
}

Pattern::Pattern(const QSize&size):mRow(size.width()),mCol(size.height())
{
    init();
}

Pattern& Pattern::operator=(const Pattern&pattern)
{
    copy(pattern);
    return *this;
}

Pattern::Pattern(const Pattern&pattern)
{
    copy(pattern);
}

Pattern::Pattern(const Pattern*pattern)
{
    copy(*pattern);
}

void Pattern::copy(const Pattern&pattern)
{
    mRow = pattern.mRow;
    mCol = pattern.mCol;

    mGap = pattern.mGap;
    mSpace = pattern.mSpace;
    mZoom = pattern.mZoom;
    mIsZoom = pattern.mIsZoom;
    mIsDrawRandomPoints = pattern.mIsDrawRandomPoints;
    mDrawPointsCount = pattern.mDrawPointsCount;
    mIsHighlight = pattern.mIsHighlight;
    mMouseEvent = pattern.mMouseEvent;
    mWheelEvent = pattern.mWheelEvent;
    mMousePos = pattern.mMousePos;
    mSignedPos = pattern.mSignedPos;
    mSelectedRects = pattern.mSelectedRects;
    mState = pattern.mState;

    mDefaultColor = pattern.mDefaultColor;
    mSelectedColor = pattern.mSelectedColor;
    mSignedColor = pattern.mSignedColor;
    mCurrentColor = pattern.mCurrentColor;

    //INIT_FONT;
    updateMinSize();
    update();
    //LOG<<"pattern copy constructor is called, rows= "<<mRow<<" cols = "<<mCol;
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
   mIsDrawRandomPoints = false;
   mDrawPointsCount = 0;
   mMouseEvent = false;
   mWheelEvent = false;
   mState = BlankState;
   mMousePos = {-1,-1};
   mSignedPos = {-1,-1};
   int PatternColorAlpha = 100;
   mSelectedColor.setAlpha(PatternColorAlpha);
   mDefaultColor.setAlpha(PatternColorAlpha);
   mCurrentColor.setAlpha(PatternColorAlpha);
   mSignedColor.setAlpha(PatternColorAlpha);

   //INIT_FONT;
   updateMinSize();
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

QPoint Pattern::currentMousePoint() const
{
    return mMousePos;
}

void Pattern::clearMousePoint()
{
    mMousePos = QPoint(-1,-1);
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
    drawSignedPoints(painter);
    drawPoints(painter);

    event->accept();
}

void Pattern::drawHeader(QPainter &painter)
{
    auto pointSize = mRow>10? 8:12;

    auto font = painter.font();
    font.setPointSize(pointSize);
    font.setFamily("Times New Roman");
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

void Pattern::drawSignedPoints(QPainter &painter)
{
    auto cell_size = getChildSize();
    int cell_w = cell_size.width();
    int cell_h = cell_size.height();
    int radius = cell_w>=cell_h? cell_h/2: cell_w/2;
    radius *= 0.75;

    auto pen = painter.pen();
    pen.setWidth(4);
    pen.setColor(mSignedColor);
    painter.setPen(pen);

    static double RadianRate = 3.1415926535/180.0;

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

void Pattern::drawRandomPoints( int count)
{
    mDrawPointsCount= count;
    mIsDrawRandomPoints = true;
    update();
}

void Pattern::drawPoints(QPainter &painter)
{
    if (!mIsDrawRandomPoints) return;

    auto pen = painter.pen();
    pen.setWidth(8);
    pen.setColor("#782DFF");
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    auto cell = getChildSize();
    int radius = cell.width()>=cell.height()? cell.height()/2: cell.width()/2;
    auto centers = getCenterPoints();
    radius *= 0.5;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    for(int row = 0 ; row < mRow; ++ row){
        for(int col = 0; col < mCol; ++ col) {
            if (mSelectedRects[row][col]) {
                for(int i = 0; i< mDrawPointsCount; ++i) {
                    auto center = centers[row][col];
                    painter.drawPoint(QPoint(qrand()%(2*radius)-radius,
                                             qrand()%(2*radius)-radius)+center);
                }
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
        {//默认情况是2个圆
            auto center = centerPts[row][col];
            painter.drawEllipse(center,radius,radius);
            painter.drawEllipse(center,radius*0.75,radius*0.75);

            if (mState != BlankState) // 非默认情况内圆填充灰色
            {
                path.clear();
                path.addEllipse(center,radius*0.75,radius*0.75);
                painter.fillPath(path,mDefaultColor);
            }


            if (mMousePos.x() == row && mMousePos.y() == col) // 鼠标不点击mPos={-1,-1}
            {
                path.clear();
                path.moveTo(center);
                path.addEllipse(center,radius*0.75,radius*0.75);
                painter.fillPath(path,mCurrentColor);
            }

            if (mSelectedRects[row][col])
            {
                path.clear();
                path.moveTo(center);
                path.addEllipse(center,radius*0.75,radius*0.75);
                painter.fillPath(path,mSelectedColor);
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

void Pattern::setSelectedPoint(int row,int col, bool isSelected)
{
    if (!mIsHighlight) return;
    if (row <0 || row >= mRow) return ;
    if (col <0 || col >= mCol) return ;

    mSelectedRects[row][col] = isSelected;
    update();
}

void Pattern::setSelectedPoint(const QPoint&point,bool isSelected)
{
    return setSelectedPoint(point.x(),point.y(),isSelected);
}

void Pattern::setSelectedPoints(bool isSelected)
{
    for(int row = 0 ; row < mRow; ++ row) {
        for (int col = 0; col < mCol; ++col)
            mSelectedRects[row][col]=isSelected;
    }
    update();
}

void Pattern::setSelectedPoints(const QVector<QPoint> &points, bool isSelected)
{
    foreach (auto p ,points) {
        setSelectedPoint(p,isSelected);
    }
}

void Pattern::clearAllPoints()
{
    setSelectedPoints(false);
}

void Pattern::selectAllPoints()
{
    setSelectedPoints(true);
}


bool Pattern::isPointSelected(int row,int col) const
{
    if (!mIsHighlight) return false;
    if (row <0 || row >= mRow) return false ;
    if (col <0 || col >= mCol) return false;

    return mSelectedRects[row][col];
}

int Pattern::selectedPointCount() const
{
    int count = 0;
    foreach (auto vector, mSelectedRects)
        count +=vector.count(true);
    return count;
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

void Pattern::setSignedPoint(int row, int col)
{
    mSignedPos = {row,col};
    update();
}

void Pattern::setSignedPoint(const QPoint& point)
{
    mSignedPos = point;
    update();
}

void Pattern::clearSignedPoint()
{
    mSignedPos = {-1,-1};
    update();
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
    updateMinSize();
    update();
}

void Pattern::setPatternSize(const QSize& size)
{
    setPatternSize(size.width(),size.height());
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
            mSelectedColor = QColor("#A0FEFF");
            mSelectedColor.setAlpha(100);
            break;
    }
}

Pattern::PatternState Pattern::state() const
{
    return mState;
}

void Pattern::setDefaultColor(const QColor&color)
{
    mDefaultColor = color;
}

QColor Pattern::defaultColor() const
{
    return mDefaultColor;
}

void Pattern::setCurrentColor(const QColor&color)
{
    mCurrentColor = color;
}

QColor Pattern::currentColor() const
{
    return mCurrentColor;
}

void Pattern::setSelectedColor(const QColor&color)
{
    mSelectedColor = color;
}

QColor Pattern::selectedColor() const
{
    return mSelectedColor;
}

void Pattern::setSignedColor(const QColor&color)
{
    mSignedColor = color;
}

QColor Pattern::signedColor() const
{
    return mSignedColor;
}

void Pattern::updateMinSize()
{
#ifdef SCREEN_2560X1600
    if (mRow<8)
        setMinimumSize(600,300);
    else if (mRow >8 && mRow < 16)
        setMinimumSize(600,400);
    else
        setMinimumSize(600,520);
#elif defined (SCREEN_1280X800)
    if (mRow<8)
        setMinimumSize(300,150);
    else if (mRow >8 && mRow < 16)
        setMinimumSize(350,250);
    else
        setMinimumSize(400,380);
#else
    if (mRow<8)
        setMinimumSize(400,150);
    else if (mRow >8 && mRow < 16)
        setMinimumSize(450,300);
    else
        setMinimumSize(500,380);
#endif
}



#ifndef PATTERN_H
#define PATTERN_H


#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QTouchEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QWheelEvent>
#include <QTime>
//#include "Constant.h"

class Pattern : public QWidget
{
    Q_OBJECT
public:
    enum PatternState {BlankState,TickState,MoveState};
    explicit Pattern();
    explicit Pattern(int rows, int cols);
    explicit Pattern(const QSize&size);
    explicit Pattern(const Pattern& pattern);
    explicit Pattern(const Pattern* pattern);
    Pattern& operator = (const Pattern&pattern);

    void toggleState(PatternState state);
    PatternState state() const;

    void setPatternSize(int rows,int cols);
    void setPatternSize(const QSize& size);
    QSize patternSize() const;

    void setDefaultColor(const QColor&color);
    QColor defaultColor() const;

    void setCurrentColor(const QColor&color);
    QColor currentColor() const;

    void setSelectedColor(const QColor&color);
    QColor selectedColor() const;

    void setSignedColor(const QColor&color);
    QColor signedColor() const;

    void setGap(uint32_t gap);
    uint32_t gap() const;

    void setSpacing(uint32_t space);
    uint32_t spacing() const;

    void setZoom(double zoom);
    double zoom() const;

    QPoint currentMousePoint() const;// 这个是鼠标选中的点
    void clearMousePoint();

    void clearAllPoints(); // 轨迹选中的点
    void selectAllPoints();
    void setSelectedPoint(int row, int col, bool isSelected = true) ;
    void setSelectedPoint(const QPoint&point,bool isSelected = true);
    void setSelectedPoints(bool isSelected = true);
    void setSelectedPoints(const QVector<QPoint>&points,bool isSelected = true);
    int selectedPointCount() const;
    bool isPointSelected(int row,int col) const;
    QVector<QPoint> selectedPoints() const; // 这个不按照顺序返回选中的点位置

    void clearSignedPoint(); // 预览标记效果的点
    void setSignedPoint(int row,int col);
    void setSignedPoint(const QPoint& point);

    void drawRandomPoints(int count); // 每孔视野数的随机点

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    double mGap;
    double mSpace;
    double mZoom;
    bool mIsZoom;
    bool mIsHighlight;
    bool mIsDrawRandomPoints;
    bool mMouseEvent;
    bool mWheelEvent;
    QPoint mMousePos;
    QPoint mSignedPos;
    QList<QVector<bool>> mSelectedRects;
    int mDrawPointsCount;
    int mRow;
    int mCol;
    PatternState mState;
    QColor mDefaultColor = Qt::darkGray;
    QColor mSelectedColor = Qt::blue;
    QColor mCurrentColor = Qt::green;
    QColor mSignedColor = Qt::red;
private:
    void init();
    void copy(const Pattern&pattern);
    QSize getChildSize() const ;
    QVector<QPointF> getRowHeaderPoints();
    QVector<QPointF> getColHeaderPoints();
    QList<QVector<QPointF>> getBorderPoints() const;
    QList<QVector<QPointF>> getCenterPoints() const;
    QList<QVector<QRectF>> getChildRects() const;
    void drawBorder(QPainter&painter);
    void drawLine(QPainter&painter);
    void drawHeader(QPainter&painter); // 行列表头
    void drawHighlight(QPainter&painter); // 绘制鼠标选中的高亮和已选择区域的高亮
    void drawPoints(QPainter&painter); // 每孔视野数画的点
    void drawSignedPoints(QPainter&painter); // 绘制预览标记的效果
    void enableZoom();
    void disableZoom();
    void enableClick();
    void disableClick();
    void enableHighlight();
    void disableHighlight();
    void updateMinSize();
signals:

};

#endif // PATTERN_H

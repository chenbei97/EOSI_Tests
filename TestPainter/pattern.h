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
#include "Constant.h"

class Pattern : public QWidget
{
    Q_OBJECT
public:
    enum PatternState {BlankState,TickState,MoveState};
    explicit Pattern(QWidget *parent = nullptr);
    explicit Pattern(int rows, int cols,QWidget *parent = nullptr);
    explicit Pattern(const QSize&size,QWidget *parent = nullptr);

    void toggleState(PatternState state);
    PatternState state() const;

    void setPatternSize(int rows,int cols);
    void setPatternSize(const QSize& size);
    QSize patternSize() const;

    void setGap(uint32_t gap);
    uint32_t gap() const;

    void setSpacing(uint32_t space);
    uint32_t spacing() const;

    void setZoom(double zoom);
    double zoom() const;

    void clearSelectedRects();
    void setSelectedRect(int row, int col, bool isSelected = true) ;
    void setSelectedRect(const QPoint&point,bool isSelected = true);
    bool isRectSelected(int row,int col) const;

    void setSignedRect(int row,int col);

    QPoint currentSelectedPos() const;
    QVector<QPoint> selectedPoints() const;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    double mGap;
    double mSpace;
    double mZoom;
    bool mIsZoom;
    bool mIsHighlight;
    bool mMouseEvent;
    bool mWheelEvent;
    QPoint mMousePos;
    QPoint mSignedPos;
    QList<QVector<bool>> mSelectedRects;
    int mRow;
    int mCol;
    PatternState mState;
private:
    void init();
    QSize getChildSize() const ;
    QVector<QPointF> getRowHeaderPoints();
    QVector<QPointF> getColHeaderPoints();
    QList<QVector<QPointF>> getBorderPoints() const;
    QList<QVector<QPointF>> getCenterPoints() const;
    QList<QVector<QRectF>> getChildRects() const;
    void drawBorder(QPainter&painter);
    void drawLine(QPainter&painter);
    void drawHeader(QPainter&painter);
    void drawHighlight(QPainter&painter);
    void drawFlag(QPainter&painter);
    void enableZoom();
    void disableZoom();
    void enableClick();
    void disableClick();
    void enableHighlight();
    void disableHighlight();
signals:

};

#endif // PATTERN_H

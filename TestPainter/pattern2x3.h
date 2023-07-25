#ifndef PATTERN2X3_H
#define PATTERN2X3_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QTouchEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QWheelEvent>

class Pattern2x3 : public QWidget
{
    Q_OBJECT
public:
    enum RectIndex {c11,c12,c13,c21,c22,c23};
    explicit Pattern2x3(QWidget *parent = nullptr);

    void setGap(int gap);
    int gap() const;

    void setZoom(double zoom);
    double zoom() const;

    void setSelectedRect(RectIndex idx, bool isSelected = true) ;
    bool isSelected(RectIndex idx) const;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    //void touchEvent(QTouchEvent*event);
private:
    int mGap;
    double mZoom;
    bool mIsZoom;
    RectIndex mRectIdx;
    QList<bool> mSelectedRects;
signals:

};

#endif // PATTERN2X3_H

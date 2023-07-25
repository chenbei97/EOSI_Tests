#ifndef PATTERN4X6_H
#define PATTERN4X6_H


#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QTouchEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QWheelEvent>

class Pattern4x6 : public QWidget
{
    Q_OBJECT
public:
    explicit Pattern4x6(QWidget *parent = nullptr);

    void setGap(int gap);
    int gap() const;

    void setZoom(double zoom);
    double zoom() const;

    void setSelectedRect(int row, int col, bool isSelected = true) ;
    bool isSelected(int row,int col) const;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    int mGap;
    double mZoom;
    bool mIsZoom;
    QPoint mPos;
    QList<QVector<bool>> mSelectedRects;
    const int mRow = 8;
    const int mCol = 12;
signals:

};


#endif // PATTERN4X6_H

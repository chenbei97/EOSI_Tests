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

class Pattern : public QWidget
{
    Q_OBJECT
public:
    explicit Pattern(QWidget *parent = nullptr);

    void setPatternSize(int rows,int cols);
    void setPatternSize(const QSize& size);
    QSize patternSize() const;

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
    double mGap;
    double mZoom;
    bool mIsZoom;
    QPoint mPos;
    QList<QVector<bool>> mSelectedRects;
    int mRow;
    int mCol;
signals:

};

#endif // PATTERN_H

#ifndef GRAPHICPATTERN_H
#define GRAPHICPATTERN_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QDebug>

class GraphicPattern : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicPattern(QWidget*parent = 0);
    void setPatternSize(int rows,int cols);
    void setGap(double gap);
    void setSpacing(double space);
private:
    double mGap;
    double mSpace;
    int mRows;
    int  mCols;
};

#endif // GRAPHICPATTERN_H

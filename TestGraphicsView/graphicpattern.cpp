#include "graphicpattern.h"


GraphicPattern::GraphicPattern(QWidget*parent):QGraphicsView(parent)
{

    //resize(800,600);
    setScene(new QGraphicsScene(rect()));
    setMinimumSize(600,300);
    qDebug()<<"scene.rect = "<<scene()->sceneRect()<<" view.rect = "<<rect();

    mGap = 10;
    mSpace = 5;
    mRows = -1;
    mCols = -1;

}


void GraphicPattern::setPatternSize(int rows, int cols)
{
    mRows = rows;
    mCols = cols;

    auto cw = (width()-2*mGap - (mCols-1)* mSpace) / mCols;
    auto ch = (height()-2*mGap - (mRows-1)* mSpace) / mRows;
    int radius = cw>ch?ch:cw;

    for(int r = 0; r < mRows; ++ r)
    {
        for(int c = 0; c < mCols; ++ c) {

        }
    }
}

void GraphicPattern::setGap(double gap)
{
    mGap = gap;
}

void GraphicPattern::setSpacing(double space)
{
    mSpace = space;
}

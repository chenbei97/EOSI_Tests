#include "tableviewwidget2x2.h"

TableViewWidget2x2::TableViewWidget2x2(QWidget *parent) : QWidget(parent)
{

}

void TableViewWidget2x2::setPixmap(int index,QPixmap*pix)
{
    mLabels[index]->setPixmap(*pix);
    mPixs[index] = pix;
}

QPixmap*TableViewWidget2x2::pixmap(int index) const
{
    return mPixs[index];
}

QVector<QPixmap*> TableViewWidget2x2::pixmaps() const
{
    return mPixs;
}

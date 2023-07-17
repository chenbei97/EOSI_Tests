#include "image2x2widget.h"
#include <QDebug>


Image2x2Widget::Image2x2Widget(QWidget *parent) : QWidget(parent)
{

    for(int i = 0 ; i < 4; i++)
    {
        mLabels.append(new QLabel);
        mFileNames.append("");
    }

    QHBoxLayout * lay1 = new QHBoxLayout;
    lay1->addWidget(mLabels[0]);
    lay1->addWidget(mLabels[1]);
    QHBoxLayout * lay2 = new QHBoxLayout;
    lay2->addWidget(mLabels[2]);
    lay2->addWidget(mLabels[3]);

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addLayout(lay1);
    lay->addLayout(lay2);
}

void Image2x2Widget::setPixmap(int index,const QString& file)
{
    mFileNames[index] = file;

    mLabels[index]->setPixmap(QPixmap(file));
}

void Image2x2Widget::setPixmap(int index,const QPixmap&pix)
{
    mLabels[index]->setPixmap(pix);

}

const QPixmap * Image2x2Widget::pixmap(int index) const
{
    return mLabels[index]->pixmap();
}

QString Image2x2Widget::pixmapName(int index) const
{
    return mFileNames[index];
}

QStringList Image2x2Widget::pixmapNames() const
{
    return  mFileNames;
}

QList<const QPixmap*> Image2x2Widget::pixmaps()  const
{
    QList<const QPixmap*> pixs;
    foreach(auto label,mLabels)
        pixs.append(label->pixmap());
    return pixs;
}

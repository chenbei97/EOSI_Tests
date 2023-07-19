#include "image2x2widget.h"
#include <QDebug>


Image2x2Widget::Image2x2Widget(QWidget *parent) : QWidget(parent)
{

    for(int i = 0 ; i < 4; i++)
    {
        mLabels.append(new QLabel);
        mFileNames.append("");
        mPixs.append(nullptr);
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

//void Image2x2Widget::setPixmap(int index,const QString& file)
//{
//    mFileNames[index] = file;

//    mLabels[index]->setPixmap(QPixmap(file));
//}

//void Image2x2Widget::setPixmap(int index,const QPixmap&pix)
//{
//    mLabels[index]->setPixmap(pix);
//}

void Image2x2Widget::setText(int index, const QString&text)
{
    mFileNames[index] = text;
    mLabels[index]->setText(text);

}

QString Image2x2Widget::text(int index) const
{
    return mFileNames[index];
}

QStringList Image2x2Widget::texts() const
{
    return mFileNames;
}

void Image2x2Widget::setPixmap(int index,QPixmap*pix)
{
    mLabels[index]->setPixmap(*pix);
    mPixs[index] = pix;
}

QPixmap* Image2x2Widget::pixmap(int index) const
{
    // mLabels[index]->pixmap()返回的const QPixmap*指针不兼容
    return mPixs[index];
}

//const QPixmap * Image2x2Widget::pixmap(int index) const
//{
//    return mLabels[index]->pixmap();
//}

//QString Image2x2Widget::pixmapName(int index) const
//{
//    return mFileNames[index];
//}

//QStringList Image2x2Widget::pixmapNames() const
//{
//    return  mFileNames;
//}

//QList<const QPixmap*> Image2x2Widget::pixmaps()
//{
//    QList< const QPixmap*> pixs;
//    foreach(auto label,mLabels)
//        pixs.append(label->pixmap());
//    return pixs;
//}

QList<QPixmap*> Image2x2Widget::pixmaps() const
{
    return mPixs;
}

void Image2x2Widget::mousePressEvent(QMouseEvent *event)
{ // 事件被TableView截获，除非设置触发方式有单击或者全部触发这里才会接收
    qDebug()<<"press pos = "<<event->pos();
}

void Image2x2Widget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"Release pos = "<<event->pos();
}


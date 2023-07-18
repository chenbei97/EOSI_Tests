#include "button.h"
#include <QDebug>

Button::Button(QWidget*parent):QWidget(parent)
{

}

Button::Button(const QString&text,QWidget*parent):QWidget(parent),mText(text)
{

}

QIcon Button::icon() const
{
    return mIcon;
}

void Button::setIcon(const QIcon &icon)
{
    mIcon = icon;
}

void Button::paintEvent(QPaintEvent *e)
{
    QStyleOptionButton option;
         option.initFrom(this);
         option.state = isPress ? QStyle::State_Sunken : QStyle::State_Raised;
             //option.features |= QStyleOptionButton::DefaultButton;
         if (isPress)
             option.features |= QStyleOptionButton::Flat;
         option.text = mText;
         //option.icon = icon();


         QPainter painter(this);


         if (option.state & QStyle::State_Enabled) {
             painter.setPen(option.palette.mid().color());
             painter.setBrush(option.palette.buttonText());
         } else {
             painter.setPen(option.palette.buttonText().color());
             painter.setBrush(option.palette.mid());
         }

         style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);
         update();
         e->accept();
}

void Button::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
       isPress = true;
       qDebug()<<"press isPress = "<<isPress;
       update();
    }
    event->accept();
}

void Button::mouseReleaseEvent(QMouseEvent *event)
{
   isPress = false;
   update();
    event->accept();
    qDebug()<<"release isPress = "<<isPress;
}


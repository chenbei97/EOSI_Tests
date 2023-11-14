#include "channelbutton.h"

ChannelButton::ChannelButton(const QString& text,QWidget*parent):QPushButton(text,parent)
{

}

void ChannelButton::paintEvent(QPaintEvent * event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    auto pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(Qt::red);
    painter.setPen(pen);

    auto benchmark = width()>=height()?height():width();
    const double radius = benchmark / 5.0;
    painter.drawEllipse(0.0,0.0,radius*2.0,radius*2.0);

    event->accept();
}

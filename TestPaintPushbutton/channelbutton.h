#ifndef CHANNELBUTTON_H
#define CHANNELBUTTON_H

#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>

class ChannelButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ChannelButton(const QString& text,QWidget*parent=nullptr);
    void paintEvent(QPaintEvent *) override;
};

#endif // CHANNELBUTTON_H

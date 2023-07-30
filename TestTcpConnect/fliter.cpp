#include "fliter.h"

Filter::Filter(QObject *parent) : QObject(parent)
{

}

bool Filter::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick || event->type() == QEvent::MouseButtonPress)
        return true; // true表示拦截
    else return QObject::eventFilter(watched,event);
}

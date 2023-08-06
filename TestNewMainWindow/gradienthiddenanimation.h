#ifndef GRADIENTHIDDENANIMATION_H
#define GRADIENTHIDDENANIMATION_H

#include "qdebug.h"
#include "qpropertyanimation.h"
#include "qgraphicseffect.h"

class GradientHiddenAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    explicit GradientHiddenAnimation(QObject *parent = nullptr);
    QGraphicsOpacityEffect * effect() const;
    void setEffect(QGraphicsEffect*effect);
private:
    QGraphicsOpacityEffect * meffect;
signals:

};

#endif // GRADIENTHIDDENANIMATION_H

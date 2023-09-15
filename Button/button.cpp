#include "button.h"

Button::Button(QWidget* parent) :QPushButton(parent)
{
        mState = false;
        mEffectSwitch = false;
        mAnimation = nullptr;
        mEffect = nullptr;
}

Button::Button(const QString&text,QWidget* parent):QPushButton(parent)
{
        setText(text);
        mState = false;
        mEffectSwitch = false;
        mAnimation = nullptr;
        mEffect = nullptr;
}

void Button::enableEffect()
{
    mEffectSwitch = true;

    mEffect = new QGraphicsOpacityEffect(this); // 延迟创建
    mEffect->setOpacity(1.0);
    setGraphicsEffect(mEffect);

    mAnimation = new QPropertyAnimation(mEffect,"opacity",this);
    mAnimation->setEasingCurve(QEasingCurve::Linear);
    mAnimation->setDuration(1000);

    mAnimation->setStartValue(0.0);
    mAnimation->setEndValue(1.0);
}

void Button::disableEffect()
{
    mEffectSwitch = false;
}

void Button::resizeEvent(QResizeEvent *e)
{
        if (mEffectSwitch)
            mAnimation->start(QAbstractAnimation::KeepWhenStopped);
        QPushButton::resizeEvent(e);
}


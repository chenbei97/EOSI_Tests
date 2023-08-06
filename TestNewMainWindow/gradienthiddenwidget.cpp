#include "gradienthiddenwidget.h"

GradientHiddenWidget::GradientHiddenWidget(QWidget *parent) : QWidget(parent)
{
    auto effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(1.0);
    setGraphicsEffect(effect);

    animation = new GradientHiddenAnimation(this);
    animation->setPropertyName("opacity");
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setDuration(2000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setTargetObject(effect);

    line = horline();
    header = headerLabel();
    mainlay =  new QVBoxLayout(this);
    mainlay->addWidget(header);
    mainlay->addWidget(line);
}

QFrame* GradientHiddenWidget::horline() const
{
    auto line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Plain);
    return line;
}

QLabel * GradientHiddenWidget::headerLabel() const
{
    auto label = new QLabel(tr("创建新流程还是使用已有流程?"));
    auto p = label->palette();
    p.setColor(QPalette::Foreground,"#0FC4F5");
    label->setPalette(p);
    auto font = label->font();
    font.setBold(true);
    font.setPointSize(18);
    label->setFont(font);
    label->setMinimumHeight(50);
    label->setMaximumHeight(100);
    return label;
}


void GradientHiddenWidget::showEvent(QShowEvent *event)
{
    animation->start();
    return QWidget::showEvent(event);
}

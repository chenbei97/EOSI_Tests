#include "scanplanconfig.h"

ScanPlanConfig::ScanPlanConfig(QWidget *parent) : QWidget(parent)
{

    auto label = headerLabel();
    auto line = horline();
    auto once = onceButton();
    auto schedule = scheduleButton();

    auto oncelay = new QHBoxLayout;
    oncelay->addWidget(once);
    oncelay->addStretch();
    auto schedulelay = new QHBoxLayout;
    schedulelay->addWidget(schedule);
    schedulelay->addStretch();

    auto lay = new QVBoxLayout(this);

    lay->addWidget(label);
    lay->addWidget(line);
    lay->addLayout(oncelay);
    lay->addStretch();
    lay->addLayout(schedulelay);
    lay->addSpacing(250);

    connect(once,&QRadioButton::clicked,this,&ScanPlanConfig::scanPlan);
    connect(schedule,&QRadioButton::clicked,this,&ScanPlanConfig::scanPlan);
}

void ScanPlanConfig::scanPlan()
{
    auto w = qobject_cast<QRadioButton*>(sender());
    if (w->objectName() == "once")
        emit scanPlanChanged(Once);
    else emit scanPlanChanged(Schedule);
    //qDebug()<<w->objectName();
}

QRadioButton * ScanPlanConfig::scheduleButton() const
{
    auto btn = new QRadioButton(tr("计划扫描"));
    btn->setObjectName("schedule");
    return btn;
}

QRadioButton * ScanPlanConfig::onceButton() const
{
    auto btn = new QRadioButton(tr("立即扫描"));
    btn->setObjectName("once");
    return btn;
}

QFrame* ScanPlanConfig::horline() const
{
    auto line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Plain);
    return line;
}

QLabel * ScanPlanConfig::headerLabel() const
{
    auto label = new QLabel(tr("计划扫描还是立即扫描?"));
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

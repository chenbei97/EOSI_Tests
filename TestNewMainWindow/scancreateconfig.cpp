#include "scancreateconfig.h"

ScanCreateConfig::ScanCreateConfig(QWidget *parent) :GradientHiddenWidget(parent)
{
    header->setText(tr("创建新流程还是使用已有流程?"));
    auto create = createNewButton();
    auto current = copyCurrentButton();
    auto previous = copyPreviousButton();

    auto lay1 = new QHBoxLayout;
    lay1->addWidget(create);
    lay1->addStretch();
    auto lay2 = new QHBoxLayout;
    lay2->addWidget(current);
    lay2->addStretch();
    auto lay3 = new QHBoxLayout;
    lay3->addWidget(previous);
    lay3->addStretch();

    mainlay->addLayout(lay1);
    mainlay->addStretch();
    mainlay->addSpacing(200);
    mainlay->addLayout(lay2);
    mainlay->addSpacing(200);
    mainlay->addLayout(lay3);
    mainlay->addSpacing(200);

    connect(create,&QRadioButton::clicked,this,&ScanCreateConfig::onCreateConfig);
    connect(current,&QRadioButton::clicked,this,&ScanCreateConfig::onCreateConfig);
    connect(previous,&QRadioButton::clicked,this,&ScanCreateConfig::onCreateConfig);
}

void ScanCreateConfig::onCreateConfig()
{
    auto w = qobject_cast<QRadioButton*>(sender());
    if (w->objectName() == "create") {
        emit createMode(New);
    } else if (w->objectName() == "current"){
        emit createMode(Current);
    } else {
        emit createMode(Previous);
    }
}

QRadioButton * ScanCreateConfig::createNewButton() const
{
    auto btn = new QRadioButton(tr("创建全新实验流程"));
    btn->setObjectName("create");
    return btn;
}

QRadioButton * ScanCreateConfig::copyCurrentButton()  const
{
    auto btn = new QRadioButton(tr("复制当前实验流程"));
    btn->setObjectName("current");
    return btn;
}

QRadioButton * ScanCreateConfig::copyPreviousButton() const
{
    auto btn = new QRadioButton(tr("复制历史实验流程"));
    btn->setObjectName("previous");
    return btn;
}



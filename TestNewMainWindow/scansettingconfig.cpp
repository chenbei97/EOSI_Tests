#include "scansettingconfig.h"

ScanSettingConfig::ScanSettingConfig(QWidget *parent) : GradientHiddenWidget(parent)
{
    header->setText(tr("通道物镜孔板设置"));
    mChannels = new QComboBox;
    mObjectives = new QComboBox;
    mViews = new QComboBox;
    mWells = new QComboBox;
    mPattern = new Pattern;

    mChannels->addItems(QStringList()<<"bright"<<"phase"<<"red"<<"green"<<"blue"<<"fluorescence");
    mObjectives->addItems(QStringList()<<"4x"<<"10x"<<"10xPH"<<"20x");
    mViews->addItems(QStringList()<<"2"<<"4"<<"8");
    mWells->addItems(QStringList()<<"6"<<"24"<<"96"<<"384");
    mChannels->setMaximumWidth(200);
    mObjectives->setMaximumWidth(200);
    mViews->setMaximumWidth(200);
    mWells->setMaximumWidth(200);
    mPattern->setPatternSize(8,12);
    mPattern->toggleState(Pattern::BlankState);


    QFormLayout * top = new QFormLayout;
    top->addRow("channel: ",mChannels);
    top->addRow("objective: ",mObjectives);
    top->addRow("view: ",mViews);
    top->addRow("wellsize: ",mWells);
    top->setHorizontalSpacing(50);
    top->setVerticalSpacing(110);


    auto toplay = new QHBoxLayout;
    toplay->addLayout(top);
    toplay->addWidget(mPattern);
    toplay->setStretch(0,1);
    toplay->setStretch(1,3);

    mainlay->addLayout(toplay);
    mainlay->addStretch();

    connect(mChannels,QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,[=](int index){emit channelOption(ChannelOption(index));});
    connect(mObjectives,QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,[=](int index){emit objectiveOption(ObjectiveOption(index));});
    connect(mViews,QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,[=](int index){emit viewOption(ViewOption(index));});
    connect(mWells,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[=](int index){
            emit wellsizeOption(WellsizeOption(index));
            switch (index) {
                case 0: mPattern->setPatternSize(2,3);break;
                case 1: mPattern->setPatternSize(4,6);break;
                case 2: mPattern->setPatternSize(8,12);break;
                case 3: mPattern->setPatternSize(16,24);break;
                default:break;
            }
    });

    mChannels->setCurrentIndex(-1);
    mObjectives->setCurrentIndex(-1);
    mViews->setCurrentIndex(-1);
    mWells->setCurrentIndex(-1); // 让用户必须选,不然直接下一步就没法传递选择的信息
}

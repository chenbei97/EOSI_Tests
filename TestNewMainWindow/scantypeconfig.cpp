#include "scantypeconfig.h"


ScanTypeConfig::ScanTypeConfig(QWidget *parent) : GradientHiddenWidget(parent)
{
    QStringList types = {"Standard","ImageLock","ScratchWound","WholeWell",
                         "DilutionCloning","Chemotaxis","Spheroid","NeuronalActivity"};
    typelist = new QListWidget;
    typelist->setMaximumWidth(300);
    typelist->addItems(types);
    info = new QLabel;

    QHBoxLayout * lay = new QHBoxLayout;
    lay->addWidget(typelist);
    lay->addWidget(info);

    header->setText(tr("扫描类型设置"));
    //mainlay->addStretch();
    mainlay->addLayout(lay);
    mainlay->addSpacing(10);

    connect(typelist,&QListWidget::currentRowChanged,this,[=](int idx){emit scanType(ScanType(idx));});
}


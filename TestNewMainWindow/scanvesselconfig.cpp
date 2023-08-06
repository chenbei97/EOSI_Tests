#include "scanvesselconfig.h"

ScanVesselConfig::ScanVesselConfig(QWidget *parent) : QWidget(parent)
{
        setProgressBar();
        addStackedWidgets();
        auto btnlay = setButton();
\
        auto lay = new QVBoxLayout(this);
        lay->addWidget(mProgressBar);
        lay->addSpacing(10);
        lay->addWidget(mStack);
        lay->addLayout(btnlay);
        resize(1200,800);

        connect(mProgressBar,&QProgressBar::valueChanged,this,&ScanVesselConfig::onProgressValue);
        mProgressBar->setValue(data.progress);
        connect(mNext,&QPushButton::clicked,this,&ScanVesselConfig::onNext);
        connect(mPrevious,&QPushButton::clicked,this,&ScanVesselConfig::onPrevious);
        connect(mStack,&QStackedWidget::currentChanged,this,&ScanVesselConfig::onStackChanged);

        setFont(QFont("Times New Roman",12));
}

void ScanVesselConfig::addStackedWidgets()
{
    mStack = new QStackedWidget;
    mCreateConfig = new ScanCreateConfig;
    mTypeConfig = new ScanTypeConfig;
    mSettingConfig = new ScanSettingConfig;
    mPatternConfig = new ScanPatternConfig;
    mPatternPreview = new ScanPatternPreview;
    mDescConfig = new ScanDescriptionConfig;
    mTimeConfig = new ScanTimeConfig;


    mStack->addWidget(mCreateConfig);
    mStack->addWidget(mTypeConfig);
    mStack->addWidget(mSettingConfig);
    mStack->addWidget(mPatternConfig);
    mStack->addWidget(mPatternPreview);
    mStack->addWidget(mDescConfig);
    mStack->addWidget(mTimeConfig);

    connect(mCreateConfig,&ScanCreateConfig::createMode,this,&ScanVesselConfig::setCreateMode);
    connect(mTypeConfig,&ScanTypeConfig::scanType,this,&ScanVesselConfig::setScanType);
    connect(mSettingConfig,&ScanSettingConfig::channelOption,this,&ScanVesselConfig::setChannel);
    connect(mSettingConfig,&ScanSettingConfig::viewOption,this,&ScanVesselConfig::setView);
    connect(mSettingConfig,&ScanSettingConfig::wellsizeOption,this,&ScanVesselConfig::setWellsize);
    connect(mSettingConfig,&ScanSettingConfig::objectiveOption,this,&ScanVesselConfig::setObjective);
}

QHBoxLayout* ScanVesselConfig::setButton()
{
        auto lay = new QHBoxLayout;
        mNext = new QPushButton(tr("下一步"));
        mPrevious = new QPushButton(tr("上一步"));
        lay->addWidget(mPrevious);
        lay->addStretch();
        lay->addWidget(mNext);
        return lay;
}

void ScanVesselConfig::setProgressBar()
{
    mProgressBar = new QProgressBar;
    mProgressBar->setRange(0,10);
    mProgressBar->setAlignment(Qt::AlignCenter);

    mProgressBar->setFormat("%v/%m");
    mProgressBar->setTextVisible(true);
    mProgressBar->setMinimumHeight(40);
}

void ScanVesselConfig::onStackChanged(int index)
{

}


void ScanVesselConfig::onNext()
{
    if (data.progress == 1) {
        if (data.create_mode == ScanCreateMode::EmptyMode)
        {
            QMessageBox::warning(this,tr("警告"),tr("至少选择一个创建模式!"));
            return;
        }
        if (data.create_mode != ScanCreateConfig::New)
        {
            // 复制当前或者历史配置,弹出一些窗口进行处理
            close();
        }
    }

    if (data.progress == 2) {
        if (data.scan_type == ScanType::EmptyType)
        {
            QMessageBox::warning(this,tr("警告"),tr("至少选择一个扫描模式!"));
            return;
        }
    }

    if (data.progress == 3) {
        if (data.channel == ChannelOption::EmptyChannel)
        {
            QMessageBox::warning(this,tr("警告"),tr("至少选择一个成像模式!"));
            return;
        }
        if (data.objective == ObjectiveOption::EmptyObjective)
        {
            QMessageBox::warning(this,tr("警告"),tr("至少选择一个物镜倍数!"));
            return;
        }
        if (data.view == ViewOption::EmptyView)
        {
            QMessageBox::warning(this,tr("警告"),tr("至少选择一个每孔视野数!"));
            return;
        }
        if (data.wellsize == WellsizeOption::EmptyWellsize)
        {
            QMessageBox::warning(this,tr("警告"),tr("至少选择一个孔板规格!"));
            return;
        }
    }

    if (data.progress == 4) { // 选择完成像轨迹,要把轨迹的位置信息和孔命名传递给预览界面
         // 视野数和规格尺寸已经通过信号传递完毕,不需要再设置
          auto names = mPatternConfig->sortNames();
          if (!names.count()) {
              QMessageBox::warning(this,tr("警告"),tr("至少添加一个孔!"));
              return;
          }
           mPatternPreview->setSortPoints(mPatternConfig->sortSelectedPoints());
           mPatternPreview->setSortNames(names);
           data.points = mPatternConfig->sortSelectedPoints(); // 把位置信息保存
    }

    if (data.progress == 6) { // 实验的各类信息更新
        auto experName = mDescConfig->experName();
        auto experPerson = mDescConfig->personName();
        if (experName.isEmpty() || experPerson.isEmpty()) return;

        data.experiment_date = mDescConfig->experDate();
        data.experiment_name = experName;
        data.experiment_person = experPerson;
        data.experiment_group = mDescConfig->workGroup();
        data.experiment_celltype = mDescConfig->cellType();
        data.experiment_description = mDescConfig->description();
    }

    if (data.progress == 7) {
        data.scan_is_once = mTimeConfig->isOnce();

        if (!mTimeConfig->isOnce()) {
            if (!mTimeConfig->checkScheduledTime()) return;
            data.scan_total_time = mTimeConfig->totalScheduledTime();
            data.scan_total_count = mTimeConfig->totcalScheduledCount();
            data.scan_end_datetime = mTimeConfig->endScheduledTime();
            data.scan_start_datetime = mTimeConfig->startScheduledTime();
            data.scan_duration_time = mTimeConfig->durationScheduledTime();
            qDebug()<<"is schedule => start = "<<data.scan_start_datetime<<" end = "<<data.scan_end_datetime
                   << " total = "<<data.scan_total_time<<" duration = "<<data.scan_duration_time<<" count = "<<data.scan_total_count;
        } else {
            if (!mTimeConfig->checkOnceTime()) return;
            data.scan_once_total_time = mTimeConfig->totalOnceTime();
            data.scan_once_duration_time = mTimeConfig->durationOnceTime();
            data.scan_once_total_count = mTimeConfig->totcalOnceCount();
            qDebug()<<"is once => total = "<<data.scan_once_total_time<<" duration = "<<data.scan_once_duration_time
                   <<" count = "<<data.scan_once_total_count;
        }
        qDebug()<<"isOnce = "<<mTimeConfig->isOnce();


    }

    data.progress++;
    mProgressBar->setValue(data.progress);
}

void ScanVesselConfig::onPrevious()
{
    data.progress--;
    mProgressBar->setValue(data.progress);
}


void ScanVesselConfig::onProgressValue(int value)
{
    mStack->setCurrentIndex(value-1);

    if (value == 1)
        mPrevious->setEnabled(false);
    else mPrevious->setEnabled(true);

    if( value == 10)
    {
        mNext->setText(tr("完成"));
        close();
    }


}

void ScanVesselConfig::setCreateMode(ScanCreateMode mode)
{
    data.create_mode = mode;
}

void ScanVesselConfig::setScanType(ScanType type)
{
    data.scan_type = type;
}

void ScanVesselConfig::setChannel(ChannelOption option)
{
    data.channel = option;
}


void ScanVesselConfig::setObjective(ObjectiveOption option)
{
    data.objective = option;
}

void ScanVesselConfig::setView(ViewOption option)
{
    data.view = option;
    int views = 0;
    switch (option) {
        case 0 : views = 2;break;
        case 1: views = 4; break;
        case 2: views = 8; break;
        default :break;
    }
    mPatternPreview->setViews(views); // 成像轨迹需要设置每孔视野数
}

void ScanVesselConfig::setWellsize(WellsizeOption option)
{
    data.wellsize= option;
    // 对于每孔视野数和孔板尺寸需要传递给下一步 progress=4,5 选择和预览成像轨迹
    // 如果更新了尺寸,预览成像轨迹之前可能已经有了一些命名并选点,要清除
    mPatternConfig->clearPointsNames();
    mPatternPreview->clearPointsNames();
    switch (option) {
        case 0: mPatternConfig->setPatternSize(2,3);
                    mPatternPreview->setPatternSize(2,3);
                    break;
        case 1:
                    mPatternConfig->setPatternSize(4,6);
                    mPatternPreview->setPatternSize(4,6);
                    break;
        case 2: mPatternConfig->setPatternSize(8,12);
                    mPatternPreview->setPatternSize(8,12);
                    break;
        case 3: mPatternConfig->setPatternSize(16,24);
                    mPatternPreview->setPatternSize(16,24);
                    break;
        default:break;
    }
}

void ScanVesselConfig::resizeEvent(QResizeEvent *e)
{
    mProgressBar->resize(e->size().width(),40);
    return QWidget::resizeEvent(e);
}

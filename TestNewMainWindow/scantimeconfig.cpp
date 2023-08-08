#include "scantimeconfig.h"

ScanTimeConfig::ScanTimeConfig(QWidget *parent) : GradientHiddenWidget(parent)
{
    mCheckBox = new QCheckBox(tr("计划执行?"));
    mCheckBox->setChecked(true);

    mStartDate = new QDateEdit;
    mEndDate = new QDateEdit;
    mStartTime = new QSpinBox;
    mEndTime = new QSpinBox;
    mDuration = new QSpinBox;
    mInfo = new QLabel(tr("总时间: %1 hours  总扫描次数: %2").arg(0).arg(0));

    mStartDate->setMinimumDate(QDate::currentDate());
    mEndDate->setMinimumDate(QDate::currentDate());
    mStartDate->setDisplayFormat("MM/dd");
    mEndDate->setDisplayFormat("MM/dd");
    mStartTime->setRange(0,24);
    mEndTime->setRange(0,24);
    mStartTime->setSuffix(":00:00");
    mEndTime->setSuffix(":00:00");
    mDuration->setMinimum(1);
    mDuration->setSuffix(" hours");

    QFormLayout * flay = new QFormLayout;
    flay->addRow(tr("开始日期: "),mStartDate);
    flay->addRow(tr("开始时间: "),mStartTime);
    flay->addRow(tr("结束日期: "),mEndDate);
    flay->addRow(tr("结束时间: "),mEndTime);
    flay->addRow(tr("间隔时间: "),mDuration);
    auto box1 = new QGroupBox(tr("计划执行"));
    box1->setLayout(flay);

    mTotalTime = new QSpinBox;
    mScanTime = new QSpinBox;
    mTotalTime->setSuffix(" hours");
    mScanTime->setSuffix(" hours");
    mTotalTime->setMinimum(1);
    mScanTime->setMinimum(1);

    QFormLayout * blay = new QFormLayout;
    blay->addRow(tr("扫描时间: "),mTotalTime);
    blay->addRow(tr("扫描频率"),mScanTime);
    auto box2 = new QGroupBox(tr("立即执行"));
    box2->setLayout(blay);
    box2->setEnabled(false);

    header->setText(tr("扫描时间和周期设置"));
    mainlay->addWidget(mCheckBox);
    mainlay->addSpacing(10);
    mainlay->addWidget(box1);
    mainlay->addSpacing(10);
    mainlay->addWidget(box2);
    mainlay->addSpacing(10);
    mainlay->addWidget(mInfo);
    mainlay->addStretch();

    connect(mCheckBox,&QCheckBox::stateChanged,this,[=](int state){
        auto r = state==Qt::Checked?true:false;
        box1->setEnabled(r);
        box2->setEnabled(!r);
    });
    connect(mStartDate,&QDateEdit::dateChanged,this,&ScanTimeConfig::onDateChanged);
    connect(mEndDate,&QDateEdit::dateChanged,this,&ScanTimeConfig::onDateChanged);
    connect(mStartTime,QOverload<int>::of(&QSpinBox::valueChanged),this,&ScanTimeConfig::onTimeChanged);
    connect(mEndTime,QOverload<int>::of(&QSpinBox::valueChanged),this,&ScanTimeConfig::onTimeChanged);
    connect(mDuration,QOverload<int>::of(&QSpinBox::valueChanged),this,&ScanTimeConfig::onTimeChanged);
    connect(mTotalTime,QOverload<int>::of(&QSpinBox::valueChanged),this,&ScanTimeConfig::onTotalScanChanged);
    connect(mScanTime,QOverload<int>::of(&QSpinBox::valueChanged),this,&ScanTimeConfig::onTotalScanChanged);
    connect(&timer,&QTimer::timeout,this,&ScanTimeConfig::onTimer);
    timer.start(1000*60*60*24-1);
}

void ScanTimeConfig::refreshInfo()
{

    if (mStartDate->date() > mEndDate->date()) // 比结束时间晚
        mInfo->setText(tr("警告: 不允许开始时间晚于结束时间!"));

    else if (mStartDate->date() == mEndDate->date()) { // 如果是同一天,继续比较时间
        if (mStartDate->date() == QDate::currentDate()) // 如果还都是当天, 除了起始时间要早于结束时间,且大于间隔时间
        {
            if (mStartTime->value() < QTime::currentTime().hour()+1) // 12.02返回的12,实际最少13 起始时间还不能早于当前时间
            {
                mInfo->setText(tr("警告: 不允许开始时间早于当前时间!"));
            } else { // 起始时间满足时 判断起始时间要早于结束时间,且大于间隔时间
                if (mStartTime->value() >= mEndTime->value())
                    mInfo->setText(tr("警告: 不允许开始时间晚于结束时间!")); // 取等号,时间不能一样
                else {
                    auto hours = mEndTime->value() - mStartTime->value();
                    if (hours < mDuration->value())
                        mInfo->setText(tr("警告: 开始和结束时间的差值至少大于一个间隔时间!"));
                     else mInfo->setText(tr("总时间: %1 hours  总扫描次数: %2").arg(hours).arg(hours/mDuration->value()));
                }
            }

        } else { // 不是当天 ,同一天只需要比较起始时间要早于结束时间,且大于间隔时间
                if (mStartTime->value() >= mEndTime->value())
                    mInfo->setText(tr("警告: 不允许开始时间晚于结束时间!")); // 取等号,时间不能一样
                else {
                    auto hours = mEndTime->value() - mStartTime->value();
                    if (hours < mDuration->value())
                        mInfo->setText(tr("警告: 开始和结束时间的差值至少大于一个间隔时间!"));
                     else mInfo->setText(tr("总时间: %1 hours  总扫描次数: %2").arg(hours).arg(hours/mDuration->value()));
                }
            }
    }

    else { // 起始时间 < 终止时间 , 不需要判断结束时间要万余终止时间(一定成立),需要判断间隔时间
        // 以及如果起始时间是今天,不能超过当前时间
        if (mStartDate->date() == QDate::currentDate())
        {
            if (mStartTime->value() < QTime::currentTime().hour()+1) // 12.02返回的12,实际最少13 起始时间还不能早于当前时间
            {
                mInfo->setText(tr("警告: 不允许开始时间早于当前时间!"));
            } else { // 没有超过当前时间,只需要判断间隔时间

                auto hours = mEndTime->value() - mStartTime->value()
                        + 24*(mEndDate->date().dayOfYear()-mStartDate->date().dayOfYear());
                if (hours < mDuration->value()) {
                    mInfo->setText(tr("警告: 开始和结束时间的差值至少大于一个间隔时间!"));
                } else mInfo->setText(tr("总时间: %1 hours  总扫描次数: %2").arg(hours).arg(hours/ mDuration->value())); // 比结束时间早
            }
        } else { // 起始不是今天,只需要判断间隔时间
            auto hours = mEndTime->value() - mStartTime->value()
                    + 24*(mEndDate->date().dayOfYear()-mStartDate->date().dayOfYear());
            if (hours < mDuration->value()) {
                mInfo->setText(tr("警告: 开始和结束时间的差值至少大于一个间隔时间!"));
            } else mInfo->setText(tr("总时间: %1 hours  总扫描次数: %2").arg(hours).arg(hours/ mDuration->value())); // 比结束时间早
        }

    }

}

bool ScanTimeConfig::isOnce() const
{
    return !mCheckBox->isChecked();
}

bool ScanTimeConfig::isSchedule() const
{
    return !isOnce();
}

bool ScanTimeConfig::checkScheduledTime()
{
       // 计算出来的总时间必须大于等于一个间隔时间
       auto hours = mEndTime->value() - mStartTime->value()
               + 24*(mEndDate->date().dayOfYear()-mStartDate->date().dayOfYear());
       // 如果起始时间是今天,还不能早于当前时间
//       qDebug()<<"endDate = "<<mEndDate->date()<<" startDate = "<<mStartDate->date()
//              <<" order1 = "<<mEndDate->date().daysInYear()<<"  order2 = "<<mStartDate->date().daysInYear();
       bool r = true;
       if (mStartDate->date() == QDate::currentDate() )
       {
           if (mStartTime->value() < QTime::currentTime().hour()+1)
               r = false;
       }
       if (r && (hours >= mDuration->value()))
           return true;
       QMessageBox::critical(this,tr("错误"),tr("扫描时间设置不正确!"));
        return false;
}

bool ScanTimeConfig::checkOnceTime()
{
    if (mTotalTime->value()>= mScanTime->value())
        return true;
    QMessageBox::critical(this,tr("错误"),tr("扫描时间设置不正确!"));
    return  false;
}

void ScanTimeConfig::onTotalScanChanged()
{ // 总时间要大于等于扫描时间
   auto total = mTotalTime->value();
   auto duration = mScanTime->value();
   if (total < duration)
       mInfo->setText(tr("警告: 实验时间不能比扫描间隔短!"));
   else mInfo->setText(tr("总扫描次数: %1").arg(total/duration));
}

void ScanTimeConfig::onDateChanged(const QDate&date)
{
   Q_UNUSED(date);
   refreshInfo();
}

void ScanTimeConfig::onTimeChanged(int time)
{
    Q_UNUSED(time);
    refreshInfo();
}

void ScanTimeConfig::onTimer()
{
    mStartDate->setMinimumDate(QDate::currentDate());
    mEndDate->setMinimumDate(QDate::currentDate());
}

QDateTime ScanTimeConfig::startScheduledTime()
{
    if (!checkScheduledTime()) return QDateTime();
    auto date = mStartDate->date().toString("yyyy-MM-dd"); // "2023/08/06"
    auto time = mStartTime->text();//  "14:00"
    if (time.indexOf(':') != 2)
        time.prepend('0'); // 让1:00:00 变成01:00:00
    return  QDateTime::fromString(date + "T"+ time,Qt::ISODate);
}

QDateTime ScanTimeConfig::endScheduledTime()
{
    if (!checkScheduledTime()) return QDateTime();
    auto date = mEndDate->date().toString("yyyy-MM-dd");
    auto time = mEndTime->text();
    if (time.indexOf(':') != 2)
        time.prepend('0'); // 让1:00:00 变成01:00:00
    auto t = QDateTime::fromString(date + "T"+ time,Qt::ISODate);
    //qDebug()<<date<<time<<t<<QDateTime::fromString("2021-01-01T14:00:00",Qt::ISODate);
    //qDebug()<<QDate::fromString(date+" "+time,"yyyy-MM-dd h:mm:ss");
    return  t;
}

int ScanTimeConfig::durationScheduledTime()
{
    if (!checkScheduledTime()) return 0;
    return  mDuration->value();
}

int ScanTimeConfig::durationOnceTime()
{
    if (!checkOnceTime()) return  0;
    return  mScanTime->value();
}

int ScanTimeConfig::totalScheduledTime()
{
     if (!checkScheduledTime()) return 0;

    return  mEndTime->value() - mStartTime->value()
            + 24*(mEndDate->date().dayOfYear()-mStartDate->date().dayOfYear());
}

int ScanTimeConfig::totalOnceTime()
{
    if (!checkOnceTime()) return 0;
    return mTotalTime->value();
}


int ScanTimeConfig::totcalScheduledCount()
{
   return totalScheduledTime() / durationScheduledTime(); // 会整除
}

int ScanTimeConfig::totcalOnceCount()
{
   return totalOnceTime() / durationOnceTime(); // 会整除
}

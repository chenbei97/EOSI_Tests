#ifndef SCANTIMECONFIG_H
#define SCANTIMECONFIG_H

#include "gradienthiddenwidget.h"
#include "qdatetimeedit.h"
#include "qspinbox.h"
#include "qformlayout.h"
#include "qcombobox.h"
#include "qtimer.h"
#include "qmessagebox.h"
#include "qcheckbox.h"
#include "qgroupbox.h"

class ScanTimeConfig : public GradientHiddenWidget
{
    Q_OBJECT
public:
    explicit ScanTimeConfig(QWidget *parent = nullptr);
    QDateTime startScheduledTime();
    QDateTime endScheduledTime();
    int durationScheduledTime();
    int totalScheduledTime();
    int totcalScheduledCount();
    bool checkScheduledTime();
    bool isSchedule() const;

    int totalOnceTime();
    int durationOnceTime();
    int totcalOnceCount();
    bool checkOnceTime();
    bool isOnce() const;
private:
    QCheckBox * mCheckBox;

    QDateEdit * mStartDate; // 计划扫描
    QSpinBox * mStartTime;
    QDateEdit * mEndDate;
    QSpinBox * mEndTime;
    QSpinBox * mDuration;

    QSpinBox * mTotalTime; // 立即扫描
    QSpinBox * mScanTime;

    QLabel * mInfo;
    QTimer timer;

private slots:
    void onTimer();
    void onDateChanged(const QDate&date);
    void onTimeChanged(int time);
    void refreshInfo();
    void onTotalScanChanged();
signals:

};

#endif // SCANTIMECONFIG_H

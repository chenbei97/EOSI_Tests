#ifndef SCANVESSELCONFIG_H
#define SCANVESSELCONFIG_H

#include <QProgressBar>
#include <QMap>
#include <QStackedWidget>
#include <QResizeEvent>
#include "scanconfigdata.h"
#include "scanvesselsummary.h"
#include "scanexperimentconfig.h"

class ScanVesselConfig : public QWidget
{
    Q_OBJECT
public:
    typedef ScanCreateConfig::ScanCreateMode ScanCreateMode;
    typedef ScanTypeConfig::ScanType ScanType;
    typedef ScanSettingConfig::WellsizeOption  WellsizeOption;
    typedef ScanSettingConfig::ChannelOption ChannelOption;
    typedef ScanSettingConfig::ViewOption ViewOption;
    typedef ScanSettingConfig::ObjectiveOption ObjectiveOption;

    explicit ScanVesselConfig(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent*e) override;
private:
    void setProgressBar();
    void addStackedWidgets();
    QHBoxLayout* setButton();
    void onStackChanged(int index);
    void onProgressValue(int value);
    void onNext();
    void onPrevious();
private slots:
    void setCreateMode(ScanCreateMode mode);
    void setScanType(ScanType type);
    void setChannel(ChannelOption option);
    void setObjective(ObjectiveOption option);
    void setView(ViewOption option);
    void setWellsize(WellsizeOption option);
private:
    QProgressBar * mProgressBar;
    QStackedWidget * mStack;
    QPushButton * mNext;
    QPushButton * mPrevious;

    ScanCreateConfig * mCreateConfig;
    ScanTypeConfig * mTypeConfig;
    ScanSettingConfig * mSettingConfig;
    ScanPatternConfig * mPatternConfig;
    ScanPatternPreview * mPatternPreview;
    ScanDescriptionConfig * mDescConfig;
    ScanTimeConfig * mTimeConfig;
    ScanVesselSummary * mSummary;
    ScanExperimentConfig * mExperConfig;
private:
    ScanConfigData data;
signals:

};

#endif // SCANVESSELCONFIG_H

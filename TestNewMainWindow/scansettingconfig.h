#ifndef SCANSETTINGCONFIG_H
#define SCANSETTINGCONFIG_H

#include "gradienthiddenwidget.h"
#include "pattern.h"
#include "qformlayout.h"
#include "qcombobox.h"

class ScanSettingConfig : public GradientHiddenWidget
{
    Q_OBJECT
public:
    enum ChannelOption {BrightChannel,PhaseChannel,RedChannel,GreenChannel,BlueChannel,FluorescenceChannel,EmptyChannel};
    enum ObjectiveOption {Objective4x,Objective10x,Objective10xph,Objective20x,EmptyObjective};
    enum ViewOption {View2,View4,View8,EmptyView};
    enum WellsizeOption {Well2x3,Well4x6,Well8x12,Well16x24,EmptyWellsize};

    explicit ScanSettingConfig(QWidget *parent = nullptr);
private:
    QComboBox * mChannels;
    QComboBox * mObjectives;
    QComboBox * mViews;
    QComboBox * mWells;
    Pattern * mPattern;
signals:
    void channelOption(ChannelOption option);
    void objectiveOption(ObjectiveOption option);
    void viewOption(ViewOption option);
    void wellsizeOption(WellsizeOption option);
};

#endif // SCANSETTINGCONFIG_H

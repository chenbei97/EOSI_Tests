#ifndef SCANVESSELSUMMARY_H
#define SCANVESSELSUMMARY_H

#include "gradienthiddenwidget.h"
#include "scanconfigdata.h"
#include "qjsonobject.h"
#include "qdir.h"

class ScanVesselSummary : public GradientHiddenWidget
{
    Q_OBJECT
public:
    typedef  const QVector<QPoint> QPointList;
    explicit ScanVesselSummary(QWidget *parent = nullptr);
    void translate(const ScanConfigData&d);
    bool saveConfig();
private:
    QString scanType(ScanConfigData::ScanType) const;
    QString scanChannel(ScanConfigData::ChannelOption) const;
    QString scanObjective(ScanConfigData::ObjectiveOption) const;
    QString scanViews(ScanConfigData::ViewOption) const;
    QString scanWellsize(ScanConfigData::WellsizeOption) const;
    QString scanTrajectory(const QPointList&points,const QStringList&names);
    QHBoxLayout * toplay();
private:
    QTextEdit * mPannel;
    QCheckBox * mCheckBox;
    QLineEdit * mNameEdit;
signals:

};

#endif // SCANVESSELSUMMARY_H

#ifndef SCANCONFIGDATA_H
#define SCANCONFIGDATA_H
#include "scancreateconfig.h"
#include "scantypeconfig.h"
#include "scansettingconfig.h"
#include "scanpatternconfig.h"
#include "scanpatternpreview.h"
#include "scandescriptionconfig.h"
#include "scantimeconfig.h"

class ScanConfigData : public QObject
{
    Q_OBJECT
public:
    typedef ScanCreateConfig::ScanCreateMode ScanCreateMode;
    typedef ScanTypeConfig::ScanType ScanType;
    typedef ScanSettingConfig::WellsizeOption  WellsizeOption;
    typedef ScanSettingConfig::ChannelOption ChannelOption;
    typedef ScanSettingConfig::ViewOption ViewOption;
    typedef ScanSettingConfig::ObjectiveOption ObjectiveOption;

    explicit ScanConfigData(QObject *parent = nullptr);
    int progress = 1;
    ScanCreateMode create_mode = ScanCreateMode::EmptyMode;

    ScanType scan_type = ScanType::EmptyType;

    WellsizeOption wellsize = WellsizeOption::EmptyWellsize;
    ChannelOption channel = ChannelOption::EmptyChannel;
    ViewOption view = ViewOption::EmptyView;
    ObjectiveOption objective = ObjectiveOption::EmptyObjective;
    QVector<QPoint> points;

    QString experiment_date;
    QString experiment_name;
    QString experiment_person;
    QString experiment_celltype;
    QString experiment_group;
    QString experiment_description;

    QDateTime scan_start_datetime;
    QDateTime scan_end_datetime;
    int scan_duration_time = 0;
    int scan_total_time = 0;
    int scan_total_count = 0;

    bool scan_is_once = false;
    int scan_once_total_time = 0;
    int scan_once_duration_time = 0;
    int scan_once_total_count = 0;
signals:

};

#endif // SCANCONFIGDATA_H

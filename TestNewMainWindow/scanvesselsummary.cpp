#include "scanvesselsummary.h"


ScanVesselSummary::ScanVesselSummary(QWidget *parent) : GradientHiddenWidget(parent)
{
    mPannel = new QTextEdit;
    mPannel->setReadOnly(true);
    mPannel->setFrameShape(QTextEdit::NoFrame);
    header->setText(tr("实验配置信息总结"));
    mainlay->addLayout(toplay());
    mainlay->addWidget(mPannel);
}

QHBoxLayout* ScanVesselSummary::toplay()
{
    auto lay = new QHBoxLayout;
    mCheckBox = new QCheckBox(tr("是否保存为常用设置?"));
    mCheckBox->setChecked(false);
    mNameEdit = new QLineEdit;
    mNameEdit->setToolTip(tr("请给本配置设定一个名称,方便下次调用"));
    mNameEdit->hide();
    lay->addWidget(mCheckBox);
    lay->addSpacing(10);
    lay->addWidget(mNameEdit);
    lay->addStretch();

    connect(mCheckBox,&QCheckBox::stateChanged,this,[=](int state){
        state==Qt::Checked? mNameEdit->show():mNameEdit->hide();
    });
    return  lay;
}

void ScanVesselSummary::translate(const ScanConfigData &d)
{
    mPannel->clear();
    mPannel->append(tr("扫描类型: %1").arg(scanType(d.scan_type)));
    mPannel->append(tr("成像模式: %1").arg(scanChannel(d.channel)));
    mPannel->append(tr("物镜倍数: %1").arg(scanObjective(d.objective)));
    mPannel->append(tr("视野数量: %1").arg(scanViews(d.view)));
    mPannel->append(tr("孔径尺寸: %1").arg(scanWellsize(d.wellsize)));
    mPannel->append(tr("扫描轨迹: %1").arg(scanTrajectory(d.points,d.names)));
    mPannel->append(tr("实验日期: %1").arg(d.experiment_date.toString("yyyy/MM/dd")));
    mPannel->append(tr("实验人员: %1").arg(d.experiment_person));
    mPannel->append(tr("实验分组: %1").arg(d.experiment_group));
    mPannel->append(tr("实验名称: %1").arg(d.experiment_name));
    mPannel->append(tr("实验细胞: %1").arg(d.experiment_celltype));
    mPannel->append(tr("实验描述: %1").arg(d.experiment_description));
    if (d.scan_is_once) {
        mPannel->append(tr("扫描类型: 立即扫描"));
        mPannel->append(tr("扫描时间: %1 hours").arg(d.scan_once_total_time));
        mPannel->append(tr("间隔时间: %1 hours").arg(d.scan_once_duration_time));
        mPannel->append(tr("扫描次数: %1").arg(d.scan_once_total_count));
    } else {
        mPannel->append(tr("扫描类型: 计划扫描"));
        mPannel->append(tr("开始时间: %1").arg(d.scan_start_datetime.toString("yyyy/MM/dd hh::mm")));
        mPannel->append(tr("结束时间: %1").arg(d.scan_end_datetime.toString("yyyy/MM/dd hh::mm")));
        mPannel->append(tr("扫描时间: %1 hours").arg(d.scan_total_time));
        mPannel->append(tr("间隔时间: %1 hours").arg(d.scan_duration_time));
        mPannel->append(tr("扫描次数: %1").arg(d.scan_total_count));
    }

}

QString ScanVesselSummary::scanType(ScanConfigData::ScanType t) const
{
    typedef ScanConfigData::ScanType ScanType;
    QString type = "";
    switch (t) {
        case ScanType::Standard:type = "Standard";break;
        case ScanType::ImageLock:type = "ImageLock";break;
        case ScanType::ScratchWound:type = "ScratchWound";break;
        case ScanType::WholeWell:type = "WholeWell";break;
        case ScanType::DilutionCloning:type = "DilutionCloning";break;
        case ScanType::Chemotaxis:type = "Chemotaxis";break;
        case ScanType::Spheroid:type = "Spheroid";break;
        case ScanType::NeuronalActivity:type = "NeuronalActivity";break;
        case ScanType::EmptyType:break;
    }
    return type;
}

QString ScanVesselSummary::scanChannel(ScanConfigData::ChannelOption p) const
{
    QString r = "";
    typedef  ScanConfigData::ChannelOption Option;
    switch (p) {
        case Option::BrightChannel : r ="Bright";break;
        case Option::PhaseChannel : r ="Phase";break;
        case Option::RedChannel : r ="Red";break;
        case Option::GreenChannel : r ="Green";break;
        case Option::BlueChannel : r ="Blue";break;
        case Option::FluorescenceChannel : r ="Fluorescence";break;
        default:break;
    }
    return  r;
}

QString ScanVesselSummary::scanObjective(ScanConfigData::ObjectiveOption p) const
{
    QString r = "";
    typedef  ScanConfigData::ObjectiveOption Option;
    switch (p) {
        case Option::Objective4x : r ="4x";break;
        case Option::Objective10x : r ="10x";break;
        case Option::Objective10xph : r ="10xPH";break;
        case Option::Objective20x : r ="20x";break;
        default:break;
    }
    return  r;
}

QString ScanVesselSummary::scanViews(ScanConfigData::ViewOption p) const
{
    QString r = "";
    typedef  ScanConfigData::ViewOption Option;
    switch (p) {
        case Option::View2 : r ="2";break;
        case Option::View4 : r ="4";break;
        case Option::View8 : r ="8";break;
        default:break;
    }
    return  r;
}

QString ScanVesselSummary::scanWellsize(ScanConfigData::WellsizeOption p) const
{
    QString r = "";
    typedef  ScanConfigData::WellsizeOption Option;
    switch (p) {
        case Option::Well2x3 : r ="2x3(6)";break;
        case Option::Well4x6 : r ="4x6(24)";break;
        case Option::Well8x12 : r ="8x12(96)";break;
        case Option::Well16x24 : r ="16x24(384)";break;
        default:break;
    }
    return  r;
}

QString ScanVesselSummary::scanTrajectory(const QPointList&points,const QStringList&names)
{
    Q_ASSERT(points.count() == names.count());
    QString r;
    for(int i = 0;i < points.count(); ++i) {
        auto point = points[i];
        auto x = (QChar)(point.x()+65);
        QString tmp(tr("[%1,%2,'%3']->").arg(x).arg(point.y()).arg(names[i]));
        r += tmp;
    }
    r.chop(2);
    return r;
}

bool ScanVesselSummary::saveConfig()
{
    if (!mCheckBox->isChecked())
        return true;
    auto name = mNameEdit->text().simplified();
    if (name.isEmpty()) {
        QMessageBox::warning(this,tr("警告"),tr("请给要保存的配置命名!"));
        return false;
    }
    // 下方将所有配置写入json文件
    return true;
}

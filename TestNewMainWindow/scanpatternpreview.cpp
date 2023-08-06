#include "scanpatternpreview.h"

ScanPatternPreview::ScanPatternPreview(QWidget *parent) : GradientHiddenWidget(parent)
{
    mPattern = new Pattern;
    mPattern->toggleState(Pattern::MoveState);
    mPointLocInfo = new QLabel(tr("当前位置: "));
    mPointNameInfo = new QLabel(tr("当前名称: "));
    mPointOrderInfo = new QLabel(tr("当前次序: "));
    mViewsCountInfo = new QLabel(tr("视野数量: "));
    mPointAllInfo = new QLabel(tr("全部信息: "));
    mPointAllInfo->setWordWrap(true);
    mPreviewBtn = new QPushButton(tr("预览"));

    auto box = new QGroupBox;
    auto boxlay = new QVBoxLayout;
    boxlay->addWidget(mPattern);
    boxlay->addSpacing(10);
    boxlay->addWidget(mPreviewBtn);
    boxlay->addSpacing(15);
    boxlay->addWidget(mPointLocInfo);
    boxlay->addSpacing(15);
    boxlay->addWidget(mPointNameInfo);
    boxlay->addSpacing(15);
    boxlay->addWidget(mPointOrderInfo);
    boxlay->addSpacing(15);
    boxlay->addWidget(mViewsCountInfo);
    boxlay->addSpacing(15);
    boxlay->addWidget(mPointAllInfo);
    box->setLayout(boxlay);


    header->setText(tr("预览成像轨迹"));
    mainlay->addWidget(box);
    connect(mPreviewBtn,&QPushButton::clicked,this,&ScanPatternPreview::onPreviewBtn);
}

void ScanPatternPreview::onPreviewBtn()
{
    Q_ASSERT(mSortNames.count() == mSortNames.count());
    QString all;
    for(int i = 0; i < mSortPoints.count(); ++i){
        auto p = mSortPoints[i];
        auto x = (QChar)(p.x()+65);
        all.append(tr("[%1,%2,%3] ").arg(x).arg(p.y()+1).arg(mSortNames[i]));
        QTimer::singleShot(i*1500,mPattern,[=]{
            mPattern->setSignedPoint(mSortPoints[i]);
            mPointLocInfo->setText(tr("当前位置: [%1,%2]").arg(x).arg(p.y()+1));
            mPointNameInfo->setText(tr("当前名称: %1").arg(mSortNames[i]));
            mPointOrderInfo->setText(tr("当前次序: %1").arg(i+1));
        });
    }
    mPointAllInfo->setText(tr("全部信息: %1").arg(all));
}

void ScanPatternPreview::setPatternSize(int rows, int cols)
{
    mPattern->setPatternSize(rows,cols);
}

void ScanPatternPreview::setViews(int count)
{
    mViews = count;
    mPattern->drawRandomPoints(mViews);
    mViewsCountInfo->setText(tr("视野数量: %1").arg(mViews));
}

void ScanPatternPreview::setSortNames(const QStringList &names)
{
    mSortNames = names;
    Q_ASSERT(mSortNames.count() >=1);
    mPointNameInfo->setText(tr("当前名称: %1").arg(mSortNames[0]));
}

void ScanPatternPreview::setSortPoints(const QVector<QPoint> &points)
{
    mSortPoints = points;
    mPattern->setSelectedPoints(points);
    Q_ASSERT(mSortPoints.count() >=1);
    auto p = points[0];
    mPointLocInfo->setText(tr("当前位置: [%1,%2]").arg((QChar)(p.x()+65)).arg(p.y()+1));
    mPointOrderInfo->setText(tr("当前次序: %1").arg(1));
}

void ScanPatternPreview::clearPointsNames()
{
    mSortNames.clear();
    mSortPoints.clear(); // 清除私有变量
    mPattern->clearAllPoints(); // 清除轨迹选中的所有点
    mPattern->clearMousePoint(); // 清除鼠标选的点
    mPattern->clearSignedPoint(); // 清除移动标记过的点
}


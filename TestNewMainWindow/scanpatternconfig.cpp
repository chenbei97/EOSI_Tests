#include "scanpatternconfig.h"

ScanPatternConfig::ScanPatternConfig(QWidget *parent) : GradientHiddenWidget(parent)
{
        mPattern = new Pattern;
        mPatternList = new QListWidget;
        mPatternList->setSelectionMode(QListWidget::MultiSelection);
        mPatternList->setSelectionBehavior(QListWidget::SelectRows);
        mPatternList->setEditTriggers(QListWidget::DoubleClicked);

        mPattern->toggleState(Pattern::TickState);
        mPattern->setPatternSize(2,3);


        mTreatNameLabel = new QLabel(tr("孔名称: "));
        mTreatNameLabel->setAlignment(Qt::AlignRight);
        mTreatNameEdit = new QLineEdit;
        mAddTreatBtn = new QPushButton(tr("添加"));
        mRemoveBtn = new QPushButton(tr("移除"));
        mRemoveAllBtn = new QPushButton(tr("移除全部"));

        // 添加,实验名称的水平布局
        auto play = new QHBoxLayout;
        play->addWidget(mTreatNameLabel);
        play->addWidget(mTreatNameEdit);
        play->addStretch();

        // 移除和移除全部的水平布局
        auto pblay = new QHBoxLayout;
        pblay->addWidget(mAddTreatBtn);
        pblay->addSpacing(100);
        pblay->addWidget(mRemoveAllBtn);
        pblay->addSpacing(100);
        pblay->addWidget(mRemoveBtn);
        pblay->addStretch();

        // 图案+2个水平布局+listwidget的水平布局
        auto patternlay = new QVBoxLayout;
        patternlay->addWidget(mPattern);
        patternlay->addLayout(play);
        patternlay->addLayout(pblay);
        patternlay->addSpacing(10);
        patternlay->addWidget(mPatternList);

        mPatternBox = new QGroupBox;
        mPatternBox->setTitle(tr("实验设置"));
        mPatternBox->setLayout(patternlay);

        header->setText(tr("选择成像轨迹"));
        mainlay->addWidget(mPatternBox);

        connect(mAddTreatBtn,&QPushButton::clicked,this,&ScanPatternConfig::onAddTreat);
        connect(mRemoveBtn,&QPushButton::clicked,this,&ScanPatternConfig::onRemoveTreat);
        connect(mRemoveAllBtn,&QPushButton::clicked,this,&ScanPatternConfig::onRemoveAllTreat);
}

void ScanPatternConfig::onAddTreat()
{
    auto name = mTreatNameEdit->text().simplified();
    if (name.isEmpty()){
        QMessageBox::critical(this,tr("错误"),tr("名称不应为空!"));
        return;
    }
    if (!mPatternList->findItems(name,Qt::MatchCaseSensitive).isEmpty()){
        QMessageBox::critical(this,tr("错误"),tr("不允许重名!"));
        return;
    }

    auto point = mPattern->currentMousePoint();
    if ( point.x()<0 || point.y() <0)
    {
        QMessageBox::critical(this,tr("错误"),tr("没有选择一个区域"));
        return;
    }
    auto points = mPattern->selectedPoints();
    if (points.contains(point))
    {
        QMessageBox::critical(this,tr("错误"),tr("不能选择重复的区域"));
        return;
    }

    mPattern->setSelectedPoint(point);

    QListWidgetItem * item = new QListWidgetItem;
    item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable);
    item->setText(name);
    item->setData(Qt::UserRole+1,point); // 存储选中的位置信息

    mPatternList->addItem(item);
    mSortSelectedPoints.append(point);
}

void ScanPatternConfig::onRemoveTreat()
{

//    auto indexs = mPatternList->selectionModel()->selectedIndexes();
//    LOG<<"selected items = "<<indexs;
//    QListWidgetItem * item;
//    foreach (auto index, indexs)
//    {
//        item = mPatternList->takeItem(index.row()); // 不要用takeIem,因为take之后行数发生了变化,再用之前的indexs可能就返回nullptr
//        LOG<< "item = "<<item;
//        auto point = item->data(Qt::UserRole+1).toPoint();
//        LOG<<"point = "<<point;
//        mPattern->setSelectedRect(point.x(),point.y(),false);
//        delete item;
//    }
        auto items = mPatternList->selectedItems();
        foreach(auto item,items)
        {
            auto point = item->data(Qt::UserRole+1).toPoint();
            mPattern->setSelectedPoint(point.x(),point.y(),false); // 根据位置信息取消被选中的位置
            auto index = mSortSelectedPoints.indexOf(point);
            mSortSelectedPoints.remove(index);
            delete item;
        }

}

void ScanPatternConfig::onRemoveAllTreat()
{
    mPatternList->clear();
    mSortSelectedPoints.clear();
    mPattern->clearAllPoints();
}


void ScanPatternConfig::setPatternSize(int rows, int cols)
{
    mPattern->setPatternSize(rows,cols);
}


QVector<QPoint> ScanPatternConfig::sortSelectedPoints() const
{
    return mSortSelectedPoints;
}

QStringList ScanPatternConfig::sortNames() const
{
    QStringList names;
    for(int i = 0; i< mPatternList->count(); ++i)
        names.append(mPatternList->item(i)->text());
    return names;
}

void ScanPatternConfig::clearPointsNames()
{
    mSortSelectedPoints.clear(); //  清除私有变量
    mPattern->clearMousePoint();// 轨迹选中的点
    mPattern->clearAllPoints();// 图案清除鼠标选中的点
    mPatternList->clear(); // 清除UI的列表显示
    mTreatNameEdit->clear();// 当前存在的命名
}

#include "tableview.h"
#include <QSpinBox>
#include "tableviewwidget2x2.h"

TableView::TableView(QWidget *parent) :QTableView(parent)
{
    initGeneralConfig();
    INIT_FONT;

    connect(this,&TableView::clicked,this,&TableView::onClicked);
    connect(this,&TableView::doubleClicked,this,&TableView::onDoubleClicked);
    connect(this,&TableView::pressed,this,&TableView::onPressed);
}

void TableView::initGeneralConfig()
{
    setSelectionBehavior(QAbstractItemView::SelectItems);//选中时只选中1个项
    setSelectionMode(QAbstractItemView::SingleSelection); // 选择项只能选中1个,再点另一个会取消选中之前的
    setEditTriggers(QTableView::NoEditTriggers);

    setShowGrid(true);
    setGridStyle(Qt::DashLine);
    setWordWrap(false);//取消自动换行
    setSortingEnabled(false); // 不启用排序
    setCornerButtonEnabled(false);
    setTabKeyNavigation(true);
    setAlternatingRowColors(false);
    setDragEnabled(false);
    setAcceptDrops(false);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel); // 按像素或者按项进行滚动
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);// 取消滚动条
    setTextElideMode(Qt::ElideNone); //防止文本超过宽度出现省略号

    //verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setHighlightSections(true);//选中一列表头是否加粗,选false就不能连续选中表头
    verticalHeader()->setStretchLastSection(false);//最后一列拉伸填充,设为false,否则2×2的格子就显示2列了
    //verticalHeader()->setMinimumSectionSize(TableWidgetItemMinWidth);//列标题最大高度
    //verticalHeader()->setDefaultSectionSize(TableWidgetItemMinWidth);//默认列宽

    //horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    horizontalHeader()->setHighlightSections(true);
    horizontalHeader()->setStretchLastSection(false);
//    horizontalHeader()->setMinimumSectionSize(TableWidgetItemMinWidth);
//    horizontalHeader()->setDefaultSectionSize(TableWidgetItemHeight);

}

void TableView::updateCellSize()
{
    if (model())
    {
        for(int r = 0; r <model()->rowCount(); ++ r)
            setRowHeight(r,TableViewRowHeight);

        for(int c = 0; c <model()->columnCount(); ++ c)
            setColumnWidth(c,TableViewColumnWidth);

//        for(int r = 0; r <model()->rowCount(); ++ r)
//             for(int c = 0; c <model()->columnCount(); ++ c)
//                 openPersistentEditor(model()->index(r,c));
    }
}

void TableView::updateGeometries()
{
    //LOG<<"is called";
    return QTableView::updateGeometries();
}

void TableView::rowsInserted(const QModelIndex &parent, int start, int end)
{

}

bool TableView::edit(const QModelIndex &index, QAbstractItemView::EditTrigger trigger, QEvent *event)
{
    setCurrentIndex(index);
    //LOG<<"edit index = "<<index<<" trigger = "<<trigger <<" event = "<<event;
    //openPersistentEditor(index);
//event->type();
  //  event->accept();

//    if (event->type() == QEvent::MouseButtonDblClick)
//    {
////        LOG<<"edit mouse clicked";
//    }
    return QTableView::edit(index,trigger,event);
//    return true;
}

void TableView::onClicked(const QModelIndex&index)
{
    //LOG<<"clicked";
}

void TableView::onDoubleClicked(const QModelIndex&index)
{
//    setIndexWidget(index,new TableViewWidget2x2);
//    openPersistentEditor(index);

    auto d = index.model()->data(index,Qt::DecorationRole);
    if (d.isValid())
    {
        auto w = new TableViewWidget2x2;
       auto dd = d .value<QVector<QPixmap*>>();
       w->setAttribute(Qt::WA_DeleteOnClose);
       w->setPixmaps(dd);
       w->show();
    }


    //LOG<<"double clicked "<< indexWidget(index);
}

void TableView::onPressed(const QModelIndex&index)
{
    //LOG<<"pressed";
}

//void TableView::openPersistentEditor(const QModelIndex &index)
//{
//    auto widget = itemDelegate(index);

//}





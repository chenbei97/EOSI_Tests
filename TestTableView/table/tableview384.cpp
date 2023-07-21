#include "tableview384.h"

TableView384::TableView384(QWidget *parent) : QWidget(parent)
{
    mView = new TableView;
    mDelegate = new TableViewDelegate2x2;
    mModel = new TableModel(mView);
    mModel->setItemCount(8,12);
    mSelection = new QItemSelectionModel(mModel);

    mView->setItemDelegate(mDelegate);
    mView->setModel(mModel);
    mView->setSelectionModel(mSelection);

    mView->updateCellSize();

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->setMargin(0);
    lay->setSpacing(0);

    lay->addWidget(mView);
    resize(mView->size());

    connect(this,&TableView384::currentItemChanged,this,&TableView384::onCurrentItemChanged);

    INIT_FONT;
}

bool TableView384::setPixmaps(int row,int col, const QVector<QPixmap*>& pixs)
{
    QVariant v;
    v.setValue(pixs);
    return mModel->setData(index(row,col),v,Qt::DecorationRole);
}

bool TableView384::setSelectedItems(int row, int col, uint32_t info)
{
    if (info < 0 || info > 15)  // 枚举值的范围0b0000-0b1111
        return false;
    return mModel->setData(index(row,col),info,TableModelDataRole::SelectedItems);
}

bool TableView384::setCurrentItem(int row,int col,uint32_t info)
{// 设置当前项
    if (info != 0 && info != 0b1000 && info != 0b0100 && info != 0b0010 && info != 0b0001)
        return false;

    bool r =  mModel->setData(index(row,col),info,TableModelDataRole::CurrentItem);
    if (r) emit currentItemChanged(row,col); // 当前项只能有1个

    return r;
}


void TableView384::onCurrentItemChanged(int row,int col)
{ // 一旦当前项改变,其它所有单元格包括子单元格的CurrentItem都要置零
    for (int r = 0; r <mModel->rowCount(); ++r ){
        for (int c= 0; c < mModel->columnCount(); ++c){
            if (r == row && c == col )
                continue;
            mModel->setData(index(r,c),0,TableModelDataRole::CurrentItem);
            //LOG<<"row = "<<row<<" col = "<<col;
        }
    }
}

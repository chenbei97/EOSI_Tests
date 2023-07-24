#include "table.h"

Table::Table(QWidget *parent) : QWidget(parent)
{

    mView = new TableView;
    mDelegate = new TableViewDelegateLabel;
    mModel = new QStandardItemModel(mView);
    mSelection = new QItemSelectionModel(mModel);

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->setMargin(0);
    lay->setSpacing(0);
    lay->addWidget(mView);

    mView->setItemDelegate(mDelegate);
    mView->setModel(mModel);
    mView->setSelectionModel(mSelection);

    connect(this,&Table::currentItemChanged,this,&Table::onCurrentItemChanged);
    resize(mView->size());
    INIT_FONT;
}

Table::Table(int rows,int cols,QWidget *parent) : QWidget(parent)
{

    mView = new TableView;
    mDelegate = new TableViewDelegateLabel;
    mModel = new QStandardItemModel(mView);
    mSelection = new QItemSelectionModel(mModel);

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->setMargin(0);
    lay->setSpacing(0);
    lay->addWidget(mView);

    mModel->setRowCount(rows);
    mModel->setColumnCount(cols);
    mView->setItemDelegate(mDelegate);
    mView->setModel(mModel);
    mView->setSelectionModel(mSelection);
    mView->updateCellSize();

    connect(this,&Table::currentItemChanged,this,&Table::onCurrentItemChanged);
    resize(mView->size());
    INIT_FONT;
}

 void Table::setItemCount(int rows,int cols)
 {
     mModel->setRowCount(rows);
     mModel->setColumnCount(cols);
     mView->updateCellSize();
 }

 void Table::setDelegate(QStyledItemDelegate *delegate)
 {
    delete  mDelegate;
    mDelegate = delegate;
     mView->setItemDelegate(delegate);
 }


QVariant Table::data(const QModelIndex &index, int role) const
{
    if (!mModel) return QVariant();
    return mModel->data(index,role);
}

QVariant Table::data(int row, int col, int role) const
{
    if (!mModel) return QVariant();
    return mModel->data(index(row,col),role);
};

bool Table::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mModel) return false;
    return mModel->setData(index,value,role);
};

bool Table::setData(int row, int col, const QVariant &value, int role)
 {
    if (!mModel) return false;
    return mModel->setData(index(row,col),value,role);
};

bool Table::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    if (!mModel) return false;
    return mModel->setItemData(index,roles);
};

bool Table::setItemData(int row, int col, const QMap<int, QVariant> &roles)
{
    if (!mModel) return false;
    return mModel->setItemData(index(row,col),roles);
};

QMap<int,QVariant> Table::itemData(const QModelIndex &index) const
{
    if (!mModel) return QMap<int,QVariant>();
    return mModel->itemData(index);
};

QMap<int,QVariant> Table::itemData(int row, int col) const
{
    if (!mModel) return QMap<int,QVariant>();
    return mModel->itemData(index(row,col));
};

QModelIndex Table::index(int row, int col) const
{
    if (!mModel) return QModelIndex();
    return mModel->index(row,col);
}

bool Table::setPixmap(int row,int col,QPixmap*pix)
{
    return mModel->setData(index(row,col),*pix,Qt::DecorationRole);
}

bool Table::setPixmap(int row,int col,const QPixmap&pix)
{
    return setPixmap(row,col,new QPixmap(pix));
}


QPixmap* Table::pixmap(int row,int col) const
{
    auto pix = mModel->data(index(row,col),Qt::DecorationRole).value<QPixmap>();
    return new QPixmap(pix);
}

bool Table::setSelectedItem(int row, int col,bool isSelected)
{
    return mModel->setData(index(row,col),isSelected,TableModelDataRole::isSelected);
}

bool Table::setCurrentItem(int row,int col,bool isCurrent)
{// 设置当前项
    bool r =  mModel->setData(index(row,col),isCurrent,TableModelDataRole::isCurrent);
    if (r) emit currentItemChanged(row,col); // 当前项只能有1个

    return r;
}

void Table::onCurrentItemChanged(int row,int col)
{ // 一旦当前项改变,其它所有单元格包括子单元格的isCurrent都要置false
    if (mModel)
    {
        for (int r = 0; r <mModel->rowCount(); ++r ){
            for (int c= 0; c < mModel->columnCount(); ++c){
                if (r == row && c == col )
                    continue;
                mModel->setData(index(r,c),false,TableModelDataRole::isCurrent);
                mModel->setData(index(r,c),false,TableModelDataRole::CurrentItem);

            }
        }
    }
}


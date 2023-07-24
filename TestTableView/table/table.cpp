#include "table.h"

Table::Table(QWidget *parent) : QWidget(parent)
{
    mView = new TableView;
    mDelegate = nullptr;
    mModel = nullptr;
    mSelection = nullptr;

    initialize();

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->setMargin(0);
    lay->setSpacing(0);

    lay->addWidget(mView);
    resize(mView->size());

    connect(this,&Table::currentItemChanged,this,&Table::onCurrentItemChanged);

    INIT_FONT;
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
            }
        }
    }
}


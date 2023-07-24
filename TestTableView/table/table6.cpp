#include "table6.h"

Table6::Table6(QWidget *parent) : Table(parent)
{

}

void Table6::initialize()
{
    mDelegate = new TableViewDelegateLabel;
    mModel = new QStandardItemModel(mView);
    auto model = static_cast<QStandardItemModel*>(mModel);
    model->setRowCount(2);
    model->setColumnCount(3);
    mModel = model;
    mView->setItemDelegate(mDelegate);
    mView->setModel(mModel);
}

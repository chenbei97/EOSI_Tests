#ifndef TABLEVIEW384_H
#define TABLEVIEW384_H

#include <qlayout.h>
#include <qitemselectionmodel.h>
#include "tableview.h"
#include "tablemodel.h"
#include "tableviewdelegate2x2.h"


class TableView384 : public QWidget
{
    Q_OBJECT
    TableViewDelegate2x2 * mDelegate;
    TableModel * mModel;
    TableView * mView;
    QItemSelectionModel * mSelection;
public:
    explicit TableView384(QWidget *parent = nullptr);

    inline QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {return mModel->data(index,role);};
    inline QVariant data(int row,int col, int role = Qt::DisplayRole) const
    {return mModel->data(index(row,col),role);};
    inline bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
    {return mModel->setData(index,value,role);};
    inline bool setData(int row,int col, const QVariant &value, int role = Qt::EditRole)
    {return mModel->setData(index(row,col),value,role);};

    inline bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
    {return mModel->setItemData(index,roles);};
    inline bool setItemData(int row,int col, const QMap<int, QVariant> &roles)
    {return mModel->setItemData(index(row,col),roles);};
    inline QMap<int, QVariant>	itemData(const QModelIndex &index) const
    {return mModel->itemData(index);};
    inline QMap<int, QVariant>	itemData(int row,int col) const
    {return mModel->itemData(index(row,col));};

    inline QModelIndex index(int row,int col) const
    {return mModel->index(row,col);}

    /*定义一些常用的快捷函数*/
    bool setPixmaps(int row,int col, const QVector<QPixmap*> &pixs);
    bool setCurrentItem(int row,int col,uint32_t info);
    bool setSelectedItems(int row,int col, uint32_t info);

signals:
    void currentItemChanged(int row,int col);

private slots:
    void onCurrentItemChanged(int row,int col);
};

#endif // TABLEVIEW384_H

#ifndef TABLE_H
#define TABLE_H

#include <qstandarditemmodel.h>
#include "tableviewdelegatelabel.h"
#include "tableview.h"

class Table : public QWidget
{
    Q_OBJECT
protected:
    QStyledItemDelegate * mDelegate;
    QAbstractItemModel * mModel;
    TableView * mView;
    QItemSelectionModel * mSelection;
public:
    explicit Table(QWidget *parent = nullptr);

    virtual void initialize() {};

    virtual inline QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {return mModel->data(index,role);};
    virtual inline QVariant data(int row,int col, int role = Qt::DisplayRole) const
    {return mModel->data(index(row,col),role);};
    virtual inline bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
    { return mModel->setData(index,value,role);};
    virtual inline bool setData(int row,int col, const QVariant &value, int role = Qt::EditRole)
    {return mModel->setData(index(row,col),value,role);};

    virtual inline bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
    {return mModel->setItemData(index,roles);};
    virtual inline bool setItemData(int row,int col, const QMap<int, QVariant> &roles)
    {return mModel->setItemData(index(row,col),roles);};
    virtual inline QMap<int, QVariant>	itemData(const QModelIndex &index) const
    {return mModel->itemData(index);};
    virtual inline QMap<int, QVariant>	itemData(int row,int col) const
    {return mModel->itemData(index(row,col));};

    inline QModelIndex index(int row,int col) const
    {return mModel->index(row,col);}

    /*定义一些常用的快捷函数*/
    bool setPixmap(int row,int col,QPixmap*pix);
    bool setPixmap(int row,int col,const QPixmap&pix);
    QPixmap* pixmap(int row,int col) const;

    bool setCurrentItem(int row,int col,bool isCurrent = true);
    bool setSelectedItem(int row,int col, bool isSelected = true);

signals:
    void currentItemChanged(int row,int col);

protected slots:
    void onCurrentItemChanged(int row,int col);

};

#endif // TABLE_H

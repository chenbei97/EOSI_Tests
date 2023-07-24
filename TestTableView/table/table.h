#ifndef TABLE_H
#define TABLE_H

#include <qstandarditemmodel.h>
#include "tableviewdelegatelabel.h"
#include "tableview.h"

class Table : public QWidget
{
    Q_OBJECT
protected:
    TableView * mView;
    QItemSelectionModel * mSelection;
    QStandardItemModel * mModel;
    QStyledItemDelegate  * mDelegate;
    void setItemCount(int rows,int cols);
    void setDelegate(QStyledItemDelegate*delegate);
public:
    explicit Table(QWidget *parent = nullptr);
    explicit Table(int rows,int cols,QWidget *parent = nullptr);


    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant data(int row,int col, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    virtual bool setData(int row,int col, const QVariant &value, int role = Qt::EditRole);

    virtual  bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);
    virtual  bool setItemData(int row,int col, const QMap<int, QVariant> &roles);

    virtual  QMap<int, QVariant>	itemData(const QModelIndex &index) const;
    virtual  QMap<int, QVariant>	itemData(int row,int col) const;


     QModelIndex index(int row,int col) const;


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

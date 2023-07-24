#ifndef TABLE_384_H
#define TABLE_384_H


#include "table.h"
#include "tableviewdelegate2x2.h"

class Table_384 : public Table
{
    Q_OBJECT
public:
    explicit Table_384(QWidget *parent = nullptr);

    inline bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)  override// 不要使用setData来设置而应该使用下方的setPixmap
    {if (role == Qt::DecorationRole) return false; return mModel->setData(index,value,role);}; // 这里设置无法保证数量一定是4还不知道位置信息,会出现越界问题
    inline bool setData(int row,int col, const QVariant &value, int role = Qt::EditRole) override
    {if (role == Qt::DecorationRole) return false;return mModel->setData(index(row,col),value,role);};

    inline bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)  override//setItemData同理
    {if (roles.keys().contains(Qt::DecorationRole)) return false; return mModel->setItemData(index,roles);};
    inline bool setItemData(int row,int col, const QMap<int, QVariant> &roles) override
    {if (roles.keys().contains(Qt::DecorationRole)) return false;return mModel->setItemData(index(row,col),roles);};

    /*定义一些常用的快捷函数*/
       bool setCurrentItem(int row,int col,bool isCurrent= true) = delete ;
       bool setSelectedItem(int row,int col, bool isSelected = true) = delete ;
       bool setPixmap(int row,int col,QPixmap*pix) = delete;
       bool setPixmap(int row,int col,const QPixmap&pix) = delete;
       QPixmap* pixmap(int row,int col) const = delete;


        bool setPixmap(int row,int col,int pos,QPixmap*pix);
        bool setPixmap(int row,int col,int pos,const QPixmap&pix);
        bool setPixmaps(int row,int col, const QVector<QPixmap*> &pixs);
        bool setPixmaps(int row,int col, const QVector<QPair<int,QPixmap*>> &pixs);
        QVector<QPixmap*> pixmaps(int row,int col) const;
        QPixmap* pixmap(int row,int col,int pos) const;

        bool setCurrent(int row,int col,uint32_t info);
        bool setSelected(int row,int col, uint32_t info);
};

#endif // TABLE_384_H

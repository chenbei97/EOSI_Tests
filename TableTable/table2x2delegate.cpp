#include "table2x2delegate.h"

Table2x2Delegate::Table2x2Delegate(QObject *parent):QStyledItemDelegate(parent)
{

}


QWidget *Table2x2Delegate::createEditor(QWidget *parent,
       const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto editor = new TableWidgetBase(2,2,parent);

    /*增加事先初始化代理组件的item的代码*/
//    QTableWidgetItem * item;

//    item = new QTableWidgetItem(QString::number(qrand()%101));
//    item->setIcon(QIcon(":/1.jpg"));
//    item->setData(Qt::DecorationRole,":/1.jpg");
//    editor->setItem(0,0,item);

//    item = new QTableWidgetItem(QString::number(qrand()%101));
//    item->setIcon(QIcon(":/2.jpg"));
//    item->setData(Qt::DecorationRole,":/2.jpg");
//    editor->setItem(0,1,item);

//    item = new QTableWidgetItem(QString::number(qrand()%101));
//    item->setIcon(QIcon(":/3.jpg"));
//    item->setData(Qt::DecorationRole,":/3.jpg");
//    editor->setItem(1,0,item);

//    item = new QTableWidgetItem(QString::number(qrand()%101));
//    item->setIcon(QIcon(":/4.jpg"));
//    item->setData(Qt::DecorationRole,":/4.jpg");
//    editor->setItem(1,1,item);

    return editor;
}

void Table2x2Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    TableWidgetBase *cell = static_cast<TableWidgetBase*>(editor); // 2x2

    QStringList texts;
    texts<< cell->item(0,0)->text()<<cell->item(0,1)->text()<<cell->item(1,0)->text()<<cell->item(1,1)->text();
    qDebug()<<"texts = "<<texts;

    QStringList icons;
    icons<<cell->item(0,0)->data(Qt::DecorationRole).toString()<<cell->item(0,1)->data(Qt::DecorationRole).toString()
        <<cell->item(1,0)->data(Qt::DecorationRole).toString()<<cell->item(1,1)->data(Qt::DecorationRole).toString();

    QList<QIcon> imgs; // 实际不能传递只能用QStringList  icons
    imgs<<cell->item(0,0)->icon()<<cell->item(0,1)->icon()
       <<cell->item(1,0)->icon()<<cell->item(1,1)->icon();

    model->setData(index, texts, Qt::EditRole);
    model->setData(index, icons, Qt::DecorationRole);
    //model->setData(index, imgs, Qt::DecorationRole);
    // 不能直接传递QIcon,所以才在createEditor通过setData传递图片路径,是曲线救国的方法
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
    model->setData(index, QBrush(Qt::white), Qt::BackgroundColorRole);
    model->setData(index, QBrush(Qt::red), Qt::TextColorRole);
}

void Table2x2Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QStringList texts = index.model()->data(index, Qt::EditRole).toStringList();
    qDebug()<<"texts = "<<texts;
    auto icons = index.model()->data(index, Qt::DecorationRole).toStringList();
    qDebug()<<"icons = "<<icons;

    TableWidgetBase *cell = static_cast<TableWidgetBase*>(editor); // 2x2

    auto item11 = cell->takeItem(0,0);
    auto item12 = cell->takeItem(0,1);
    auto item21 = cell->takeItem(1,0);
    auto item22 = cell->takeItem(1,1);

    if (texts.count() !=4)
    {
        item11->setText("-11");
        item12->setText("-12");
        item21->setText("-21");
        item22->setText("-22");
    }
    else {
        item11->setText(texts[0]+"-11");
        item12->setText(texts[1]+"-12");
        item21->setText(texts[2]+"-21");
        item22->setText(texts[3]+"-22");
    }

    if (icons.count() == 4){
        item11->setIcon(QIcon(icons[0]));
        item12->setIcon(QIcon(icons[1]));
        item21->setIcon(QIcon(icons[2]));
        item22->setIcon(QIcon(icons[3]));

        item11->setData(Qt::DecorationRole,icons[0]);
        item12->setData(Qt::DecorationRole,icons[1]);
        item21->setData(Qt::DecorationRole,icons[2]);
        item22->setData(Qt::DecorationRole,icons[3]);
    }

    cell->setItem(0,0,item11);
    cell->setItem(0,1,item12);
    cell->setItem(1,0,item21);
    cell->setItem(1,1,item22);
}




void Table2x2Delegate::updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

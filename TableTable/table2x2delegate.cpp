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

    return editor;
}

void Table2x2Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QStringList str = index.model()->data(index, Qt::EditRole).toStringList();
    qDebug()<<"strs = "<<str;
    auto icons = index.model()->data(index, Qt::DecorationRole).toStringList();
    qDebug()<<"icons = "<<icons;

    TableWidgetBase *cell = static_cast<TableWidgetBase*>(editor);

    auto item11 = cell->takeItem(0,0);
    auto item12 = cell->takeItem(0,1);
    auto item21 = cell->takeItem(1,0);
    auto item22 = cell->takeItem(1,1);
    if (str.count() !=4)
    {
        item11->setText("-11");
        item12->setText("-12");
        item21->setText("-21");
        item22->setText("-22");
    }
    else {
        item11->setText(str[0]+"-11");
        item12->setText(str[1]+"-12");
        item21->setText(str[2]+"-21");
        item22->setText(str[3]+"-22");
    }

    if (icons.count() == 4){
        item11->setIcon(QIcon(icons[0]));
        item12->setIcon(QIcon(icons[1]));
        item21->setIcon(QIcon(icons[2]));
        item22->setIcon(QIcon(icons[3]));
    }

    cell->setItem(0,0,item11);
    cell->setItem(0,1,item12);
    cell->setItem(1,0,item21);
    cell->setItem(1,1,item22);
}

void Table2x2Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    TableWidgetBase *cell = static_cast<TableWidgetBase*>(editor);

    // 传递数据也是可行的
    QStringList texts;
    texts<< cell->item(0,0)->text()<<cell->item(0,1)->text()<<cell->item(1,0)->text()<<cell->item(1,1)->text();

    qDebug()<<"texts = "<<texts;
    QStringList icons;
    icons<<":/1.jpg"<<":/2.jpg"<<":/3.jpg"<<":/4.jpg";

//    icons << cell->item(0,0)->icon().pixmap(QSize(32,32))<< cell->item(0,1)->icon().pixmap(QSize(32,32))
//          << cell->item(1,0)->icon().pixmap(QSize(32,32))<< cell->item(1,1)->icon().pixmap(QSize(32,32));

//    QList<int> aligns;
//    aligns << cell->item(0,0)->textAlignment()<< cell->item(0,1)->textAlignment()
//           << cell->item(1,0)->textAlignment()<< cell->item(1,1)->textAlignment();
//    cell->item(0,0)->textColor();
//    cell->item(0,0)->backgroundColor();

    model->setData(index, texts, Qt::EditRole);
    model->setData(index, icons, Qt::DecorationRole);
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
    model->setData(index, QBrush(Qt::white), Qt::BackgroundColorRole);
    model->setData(index, QBrush(Qt::red), Qt::TextColorRole);
}

void Table2x2Delegate::updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

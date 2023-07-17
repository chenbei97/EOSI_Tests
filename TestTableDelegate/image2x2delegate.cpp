#include "image2x2delegate.h"


QWidget *Image2x2Delegate::createEditor(QWidget *parent,
       const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto editor = new Image2x2Widget;
    //editor->installEventFilter(const_cast<Image2x2Delegate*>(this));
    return editor;
}

void Image2x2Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    auto icons = index.model()->data(index, Qt::DecorationRole).toStringList();
    qDebug()<<"icons = "<<icons;

    Image2x2Widget *cell = static_cast<Image2x2Widget*>(editor);
    if (icons.count() == 4){
//        cell->setPixmap(0,QPixmap(icons[0]));
//        cell->setPixmap(1,QPixmap(icons[1]));
//        cell->setPixmap(2,QPixmap(icons[2]));
//        cell->setPixmap(3,QPixmap(icons[3]));
        cell->setPixmap(0,icons[0]); // 传递字符串最好
        cell->setPixmap(1,icons[1]);
        cell->setPixmap(2,icons[2]);
        cell->setPixmap(3,icons[3]);
    }
}

void Image2x2Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    Image2x2Widget *cell = static_cast<Image2x2Widget*>(editor);


    //QStringList texts;

    //model->setData(index, texts, Qt::EditRole);
    model->setData(index, cell->pixmapNames(), Qt::DecorationRole); //拿到图标的名称
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
    model->setData(index, QBrush(Qt::white), Qt::BackgroundColorRole);
    model->setData(index, QBrush(Qt::red), Qt::TextColorRole);
}

void Image2x2Delegate::updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

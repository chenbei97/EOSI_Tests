#include "image2x2delegate.h"
#include <QAbstractItemDelegate>
#include <QPainter>

Q_DECLARE_METATYPE(QList<QPixmap*>)

QWidget *Image2x2Delegate::createEditor(QWidget *parent,
       const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto editor = new Image2x2Widget(parent);
    //editor->installEventFilter(const_cast<Image2x2Delegate*>(this));
    return editor;
}

void  Image2x2Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"index = "<<index;
    auto icons = index.model()->data(index, Qt::DisplayRole).value<QList<QPixmap*>>();
    if (icons.count() == 4) {
        if (icons[0])
        painter->drawPixmap(QRect(0,0,200,200),*(icons[0]));
        if (icons[1])
        painter->drawPixmap(QRect(200,0,200,200),*(icons[1]));
        if (icons[2])
        painter->drawPixmap(QRect(0,200,200,200),*(icons[2]));
        if (icons[3])
        painter->drawPixmap(QRect(200,200,200,200),*(icons[3]));

    }
}

bool Image2x2Delegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option, const QModelIndex &index)
{
//    if(event->type()  == QEvent::MouseButtonDblClick)
//    {
//        //QMouseEvent * mouse = static_cast<QMouseEvent*>(event);
//        event->ignore();
//        printf("123\n");
//        return false;
//    }
//    return true;
    qDebug()<<index;

    return QStyledItemDelegate::editorEvent(event,model,option,index);
}


void Image2x2Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
//    auto texts = index.model()->data(index, Qt::DisplayRole).toStringList();
//    qDebug()<<"texts = "<<texts;

//auto icons = index.model()->data(index, Qt::DecorationRole).toStringList();
    auto icons = index.model()->data(index, Qt::DisplayRole).value<QList<QPixmap*>>();
    qDebug()<<"icons = "<<icons;
    Image2x2Widget *cell = static_cast<Image2x2Widget*>(editor);



    if (icons.count() == 4){
        if (icons[0]) // 如果模型单元格没有传递图像数据会异常
            cell->setPixmap(0,icons[0]);
        if (icons[1])
            cell->setPixmap(1,icons[1]);
        if (icons[2])
            cell->setPixmap(2,icons[2]);
        if (icons[3])
            cell->setPixmap(3,icons[3]);
    }

//    if (texts.count() == 4)
//    {
//        cell->setText(0,texts[0]);
//         cell->setText(1,texts[1]);
//          cell->setText(2,texts[2]);
//           cell->setText(3,texts[3]);
//    }

}

void Image2x2Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

//    qRegisterMetaType<QList<QPixmap*>>("pixmaplist");
    Image2x2Widget *cell = static_cast<Image2x2Widget*>(editor);
    QVariant v;
    v.setValue(cell->pixmaps());

    //model->setData(index,cell->texts(),Qt::DisplayRole);
    //model->setData(index, v, Qt::DecorationRole); //拿到图标的名称
    model->setData(index, v, Qt::DisplayRole); //拿到图标的名称
//    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
//    model->setData(index, QBrush(Qt::white), Qt::BackgroundColorRole);
//    model->setData(index, QBrush(Qt::red), Qt::TextColorRole);

}

void Image2x2Delegate::updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

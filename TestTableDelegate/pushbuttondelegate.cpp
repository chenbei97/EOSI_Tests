#include "pushbuttondelegate.h"

void PushButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   // painter->drawPixmap(center_x,center_y,QPixmap::fromImage(img)); // 绘制项图像
}

QWidget *PushButtonDelegate::createEditor(QWidget *parent,
       const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return new QPushButton;
}


void PushButtonDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    auto text = index.model()->data(index, Qt::EditRole).toString();
    QPushButton *btn = static_cast<QPushButton*>(editor);
    btn->setText(text);
}

void PushButtonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    QPushButton*btn = static_cast<QPushButton*>(editor);
    model->setData(index,btn->text(), Qt::EditRole);
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
    model->setData(index, QBrush(Qt::white), Qt::BackgroundColorRole);
    model->setData(index, QBrush(Qt::red), Qt::TextColorRole);
}

void PushButtonDelegate::updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

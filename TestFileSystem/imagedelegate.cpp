#include "imagedelegate.h"
#include "qdebug.h"

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    auto pix_var = index.model()->data(index, Qt::DecorationRole);
    if (pix_var.isValid()){
        auto pix = pix_var.value<QPixmap>();
        //qDebug()<<"pix = "<<pix;
        painter->drawPixmap(option.rect,pix);
        auto pen = painter->pen();
        pen.setWidth(1);
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->drawRect(option.rect);
    }
}

void ImageDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

bool ImageDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                 const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        auto  v = index.model()->data(index, Qt::UserRole+1);
        if (v.isValid())
        {
            QLabel * dlg = new QLabel();
            dlg->setAttribute(Qt::WA_DeleteOnClose);

            auto path = v.value<QString>();
            auto icon = QPixmap(path); // 显示的是原图
            dlg->setPixmap(icon);

            if (!dlg->pixmap()->isNull())
                dlg->show();
            else dlg->close();
        }
    }
    return QStyledItemDelegate::editorEvent(event,model,option,index);
}


#include "image2x2delegate.h"
#include <QAbstractItemDelegate>
#include <QPainter>
#include <QTime>
#include <QStyle>
#include <QStylePainter>

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
//    QStyleOptionViewItem opt = option;
//    opt.rect.adjusted(0,0,-30,-30);
//    QStyledItemDelegate::paint(painter, opt, index);

    //qDebug()<<"index = "<<index << " rect = "<<option.rect;
qDebug()<<"ready paint "<< QTime::currentTime().toString("hh::mm:ss::zzz");
    auto x = option.rect.x(); // 0 每个单元格的起始位置会变化
    auto y = option.rect.y(); // 0
    auto w = option.rect.width(); // 400
    auto h = option.rect.height(); // 400 不会变
    // 要做的是400x400的单元格划分成2x2的大小

    auto rect11 = QRect(x,y,w/2,h/2);
    auto rect12 = QRect(x+w/2,y,w/2,h/2);
    auto rect21 = QRect(x,y+h/2,w/2,h/2);
    auto rect22 = QRect(x+w/2,y+h/2,w/2,h/2);

    auto pen = painter->pen();
    pen.setWidth(5);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawRect(option.rect);

    pen.setWidth(3);
    pen.setColor(Qt::gray);
    painter->setPen(pen);
    painter->drawLine(QPointF(x+w/2,y),QPointF(x+w/2,y+h));
    painter->drawLine(QPointF(x,y+h/2),QPointF(x+w,y+h/2));

//    QStylePainter spainter(painter);
//    spainter.drawPrimitive(QStyle::PE_FrameFocusRect, option);

    auto icons = index.model()->data(index, Qt::DisplayRole).value<QList<QPixmap*>>();
    if (icons.count() == 4) {
        if (icons[0])
        painter->drawPixmap(rect11,*(icons[0]));
        if (icons[1])
        painter->drawPixmap(rect12,*(icons[1]));
        if (icons[2])
        painter->drawPixmap(rect21,*(icons[2]));
        if (icons[3])
        painter->drawPixmap(rect22,*(icons[3]));
    }

    QPalette::ColorGroup cg = (option.state & QStyle::State_Enabled) ?
        (option.state & QStyle::State_Active) ? QPalette::Normal :QPalette::Inactive
                                            :QPalette::Disabled;



    if (option.state & QStyle::State_Selected) // 如果小部件被选择就高亮这个颜色组,否则项不会被高亮
{
        // painter->fillRect(option.rect,option.palette.color(cg, QPalette::Background));

        auto c = index.model()->data(index, Qt::BackgroundRole).value<QColor>();
        qDebug()<<"c = "<<c.name();
         pen.setColor(c);
         painter->setPen(pen);
         qDebug()<<"ready drawing..  "<< QTime::currentTime().toString("hh::mm:ss::zzz");
        QColor col =Qt::green; col.setAlpha(100);
         auto p  = index.model()->data(index,Qt::UserRole+1).toPoint();

         // 计算鼠标的位置在哪个部分 (mMousePos
         if (rect11.contains(p))
            {
             painter->drawRect(rect11);
             painter->fillRect(rect11,col);
         }
         if (rect12.contains(p)) {
            painter->drawRect(rect12);
            painter->fillRect(rect12,col);
         }
         if (rect21.contains(p)) {
            painter->drawRect(rect21);
             painter->fillRect(rect21,col);
         }
         if (rect22.contains(p))
         {painter->drawRect(rect22);
          painter->fillRect(rect22,col);}

//         auto pal = option.palette;
//         QColor col =Qt::green;
//         col.setAlpha(100);
//         pal.setColor(cg,QPalette::Highlight,col);
//         auto opt (option);
//         opt.palette = pal;
//         QStyledItemDelegate::paint(painter, opt, index);
    }

//    QStyleOptionViewItem opt = option;
//    opt.showDecorationSelected = true;
    //QStyledItemDelegate::paint(painter, opt, index);
}


bool Image2x2Delegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type()  == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent * mouse = static_cast<QMouseEvent*>(event);
model->setData(index,mouse->pos(),Qt::UserRole+1);
        //mMousePos = mouse->pos();
//qDebug()<<"mMousePos = "<<mMousePos<< QTime::currentTime().toString("hh::mm:ss::zzz");



            event->accept();

    }

////return true;
    return QStyledItemDelegate::editorEvent(event,model,option,index);
}


void Image2x2Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
//    auto texts = index.model()->data(index, Qt::DisplayRole).toStringList();
//    qDebug()<<"texts = "<<texts;

//auto icons = index.model()->data(index, Qt::DecorationRole).toStringList();
    auto icons = index.model()->data(index, Qt::DisplayRole).value<QList<QPixmap*>>();
    //qDebug()<<"icons = "<<icons;
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

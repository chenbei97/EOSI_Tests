#include "tableviewdelegate2x2.h"

void TableViewDelegate2x2::setEditorData(QWidget *editor, const QModelIndex &index) const
{//从TableModel拿数据,data返回的是QVariant,但是模型初始化时对QVariant赋值赋的QVector<QPixmap*>

    static QVector<QPixmap*>  icons =
            index.model()->data(index, Qt::DecorationRole).value<QVector<QPixmap*>>();
    LOG<<"icons = "<<icons;

    TableViewWidget2x2 *cell = static_cast<TableViewWidget2x2*>(editor);

    if (icons.count() == 4){ // 启动的时候可能没数据
        if (icons[0]) // 如果模型单元格没有传递图像数据会异常
            cell->setPixmap(0,icons[0]);
        if (icons[1])
            cell->setPixmap(1,icons[1]);
        if (icons[2])
            cell->setPixmap(2,icons[2]);
        if (icons[3])
            cell->setPixmap(3,icons[3]);
    }
}

void TableViewDelegate2x2::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{ // 这些数据实际上就是存到了TableModel内部的TableModelItem的TableModelData
    TableViewWidget2x2 *cell = static_cast<TableViewWidget2x2*>(editor);

    static QVariant v;
    v.setValue(cell->pixmaps());

    model->setData(index, v, Qt::DecorationRole); //拿到图标的名称
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
    model->setData(index, QBrush(Qt::white), Qt::BackgroundRole);
    model->setData(index, QBrush(Qt::black), Qt::ForegroundRole);
}


bool TableViewDelegate2x2::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option, const QModelIndex &index)
{ // TableView的cell的鼠标事件可以在这里拿到,但不会传递给代理组件
    if(event->type()  == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent * mouse = static_cast<QMouseEvent*>(event);
        model->setData(index,mouse->pos(),TableModelDataRole::MousePosition);
        event->accept();
    }
    return QStyledItemDelegate::editorEvent(event,model,option,index);
}

QWidget *TableViewDelegate2x2::createEditor(QWidget *parent,
       const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto editor = new TableViewWidget2x2(parent);
    //editor->installEventFilter(const_cast<TableViewWidget2x2*>(this));
    return editor;
}

void  TableViewDelegate2x2::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    paintBorder(painter,option); // 1. 绘制外部和内部边框,通用区域要先绘制否则会被覆盖

    paintPixmap(painter,option,index); // 2. 然后绘制显示的图片

    paintText(painter,option,index); // 3. 每张图片显示对应的必要信息/脚注显示

    paintHighlight(painter,option,index); // 4. 鼠标点击的高亮区域绘制

}

void TableViewDelegate2x2::paintHighlight(QPainter *painter, const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    /*每个单元格的左上角位置和大小*/
    static int x = option.rect.x();
    static int y = option.rect.y();
    static int w = option.rect.width();
    static int h = option.rect.height();

    /*划分单元格为4个子区域*/
    static QRect rect11 = QRect(x,y,w/2,h/2);
    static QRect rect12 = QRect(x+w/2,y,w/2,h/2);
    static QRect rect21 = QRect(x,y+h/2,w/2,h/2);
    static QRect rect22 = QRect(x+w/2,y+h/2,w/2,h/2);

    if (option.state & QStyle::State_Selected) // 如果小部件被选择就高亮这个颜色组,否则项不会被高亮
    {
        auto borderColor = index.model()->data(index, TableModelDataRole::HighlightBorderColor).value<QColor>();
        auto backColor = index.model()->data(index, TableModelDataRole::HighlightBackColor).value<QColor>();
        auto mousePos  = index.model()->data(index,TableModelDataRole::MousePosition).toPoint();
        backColor.setAlpha(TableViewHighlightColorAlpha); // 设置透明度,不然fillRect会把绘制的图片覆盖掉

        auto pen = painter->pen();
        pen.setColor(borderColor);
        painter->setPen(pen);

        // 鼠标属于的子区域进行高亮绘制
        if (rect11.contains(mousePos)){
            painter->drawRect(rect11);
            painter->fillRect(rect11,backColor);
        }
        if (rect12.contains(mousePos)) {
            painter->drawRect(rect12);
            painter->fillRect(rect12,backColor);
        }
        if (rect21.contains(mousePos)) {
            painter->drawRect(rect21);
            painter->fillRect(rect21,backColor);
        }
        if (rect22.contains(mousePos)){
            painter->drawRect(rect22);
            painter->fillRect(rect22,backColor);
        }
    }
}

void TableViewDelegate2x2::paintPixmap(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    static int x = option.rect.x();
    static int y = option.rect.y();
    static int w = option.rect.width();
    static int h = option.rect.height();

    static QRect rect11 = QRect(x,y,w/2,h/2);
    static QRect rect12 = QRect(x+w/2,y,w/2,h/2);
    static QRect rect21 = QRect(x,y+h/2,w/2,h/2);
    static QRect rect22 = QRect(x+w/2,y+h/2,w/2,h/2);

    static QVector<QPixmap*> icons =
            index.model()->data(index, Qt::DecorationRole).value<QVector<QPixmap*>>();
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
}

void TableViewDelegate2x2::paintBorder(QPainter *painter, const QStyleOptionViewItem &option) const
{
    // 1. 外边框是黑色
    auto pen = painter->pen();
    pen.setWidth(5);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    painter->drawRect(option.rect);

    // 2. 内边框是十字形灰色
    pen.setWidth(3);
    pen.setColor(Qt::gray);
    painter->setPen(pen);

    static int x = option.rect.x();
    static int y = option.rect.y();
    static int w = option.rect.width();
    static int h = option.rect.height();
    painter->drawLine(QPointF(x+w/2,y),QPointF(x+w/2,y+h));
    painter->drawLine(QPointF(x,y+h/2),QPointF(x+w,y+h/2));
}

void TableViewDelegate2x2::paintText(QPainter *painter, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{

}

void TableViewDelegate2x2::updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

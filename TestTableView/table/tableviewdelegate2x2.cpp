#include "tableviewdelegate2x2.h"
#include "tableview.h"
#include <qapplication.h>

void TableViewDelegate2x2::setEditorData(QWidget *editor, const QModelIndex &index) const
{//从TableModel拿数据,data返回的是QVariant,但是模型初始化时对QVariant赋值赋的QVector<QPixmap*>

    QVector<QPixmap*>  icons =
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
    //return QStyledItemDelegate::setEditorData(editor,index);
}

void TableViewDelegate2x2::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{ // 这些数据实际上就是存到了TableModel内部的TableModelItem的TableModelData
    TableViewWidget2x2 *cell = static_cast<TableViewWidget2x2*>(editor);
    QVariant v;
    v.setValue(cell->pixmaps());
    model->setData(index, v, Qt::DecorationRole); //拿到图标的名称

    // 其他数据可以预设默认值,外部基本不会传递

//    model->setData(index, QColor(Qt::red), TableModelDataRole::HighlightBorderColor);
//    auto c = QColor(Qt::green);
//    c.setAlpha(TableViewHighlightColorAlpha);
//    model->setData(index, c, TableModelDataRole::HighlightBackColor);
//    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
//    model->setData(index, QBrush(Qt::white), Qt::BackgroundRole);
//    model->setData(index, QBrush(Qt::black), Qt::ForegroundRole);
    //return QStyledItemDelegate::setModelData(editor,model,index);
}


bool TableViewDelegate2x2::editorEvent(QEvent *event, QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option, const QModelIndex &index)
{ // TableView的cell的鼠标事件可以在这里拿到,但不会传递给代理组件
    if(event->type()  == QEvent::MouseButtonPress
            || event->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent * mouse = static_cast<QMouseEvent*>(event);

        model->setData(index,mouse->pos(),TableModelDataRole::MousePosition);

        if (event->type() == QEvent::MouseButtonDblClick)
        {
            int x = option.rect.x();
            int y = option.rect.y();
            int w = option.rect.width();
            int h = option.rect.height();

            QRect rect11 = QRect(x,y,w/2,h/2);
            QRect rect12 = QRect(x+w/2,y,w/2,h/2);
            QRect rect21 = QRect(x,y+h/2,w/2,h/2);
            QRect rect22 = QRect(x+w/2,y+h/2,w/2,h/2);

            QVector<QPixmap*> icons =
                    index.model()->data(index, Qt::DecorationRole).value<QVector<QPixmap*>>();

//            auto tableview = static_cast<const TableView*>(option.widget);
//            LOG<<tableview->rowHeight(0); // 可以拿到代理的父类TableView,能做什么事这里留待思考~

            if (icons.count() == 4)
            {
                Picture * dlg = new Picture;
                dlg->setAttribute(Qt::WA_DeleteOnClose);
                if (rect11.contains(mouse->pos())){
                    dlg->setPixmap(*icons[0]);
                }
                if (rect12.contains(mouse->pos())) {
                    dlg->setPixmap(*icons[1]);
                }
                if (rect21.contains(mouse->pos())) {
                    dlg->setPixmap(*icons[2]);
                }
                if (rect22.contains(mouse->pos())){
                    dlg->setPixmap(*icons[3]);
                }
                dlg->show();
            }
        }
        event->accept();
    }

     if (event->type() == QEvent::KeyPress)
    {
            QKeyEvent * e = static_cast<QKeyEvent*>(event);
            auto tableview = static_cast<const TableView*>(option.widget);
            auto idx = tableview->currentIndex();
            LOG<<"cur idx = "<<idx<<" key = "<<e->key();
            if (e->key() == Qt::Key_Left){
                 int col = (idx.column()-1<0)?0:idx.column()-1;

            } else if (e->key() ==Qt::Key_Right){
                int col = (idx.column()+1>=model->columnCount())?
                            model->columnCount()-1:idx.column()+1; // 5+1>=6? 5: 6=> 5
            } else if (e->key() ==Qt::Key_Up){
                int row = (idx.row()-1<0)? 0:idx.row()-1;

            } else if (e->key() ==Qt::Key_Down){
                int row = (idx.row()+1>=model->rowCount())?
                            model->rowCount()-1:idx.row()+1;
            }
    }
    return QStyledItemDelegate::editorEvent(event,model,option,index);
}

QWidget *TableViewDelegate2x2::createEditor(QWidget *parent,
       const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto editor = new TableViewWidget2x2(parent);
    //LOG<<"editor = "<<editor;
    return editor;
    //return QStyledItemDelegate::createEditor(parent,option,index);
}

void  TableViewDelegate2x2::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    paintBorder(painter,option); // 1. 绘制外部和内部边框,通用区域要先绘制否则会被覆盖

    paintPixmap(painter,option,index); // 2. 然后绘制显示的图片

    paintSelectedHighlight(painter,option,index); // 3. 已被选中单元格的高亮绘制

    paintMouseHighlight(painter,option,index); // 4. 鼠标点击的高亮区域绘制
//        QStyleOptionFrame opt;
//        QApplication::style()->drawControl(QStyle::CE_ShapedFrame,&opt, painter);
}

void TableViewDelegate2x2::paintMouseHighlight(QPainter *painter, const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    int x = option.rect.x();
    int y = option.rect.y();
    int w = option.rect.width();
    int h = option.rect.height();

    QRect rect11 = QRect(x,y,w/2,h/2);
    QRect rect12 = QRect(x+w/2,y,w/2,h/2);
    QRect rect21 = QRect(x,y+h/2,w/2,h/2);
    QRect rect22 = QRect(x+w/2,y+h/2,w/2,h/2);

    if (option.state & QStyle::State_Selected) // 如果小部件被选择就高亮这个颜色组,否则项不会被高亮
    {
        auto backColor = index.model()->data(index, TableModelDataRole::HighlightColor).value<QColor>();
        if (!backColor.isValid()) {
            backColor = TableViewMouseHighlightColor;
            backColor.setAlpha(TableViewHighlightColorAlpha); // 设置透明度,不然fillRect会把绘制的图片覆盖掉
        }
        auto mousePos  = index.model()->data(index,TableModelDataRole::MousePosition).toPoint();


        auto pen = painter->pen();
        pen.setColor(TableViewBorderHighlightColor);
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
    int x = option.rect.x();
    int y = option.rect.y();
    int w = option.rect.width();
    int h = option.rect.height();

    QRect rect11 = QRect(x,y,w/2,h/2);
    QRect rect12 = QRect(x+w/2,y,w/2,h/2);
    QRect rect21 = QRect(x,y+h/2,w/2,h/2);
    QRect rect22 = QRect(x+w/2,y+h/2,w/2,h/2);

    QVector<QPixmap*> icons =
            index.model()->data(index, Qt::DecorationRole).value<QVector<QPixmap*>>();
    //LOG<<"icons = "<<icons;
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

    int x = option.rect.x();
    int y = option.rect.y();
    int w = option.rect.width();
    int h = option.rect.height();
    painter->drawLine(QPointF(x+w/2,y),QPointF(x+w/2,y+h));
    painter->drawLine(QPointF(x,y+h/2),QPointF(x+w,y+h/2));
}

void TableViewDelegate2x2::paintSelectedHighlight(QPainter *painter, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    /*每个单元格的左上角位置和大小*/
    int x = option.rect.x();
    int y = option.rect.y();
    int w = option.rect.width();
    int h = option.rect.height();

    /*划分单元格为4个子区域*/
    QRect rect11 = QRect(x,y,w/2,h/2);
    QRect rect12 = QRect(x+w/2,y,w/2,h/2);
    QRect rect21 = QRect(x,y+h/2,w/2,h/2);
    QRect rect22 = QRect(x+w/2,y+h/2,w/2,h/2);

    /*绘制已被选中使用过的项 在前*/
    auto pen = painter->pen(); // 边框颜色统一红色
    pen.setColor(TableViewBorderHighlightColor);
    painter->setPen(pen);

    uint32_t  selected = index.model()->data(index,TableModelDataRole::SelectedItems).toUInt();
    LOG<<"selected = "<<selected;
    auto scolor = index.model()->data(index,TableModelDataRole::SelectedColor).value<QColor>();
    if (!scolor.isValid()) {
        scolor = TableViewSelectedHighlightColor;
        scolor.setAlpha(TableViewHighlightColorAlpha);
    }
    switch (selected) {
        case TableViewCellSelected::None:break;
        case TableViewCellSelected::All:
                painter->fillRect(rect11,scolor);painter->drawRect(rect11);
                painter->fillRect(rect12,scolor);painter->drawRect(rect12);
                painter->fillRect(rect21,scolor);painter->drawRect(rect21);
                painter->fillRect(rect22,scolor);painter->drawRect(rect22);
                break;

        case TableViewCellSelected::OnlyTopLeft:
                painter->fillRect(rect11,scolor);painter->drawRect(rect11);break;
        case TableViewCellSelected::OnlyTopRight:
                painter->fillRect(rect12,scolor);painter->drawRect(rect12);break;
        case TableViewCellSelected::OnlyBottomLeft:
                painter->fillRect(rect21,scolor);painter->drawRect(rect21);break;
        case TableViewCellSelected::OnlyBottomRight:
                painter->fillRect(rect22,scolor);painter->drawRect(rect22);break;

        case TableViewCellSelected::Top:
                painter->fillRect(rect11,scolor);painter->drawRect(rect11);
                painter->fillRect(rect12,scolor);painter->drawRect(rect12);break;
        case TableViewCellSelected::Bottom:
                painter->fillRect(rect21,scolor);painter->drawRect(rect21);
                painter->fillRect(rect22,scolor);painter->drawRect(rect22);break;
        case TableViewCellSelected::Right:
                painter->fillRect(rect12,scolor);painter->drawRect(rect12);
                painter->fillRect(rect22,scolor);painter->drawRect(rect22);break;
        case TableViewCellSelected::Left:
                painter->fillRect(rect11,scolor);painter->drawRect(rect11);
                painter->fillRect(rect21,scolor);painter->drawRect(rect21);break;
        case TableViewCellSelected::DiagLeft: // 0x0101
                painter->fillRect(rect11,scolor);painter->drawRect(rect11);
                painter->fillRect(rect22,scolor);painter->drawRect(rect22);break;
        case TableViewCellSelected::DiagRight: // 0x1010
                painter->fillRect(rect12,scolor);painter->drawRect(rect12);
                painter->fillRect(rect21,scolor);painter->drawRect(rect21);break;

        case TableViewCellSelected::ExceptTopLeft:
                painter->fillRect(rect12,scolor);painter->drawRect(rect12);
                painter->fillRect(rect21,scolor);painter->drawRect(rect21);
                painter->fillRect(rect22,scolor);painter->drawRect(rect22);break;
        case TableViewCellSelected::ExceptTopRight:
                painter->fillRect(rect11,scolor);painter->drawRect(rect11);
                painter->fillRect(rect21,scolor);painter->drawRect(rect21);
                painter->fillRect(rect22,scolor);painter->drawRect(rect22);break;
        case TableViewCellSelected::ExceptBottomLeft:
                painter->fillRect(rect11,scolor);painter->drawRect(rect11);
                painter->fillRect(rect12,scolor);painter->drawRect(rect12);
                painter->fillRect(rect22,scolor);painter->drawRect(rect22);break;
        case TableViewCellSelected::ExceptBottomRight:
                painter->fillRect(rect11,scolor);painter->drawRect(rect11);
                painter->fillRect(rect12,scolor);painter->drawRect(rect12);
                painter->fillRect(rect21,scolor);painter->drawRect(rect21);break;
    }

    /*绘制当前具有焦点的项*/
    uint32_t isCurrent = index.model()->data(index,TableModelDataRole::CurrentItem).toUInt();
    LOG<<"isCurrent = "<<isCurrent<<" index = "<<index;
    auto ccolor = index.model()->data(index,TableModelDataRole::CurrentColor).value<QColor>();
    if (!ccolor.isValid()) {
        ccolor = TableViewCurrentHighlightColor;
        ccolor.setAlpha(TableViewHighlightColorAlpha);
    }
    switch (isCurrent) {
        case 0:break; // 不具有焦点
        case 0b0001:
            painter->fillRect(rect11,ccolor);painter->drawRect(rect11);break;
        case 0b0010:
            painter->fillRect(rect12,ccolor);painter->drawRect(rect12);break;
        case 0b0100:
            painter->fillRect(rect21,ccolor);painter->drawRect(rect21);break;
        case 0b1000:
            painter->fillRect(rect22,ccolor);painter->drawRect(rect22);break;
        default:break; // 其它值忽略
    }

}

void TableViewDelegate2x2::updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

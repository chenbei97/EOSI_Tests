#include "tablewidget.h"
#include <QDebug>

TableWidget::TableWidget(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(1);
    setRowCount(1);
    for (int i = 0; i< rowCount();++i)
        setRowHeight(i,200);
    for (int i = 0; i< columnCount();++i)
        setColumnWidth(i,200);

    //QWidget * w = new QWidget;
    QTableWidget * cell = new QTableWidget(2,2);
    cell->setEditTriggers(QTableWidget::EditTrigger::NoEditTriggers);
    cell->setRowHeight(0,98);
    cell->setRowHeight(1,98);
    cell->setColumnWidth(0,98);
    cell->setColumnWidth(1,98);
    cell->setCornerButtonEnabled(false);
    //cell->setFrameShape(QFrame::NoFrame);
    cell->setAcceptDrops(false);
    cell->verticalHeader()->hide();
    cell->horizontalHeader()->setHidden(true);
    //cell->horizontalHeader()->setFixedSize(100,100);
    //cell->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //cell->setStyleSheet("QTableView{background-color: rgb(250, 250, 115);" "alternate-background-color: rgb(0, 0, 0);}");
    //setStyleSheet("QTableWidget::Item{border:0px solid rgb(191,191,191);}");//"border-bottom:1px solid rgb(191,191,191);}"
    cell->setStyleSheet("selection-background-color:yellow;");
    cell->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cell->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //cell->setStyleSheet("QTableWidget::Item{border:1px solid black;}");
//    cell->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
//                                                     "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
//                                                     "QScrollBar::handle:hover{background:gray;}"
//                                                     "QScrollBar::sub-line{background:transparent;}"
//                                                     "QScrollBar::add-line{background:transparent;}");
    //cell->setShowGrid(false);
    //cell->showDropIndicatorShown(false);
    cell->setTabKeyNavigation(true);
    //cell->setAutoScrollMargin(0);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
//    QVBoxLayout * lay = new QVBoxLayout;
//    lay->addWidget(cell);
//    lay->setMargin(0);
//    lay->setSpacing(0);
    //w->setLayout(lay);

horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
qDebug()<<cell->autoScrollMargin();
//setCellWidget(0,0,w);
//    setCellWidget(0,1,w);
setCellWidget(0,0,cell);
    setAlternatingRowColors(true); // 交替颜色
    setAutoScrollMargin(30);
   // setStyleSheet("QTableWidget::Item{padding:10px;}");
    //resize(1000,500);
}

TableWidget::~TableWidget()
{
}


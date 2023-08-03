#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTreeWidget * w = new QTreeWidget;
    w->setHeaderLabels(QStringList()<<"aa"<<"bb"<<"cc");
    setCentralWidget(w);

    w->setColumnCount(5);

    QList<QTreeWidgetItem *> items1;
    for (int i = 0; i < 5; ++i)
        items1.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    QList<QTreeWidgetItem *> items2;
    for (int i = 0; i <5 ; ++i)
        items2.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i+3))));
    w->insertTopLevelItems(0, items1);


    w->insertTopLevelItem(1,items2[4]);
//     w->insertTopLevelItems(1, items2);
    auto it1 = new QTreeWidgetItem(QStringList()<<"a"<<"b"<<"c"<<"d");
    w->addTopLevelItem(it1);

    auto it2 = new QTreeWidgetItem(QStringList()<<"vv"<<"bb"<<"cc");
    auto it3 = new QTreeWidgetItem(QStringList()<<"aaa"<<"bbb");
    it3->addChild(new QTreeWidgetItem(QStringList()<<"jhdfjsdhf"));
    auto it4 = new QTreeWidgetItem(it3);
    it4->setText(0,"chen");
    it2->addChild(it3);
    it2->addChild(new QTreeWidgetItem(QStringList()<<"324232"));
    w->addTopLevelItem(it2);

    w->setCurrentIndex(w->model()->index(3,2));

    qDebug()<<"columnCount = "<<w->columnCount()
           <<"currentColumn = "<<w->currentColumn()
          <<" topLevelItemCount =  "<<w->topLevelItemCount()
         <<"  "<<w->topLevelItem(0)->text(0)<<"  "<<w->topLevelItem(6)->text(3)
        <<" childCount = "<<it2->childCount()<< " item's columnCount = "<<it2->columnCount();

qDebug()<<w->invisibleRootItem()->text(1);
qDebug()<<w->itemAt(1,2)->text(0);

w->expandItem(it2);
w->collapseItem(it2);
w->scrollToItem(it3);
qDebug()<<w->isExpanded(w->model()->index(7,0));

w->setRootIndex(w->model()->index(5,-1));
qDebug()<<w->rootIndex();

w->selectAll();
w->collapseAll();
w->expandAll();
    resize(800,600);
}

MainWindow::~MainWindow()
{
}


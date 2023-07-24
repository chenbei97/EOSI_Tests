#include "table384.h"
#include <QApplication>
#include <QStandardItemModel>
#include "tableviewdelegatelabel.h"
#include "table24.h"
#include "table96.h"
#include "table_384.h"

void test1();
void test1(TableModel&m,const QMap<int, QVariant>&roles);
void app1();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //app1();
    Table_384 w;

    QMap<int, QVariant> roles;
    QVector<QPixmap*> iconlist;
    iconlist<<new QPixmap(":/1.jpg")<<new QPixmap(":/2.jpg")
           <<new QPixmap(":/3.jpg")<<new QPixmap(":/4.jpg");

    QVariant v ;
    v.setValue(iconlist);
    roles[Qt::DecorationRole] = v;
    roles[TableModelDataRole::HighlightColor] = QColor(Qt::red);

    w.setPixmaps(0,1,iconlist);
    w.setPixmap(0,2,1,iconlist[1]);
    w.setCurrent(3,3,0b0100);
     w.setCurrent(3,4,0b0100);
    w.pixmap(0,1,1);
   // w.pixmap(0,1);

//    w.setData(0,1,QPixmap(":/1.jpg"),Qt::DecorationRole);
//    w.setData(0,1,true,TableModelDataRole::isSelected);
//    w.setData(3,1,true,TableModelDataRole::isSelected);
//    w.setData(3,5,true,TableModelDataRole::isSelected);
//    w.setData(1,3,true,TableModelDataRole::isCurrent);
//    w.setSelectedItem(2,2);
//    w.setPixmap(0,1,QPixmap(":/1.jpg"));
//    w.setCurrentItem(3,3);

    w.show();

    return a.exec();
}

void app1()
{
    //test1();
    Table384 w;
    QMap<int, QVariant> roles;
    QVector<QPixmap*> iconlist;
    iconlist<<new QPixmap(":/1.jpg")<<new QPixmap(":/2.jpg")
           <<new QPixmap(":/3.jpg")<<new QPixmap(":/4.jpg");
//    QVariant v ;
//    v.setValue(iconlist);
//    roles[Qt::DecorationRole] = v;
//    roles[TableModelDataRole::SelectedItems] = 0b1010;
//    //roles[TableModelDataRole::IsCurrentItem] = 0b0000;
//    w.setItemData(0,1,roles);
    w.setPixmaps(0,1,iconlist);
    w.setPixmap(0,0,3,iconlist[2]);

    w.setData(4,0,0b1000,TableModelDataRole::CurrentItem);

    w.show();
}

void test1()
{
    TableView w;

    TableViewDelegate2x2 d;


    QMap<int, QVariant> roles;
//    auto texts = QStringList()<<":/1.jpg"<<":/2.jpg"<<":/3.jpg"<<":/4.jpg";
    QVector<QPixmap*> iconlist;
    iconlist<<new QPixmap(":/1.jpg")<<new QPixmap(":/2.jpg")
           <<new QPixmap(":/3.jpg")<<new QPixmap(":/4.jpg");
    QVariant v ;
    v.setValue(iconlist);
    roles[Qt::DecorationRole] = v;
    roles[TableModelDataRole::HighlightColor] = QColor(Qt::red);



    TableModel m;

//    m.setItemCount(12,8);
//    m.setItemCount(5,5);
    test1(m,roles);


    QItemSelectionModel s(&m);


    w.setItemDelegate(&d);
    w.setModel(&m);
    w.setSelectionModel(&s);
    w.openPersistentEditor(m.index(0,2));

    w.show();
}

void test1(TableModel&m,const QMap<int, QVariant>&roles)
{

    m.insertRows(0,10);
    m.insertColumns(0,5);
//    m.insertRow(0);
//    m.insertColumn(3);

    bool r;
    //    m.setData(m.index(9,9),"5",Qt::EditRole);
    //m.setData(m.index(0,0),QPixmap(":/1.jpg"),Qt::DecorationRole);
    r = m.setItemData(m.index(0,1),roles);
    //qDebug()<<r;
    qDebug()<<m.itemData(m.index(0,1));
    //qDebug()<<m.data(m.index(0,1),Qt::DecorationRole);

    m.removeRows(9,2);
    m.removeColumns(9,1);
}

#include "tableview384.h"
#include <QApplication>
void test1();
void test1(TableModel&m,const QMap<int, QVariant>&roles);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //test1();
    TableView384 w;
    QMap<int, QVariant> roles;
    QVector<QPixmap*> iconlist;
    iconlist<<new QPixmap(":/1.jpg")<<new QPixmap(":/2.jpg")
           <<new QPixmap(":/3.jpg")<<new QPixmap(":/4.jpg");
    QVariant v ;
    v.setValue(iconlist);
    roles[Qt::DecorationRole] = v;
    roles[TableModelDataRole::SelectedItems] = 0b1010;
    //roles[TableModelDataRole::IsCurrentItem] = 0b0000;
    w.setItemData(0,1,roles);
    w.setData(4,0,0b1000,TableModelDataRole::CurrentItem);

    w.show();
    return a.exec();
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

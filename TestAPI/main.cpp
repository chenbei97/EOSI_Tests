#include <QCoreApplication>
#include <QVector>
#include <QDebug>
#include <QApplication>
#include <QItemSelectionModel>

void test1();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test1();

    return a.exec();
}

void test1()
{
    QVector<int> v = {1,2,3,4,5};
    int column = 2;
    int count = 6;
    auto iter = v.begin()+column;
    v.insert(iter,count,qrand()%100);
    qDebug()<<v;

    v.remove(10,6);
    qDebug()<<v;
}

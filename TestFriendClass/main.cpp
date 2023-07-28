#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    A w;
    w.setAge(10);
    increase_age(w); // 11
    B b;
    b.increase_age(&w); // 12
    C c;
    c.increase(&w); // 14
    c.decrease(&w); // 11
    qDebug()<<w.age();

    w.show();
    return a.exec();
}

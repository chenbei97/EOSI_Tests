#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss("style.qss");
    qss.open(QIODevice::ReadOnly);
    a.setStyleSheet(qss.readAll());
    qss.close();

    MainWindow w;
    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include "graphicpattern.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    GraphicPattern w;
    w.show();
    return a.exec();
}

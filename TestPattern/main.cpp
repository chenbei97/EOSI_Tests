#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProtocolPattern w(8,12);
    w.show();
    return a.exec();
}

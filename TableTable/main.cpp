﻿#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QList<QPixmap*>>("pixmaplist");
    MainWindow w;
    w.show();
    return a.exec();
}

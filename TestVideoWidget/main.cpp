#include "mainwindow.h"
#include "videowidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    VideoWidget w;
//    w.show();
//    w.setMedia("C:/Users/22987/Desktop/EOSI_Tests/build/debug/test.avi");
//    w.play();
    MainWindow w;
    w.show();
    return a.exec();
}

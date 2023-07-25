#include "mainwindow.h"
#include "pattern2x3.h"
#include "pattern4x6.h"
#include <QApplication>
#include "pattern.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
//    Pattern2x3 w;
//    w.setGap(50);
//    w.setSelectedRect(Pattern2x3::c11,true);
//    w.setSelectedRect(Pattern2x3::c21,true);
//    w.setSelectedRect(Pattern2x3::c23,true);
    Pattern w;
    //w.setGap(50);
    w.setPatternSize(20,40);
        w.setSelectedRect(1,2);
        w.setSelectedRect(3,4);
        w.setSelectedRect(2,2);
    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include "fliter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 分辨率很高时会自动缩放窗口大小
//    QApplication::setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling);
//    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);
//    Filter filter;
    MainWindow w;
//    w.installEventFilter(&filter);
    w.show();
    return a.exec();
}

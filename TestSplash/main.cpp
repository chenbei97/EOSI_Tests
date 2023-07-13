#include "mainwindow.h"
#include "splash.h"
#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Splash splash(QPixmap(":/cell.png"));

    splash.show();

    int ratio = 3;
    auto rect = splash.screen()->availableGeometry();
    splash.resize(rect.width()/ratio,rect.height()/ratio);
    splash.move((rect.width()-splash.width())/2,(rect.height()-splash.height())/2);
    //splash.showMessage("Loaded MainWindow");
    a.processEvents();

    MainWindow w;
    w.resize(800,600);
    //splash.finish(&w);

    QObject::connect(&splash,&Splash::end,&w,&MainWindow::show);

    //splash.finish(&w);
    return a.exec();
}

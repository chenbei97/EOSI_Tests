#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_ASSERT(QCameraInfo::availableCameras().count() == 1);
    //qDebug()<<QCameraInfo::availableCameras();
    //qDebug()<<QCameraInfo::defaultCamera();
    qDebug()<<QCameraInfo::defaultCamera().deviceName();
    qDebug()<<QCameraInfo::defaultCamera().position();
    qDebug()<<QCameraInfo::defaultCamera().description();
    qDebug()<<QCameraInfo::defaultCamera().orientation();
    MainWindow w;
    w.show();
    return a.exec();
}

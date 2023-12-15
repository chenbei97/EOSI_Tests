#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    player = new QMediaPlayer;

    player->setMedia
            (QUrl::fromLocalFile("C:/Users/22987/Desktop/EOSI_Tests/build/debug/test.avi"));

    auto canvas = new QVideoWidget;
    player->setNotifyInterval(2000);
    player->setVideoOutput(canvas);

    player->play();

}

MainWindow::~MainWindow()
{
}


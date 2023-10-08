#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QMediaRecorder>
#include <QVideoWidget>
#include <QCameraImageCapture>
#include <QCameraViewfinderSettings>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QDebug>
#include <QLabel>
#include <QSplitter>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QCamera * camera;
    QVideoWidget * vwidget;
    QCameraImageCapture * capture;
    QLabel * pic;
    QPushButton * btn;
};
#endif // MAINWINDOW_H

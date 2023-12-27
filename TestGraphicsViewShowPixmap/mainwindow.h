#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent*event) override;
    ~MainWindow();
    QGraphicsView * view;
    QGraphicsScene * scene;
};
#endif // MAINWINDOW_H

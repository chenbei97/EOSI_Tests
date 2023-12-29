#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QGraphicsPixmapItem>
#include <QGLWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent*event) override;
    void wheelEvent(QWheelEvent*event) override;
    ~MainWindow();
    QGraphicsView * view;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * pix;
};
#endif // MAINWINDOW_H

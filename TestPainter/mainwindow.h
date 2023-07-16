#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QMainWindow>
#include <QStaticText>

class MainWindow : public QWidget
{
    Q_OBJECT
    const double mw = 800.0;
    const double mh = 800.0;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*e) override;
};
#endif // MAINWINDOW_H

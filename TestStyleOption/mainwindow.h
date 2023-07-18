#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStyleOption>
#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QSplitter>
#include "button.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPushButton * btn1;
    Button * btn2;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void print(const QStyleOptionButton& opt);
};
#endif // MAINWINDOW_H

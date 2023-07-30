#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QLabel>
#include "tcploader.h"
#include "tcpquery.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject*obj,QEvent*e) override;
    QLabel * mLabel;
    QPushButton * mBtn;
};
#endif // MAINWINDOW_H

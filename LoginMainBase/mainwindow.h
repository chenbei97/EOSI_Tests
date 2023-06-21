#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginmainbase.h"
#include "loginbutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    LoginMain * main;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H

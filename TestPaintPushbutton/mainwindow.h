#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "channelbutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ChannelButton * btn;
};
#endif // MAINWINDOW_H

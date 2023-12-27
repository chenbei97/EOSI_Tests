#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTextEdit>
#include <QTreeView>
#include <QGroupBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QScrollBar>
#include <QScrollArea>
#include "basicwidgettab.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTabWidget * tab;
    BasicWidgetTab * basictab;
};
#endif // MAINWINDOW_H

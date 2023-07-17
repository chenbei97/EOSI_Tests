#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include "qwcomboboxdelegate.h"
#include "tablewidgetbase.h"
#include "tableview.h"
#include "table2x2delegate.h"
#include "image2x2delegate.h"
#include "pushbuttondelegate.h"
#include <QDebug>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qjsonobject.h"
#include "qjsonarray.h"
#include "qjsonvalue.h"
#include "qjsondocument.h"
#include "qdir.h"
#include "qdebug.h"
#include "jsonreadwrite.h"
#include "data.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void test();
    void test_read();
    ~MainWindow();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qaction.h>
#include <qmenu.h>
#include <qdebug.h>
#include <qmenubar.h>
#include <qtabwidget.h>
#include "sqlqueryconsole.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void createNewExperments();
    void queryHistoryExperments();
    void viewCurrentExperments();
private:
    QTabWidget * mTab;
    SqlQueryConsole * mQueryPanel;
};
#endif // MAINWINDOW_H

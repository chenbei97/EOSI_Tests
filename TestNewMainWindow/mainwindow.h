#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qaction.h>
#include <qmenu.h>
#include <qdebug.h>
#include <qmenubar.h>
#include <qtabwidget.h>
#include "scanplanconfig.h"
#include "sqlqueryconsole.h"
#include "scanvesselconfig.h"
#include "gradienthiddenwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef  ScanPlanConfig::ScanPlan ScanPlan;
    MainWindow(QWidget *parent = nullptr);
private slots:
    void onScanPlanChanged(ScanPlan fre);
private:
    QTabWidget * mTab;
    ScanPlanConfig * mScanFreConfig;
    //ScanVesselConfig *  mVesselConfig;
    SqlQueryConsole * mQueryPanel;
    GradientHiddenWidget * www;

private:
    ScanPlan mScanPlan;
};
#endif // MAINWINDOW_H

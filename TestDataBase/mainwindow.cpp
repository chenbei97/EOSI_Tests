#include "mainwindow.h"

//#define A 0
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    DBController * db = &DBController::instance();
#ifdef A
    db->openMysql("dbcontroller","root","199791","127.0.0.1",3306);
    db->openMysql("dbcontroller","root","199791","127.0.0.1",3306);

    //qDebug()<<QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
//    db->closeSqlite();
#else
    db->openSqlite(QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0)+"/db.db3");
    db->openSqlite(QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0)+"/db.db3");
//        db->closeMysql();
#endif
    db->createTable();
    qDebug()<<"mysql isopen? "<<db->mysqlIsOpen()<<" sqlite isopen? "<<db->sqliteIsOpen();
//    qDebug()<<db->mysql();
//    qDebug()<<db->sqlite();
}

MainWindow::~MainWindow()
{
}


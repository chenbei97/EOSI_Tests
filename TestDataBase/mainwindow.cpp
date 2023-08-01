#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    DBController * db = &DBController::instance();
    auto sqlite_path = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0)+"/db.db3";
    //db->open(sqlite_path);
        db->open(sqlite_path);
        db->createTable();

    db->open("dbcontroller","root","199791","127.0.0.1",3306,DBController::MySQL);
    db->createTable(DBController::MySQL);


    qDebug()<<"mysql isopen? "<<db->isOpen(DBController::MySQL)
           <<" sqlite isopen? "<<db->isOpen();

    QString keys,values;
    QVector<QPair<QString,QString>>pairs = {
        {"type","sdjfks"},{"datetime","3ijks"},{"channel","jklsd9"}
    };
    db->addRecord(pairs);
    db->addRecord(pairs,DBController::MySQL);
//    foreach (auto pair, pairs) {
//        keys.append(pair.first);
//        keys.append(',');
//        values.append('\'');
//        values.append(pair.second);
//        values.append('\'');
//        values.append(',');
//    }
//    keys.chop(1);
//    qDebug()<<keys<<values;

    QStringList kk = {"datetime","name","description"};
    QVector<QStringList> vv = {
        {"1","3","5"},
        {"2","4","6"},
        {"a","b","c"},
    };
    db->addRecord(kk,vv);
    db->addRecord(kk,vv,DBController::MySQL);

    qDebug()<<"mysql tables rows = "<<db->tableRows(DBController::MySQL)
        <<" cols = "<<db->tableColumns(DBController::MySQL);

    qDebug()<<"sqlite tables rows = "<<db->tableRows()
        <<" cols = "<<db->tableColumns();

    qDebug()<<"sqlite have field kk? "<<db->haveField("kk")
           <<"mysql have field kk? "<<db->haveField("kk",DBController::MySQL);
    qDebug()<<"sqlite have field type? "<<db->haveField("type")
           <<"mysql have field channel? "<<db->haveField("channel",DBController::MySQL);
}

MainWindow::~MainWindow()
{
}


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    DBController * db = &DBController::instance();
    auto sqlite_path = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0)+"/db.db3";
    qDebug()<<sqlite_path;
    //db->open(sqlite_path);
        db->open(sqlite_path);
        qDebug()<<db->haveTable(ExpermentTableName);
        db->createTable();

    db->open("dbcontroller","root","199791","127.0.0.1",3306,DBController::MySQL);
    db->createTable(DBController::MySQL);


//    qDebug()<<"mysql isopen? "<<db->isOpen(DBController::MySQL)
//           <<" sqlite isopen? "<<db->isOpen();

    QString keys,values;
    QVector<QPair<QString,QString>>pairs = {
        {"type","sdjfks"},{"datetime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh::mm::ss")},{"channel","jklsd9"}
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

    QStringList kk = {"channel","name","description"};
    QVector<QStringList> vv = {
        {"1","3","5"},
        {"2","4","6"},
        {"a","b","c"},
    };
    db->addRecord(kk,vv);
    db->addRecord(kk,vv,DBController::MySQL);

//    qDebug()<<"mysql tables rows = "<<db->tableRows(DBController::MySQL)
//        <<" cols = "<<db->tableColumns(DBController::MySQL);

//    qDebug()<<"sqlite tables rows = "<<db->tableRows()
//        <<" cols = "<<db->tableColumns();

//    db->haveField("kk");
//    db->haveField("aa",DBController::MySQL);
//    db->haveField("type");
//    db->haveField("channel",DBController::MySQL);

//    db->containField("kk");
//    db->containField("kk",DBController::MySQL);
//    db->containField("type");
//    db->containField("channel",DBController::MySQL);

//    db->fieldName(5);
//    db->fieldIndex("channel");
//    db->fieldValue(2,5);
//    db->fieldValue(3,"name");
}

MainWindow::~MainWindow()
{
}


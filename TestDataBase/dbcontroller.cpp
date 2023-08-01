#include "dbcontroller.h"


void DBController::open(const QString &db, const QString &user, const QString &pwd,
                        const QString &ip, int port, SQLType type)
{
     if (type == MySQL) {
         if (mMysqlDataBase.isValid()) {
             mMysqlDataBase.open();
             return;
         }
         mMysqlDataBase = QSqlDatabase::addDatabase("QMYSQL","mysql");
         mMysqlDataBase.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1;");
         mMysqlDataBase.setDatabaseName(db);
         mMysqlDataBase.setUserName(user);
         mMysqlDataBase.setPassword(pwd);
         mMysqlDataBase.setHostName(ip);
         mMysqlDataBase.setPort(port);
         mMysqlDataBase.open();
     } else {
         if (mSqliteDataBase.isValid()) {
             mSqliteDataBase.open();
             return;
         }
         mSqliteDataBase = QSqlDatabase::addDatabase("QSQLITE","sqlite");
         mSqliteDataBase.setDatabaseName(db);
         mSqliteDataBase.open();
     }
}


const QSqlDatabase DBController::database(SQLType type) const
{
    auto name = type==SQLite?"sqlite":"mysql";
    return QSqlDatabase::database(name,false); // 不要改变原有的状态
}


void DBController::close(SQLType type)
{
    if (type == SQLite)
        mSqliteDataBase.close();
    else mMysqlDataBase.close();
}


bool DBController::isOpen(SQLType type) const
{
    if (type == SQLite)
         return mSqliteDataBase.isOpen();
    return mMysqlDataBase.isOpen();
}

bool DBController::createTable(SQLType type)
{
    // 1. 是否打开了对应的驱动
    if (!isOpen(type)) return false;

    // 2. 是否已存在该表
    if (haveTable(type)) return true;

    // 3, 准备创建表
    if (SQLite == type) {
        query = QSqlQuery(mSqliteDataBase);
        query.exec(CreateTableSqlite);
    }
    else {
        query = QSqlQuery(mMysqlDataBase);
        query.exec(CreateTableMysql);
    }

    if (!query.isActive()){ // 执行语句失败
        qDebug()<<"exec failed error is "<<query.lastError().text();
    } else qDebug()<<"create table is successful";

    return true; // 语句不会执行错误,直接返回true
}

bool DBController::haveTable(SQLType type)
{
    if (SQLite == type) {
        query = QSqlQuery(mSqliteDataBase);
        query.exec(QueryTableSqlite);
    }
    else {
        query = QSqlQuery(mMysqlDataBase);
        query.exec(QueryTableMysql);
    }

    if (query.isActive()){ // 执行语句成功前提下
        query.first(); // 这里是有返回值的,要检查是否有记录,要放在isValid前边
        if (query.isValid() && query.record().count() == 1) {
            qDebug()<<"have table"<<ExpermentTableName;
            return true;
        }
    } else { // 是语句格式错误执行失败,不是逻辑错误
        qDebug()<<"exec failed, error is "<<query.lastError().text();
    }

    qDebug()<<"dont have table"<<ExpermentTableName;
    return false;
}

bool DBController::addRecord(const QVector<QPair<QString,QString>>&pairs, SQLType type)
{
    QString keys,values;

    foreach (auto pair, pairs) {
        keys.append(pair.first);
        keys.append(',');
        values.append('\'');
        values.append(pair.second);
        values.append('\'');
        values.append(',');
    }
    keys.chop(1);
    values.chop(1);

    toggleSql(type);
    //qDebug()<<"insert keys = "<<keys<<" values = "<<values;

    int rows = tableRows(type);
    query.exec(QString(QString(InsertRecord).arg(keys).arg(values)));
    if (query.isActive()) {
        if (tableRows(type) == rows + 1) // 确实新增1行
        {
            qDebug()<<"insert into table successful! cur rows = "<<rows+1;
            return true;
        }
    }
    qDebug()<<"insert into table failed! cur rows = "<<rows;
    return false;
}

bool DBController::addRecord(const QStringList&keys,const QVector<QStringList> &multivalues,SQLType type)
{

    QPair<QString,QString> pair; // key-value 一一对应
    for(int i = 0; i < multivalues.count(); ++ i) { // 多个values
        auto values = multivalues[i]; // 新的values
        if (values.count() == keys.count()) {
            QVector<QPair<QString,QString>> pairs; // 某一组keys和values
            for(int j = 0; j < values.count(); ++ j) {
                pair.first = keys[j];
                pair.second = values[j];
                pairs.append(pair);
            }
            if (!addRecord(pairs,type)) // 这组keys,values插入,更新values
                return false;
        }
    }
    return true;
}

int DBController::tableRows(SQLType type)
{
    toggleSql(type);
    query.exec(QueryTableRows); // 查询表格行数
    query.first();
    auto rows = query.value(0).toInt();
    return rows;
}

int DBController::tableColumns(SQLType type)
{
    int cols = 0;
    if (SQLite == type){
        query = QSqlQuery(mSqliteDataBase);
        query.exec(QueryTable); // 查询表格信息
        cols = query.record().count(); // 暂时只能借助QSqlRecord本身提供的功能
    }
    else {
        query = QSqlQuery(mMysqlDataBase);
        query.exec(QueryTableColsMysql); // 可以直接查询表格列数
        query.first();
        cols = query.value(0).toInt();
    }

    return cols;
}


bool DBController::haveField(const QString&field,SQLType type)
{
    toggleSql(type);
    query.exec(QString(QueryTableField).arg(field));
    //qDebug()<<query.lastQuery();
    if (query.isActive()) { // 对于select col from table,col不存在都会直接失败
       query.first();
       //qDebug()<<query.record();
       if (query.isValid()) {
           return true;
       }
    }
    return false;
}



void DBController::updateRecord()
{

}

void DBController::removeRecord()
{

}

DBController::DBController(QObject*parent) : QObject(parent)
{

}

void DBController::toggleSql(SQLType type)
{
    if (SQLite == type)
        query = QSqlQuery(mSqliteDataBase);
    else  query = QSqlQuery(mMysqlDataBase);
}

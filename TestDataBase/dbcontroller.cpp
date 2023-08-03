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

bool DBController::query(const QString &q, SQLType type)
{
    toggleSql(type);
    return mQuery.exec(q);
}

QString DBController::lastError() const
{
    return  mQuery.lastError().text();
}

QSqlRecord DBController::lastRecord() const
{
    return mQuery.record();
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
    if (haveTable(ExpermentTableName,type)) return true;

    // 3, 准备创建表
    if (SQLite == type) {
        mQuery = QSqlQuery(mSqliteDataBase);
        mQuery.exec(CreateTableSqlite);
    }
    else {
        mQuery = QSqlQuery(mMysqlDataBase);
        mQuery.exec(CreateTableMysql);
    }

    if (!mQuery.isActive()){ // 执行语句失败
        qDebug()<<"exec failed error is "<<mQuery.lastError().text();
    } else qDebug()<<"create table is successful";

    return true; // 语句不会执行错误,直接返回true
}

bool DBController::containTable(const QString& table,SQLType type)
{
    QStringList tables;
    if (type == SQLite) {
        tables = mSqliteDataBase.tables();
    } else {
        tables = mMysqlDataBase.tables();
    }
    return tables.contains(table);
}


bool DBController::haveTable(const QString& table,SQLType type)
{
    if (SQLite == type) {
        mQuery = QSqlQuery(mSqliteDataBase);
        mQuery.exec(QString(QueryTableSqlite).arg(table));
    }
    else {
        mQuery = QSqlQuery(mMysqlDataBase);
        mQuery.exec(QString(QueryTableMysql).arg(table));
    }

    if (mQuery.isActive()){ // 执行语句成功前提下
        mQuery.first(); // 这里是有返回值的,要检查是否有记录,要放在isValid前边
        if (mQuery.isValid() && mQuery.record().count() == 1) {
            qDebug()<<"have table"<<ExpermentTableName;
            return true;
        }
    } else { // 是语句格式错误执行失败,不是逻辑错误
        qDebug()<<"exec failed, error is "<<mQuery.lastError().text();
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
    mQuery.exec(QString(QString(InsertRecord).arg(keys).arg(values)));
    if (mQuery.isActive()) {
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
    mQuery.exec(QueryTableRows); // 查询表格行数
    mQuery.first();
    auto rows = mQuery.value(0).toInt();
    return rows;
}

int DBController::tableColumns(SQLType type)
{
    int cols = 0;
    if (SQLite == type){
        mQuery = QSqlQuery(mSqliteDataBase);
        mQuery.exec(QueryTable); // 查询表格信息
        cols = mQuery.record().count(); // 暂时只能借助QSqlRecord本身提供的功能
    }
    else {
        mQuery = QSqlQuery(mMysqlDataBase);
        mQuery.exec(QueryTableColsMysql); // 可以直接查询表格列数
        mQuery.first();
        cols = mQuery.value(0).toInt();
    }

    return cols;
}


bool DBController::haveField(const QString&field,SQLType type)
{
     // select 123 from experments;,select 'a' from experments;都会查到但是没有意义
    toggleSql(type);
    mQuery.exec(QString(QueryTableField).arg(field));

    if (mQuery.isActive()) { // 对于select col from table,col不存在都会直接失败
       mQuery.first();
       //qDebug()<<mQuery.record();
       if (mQuery.isValid()) {
           qDebug()<<"field ["<<field<<"] is exist!";
           return true;
       }
    }
    qDebug()<<"field ["<<field<<"] is not exist!";
    return false;
}

bool DBController::containField(const QString &field, SQLType type)
{
    toggleSql(type);
    mQuery.exec(QueryTable);
    auto record = mQuery.record();
    if (record.contains(field)) {
         qDebug()<<"field ["<<field<<"] is contains!";
         return true;
    }

    qDebug()<<"field ["<<field<<"] is not contains!";
    return false;
}

QString DBController::fieldName(int index, SQLType type)
{
    toggleSql(type);
    mQuery.exec(QueryTable);
    auto record = mQuery.record();
    auto name = record.fieldName(index);
    //auto n = record.field(index).name(); // 结果一样
    qDebug()<<"the "<<index<<" field is "<<name;
    return name;
}

int DBController::fieldIndex(const QString &field, SQLType type)
{
    toggleSql(type);
    mQuery.exec(QueryTable);
    auto record = mQuery.record();
    auto idx = record.indexOf(field);
    qDebug()<<"the "<<field<<"'s index  is "<<idx;
    return idx;
}

QString DBController::fieldValue(int row, int col, SQLType type)
{
    toggleSql(type);
    mQuery.exec(QueryTableOrderById);
    mQuery.first();
    int r = row;
    while (row-- && mQuery.next()) {};
    auto var = mQuery.value(col);
    qDebug()<<"["<<r+1<<","<<col+1<<"] 's value = "<<var.toString();
    return var.toString();
}

QString DBController::fieldValue(int row, const QString &field, SQLType type)
{
    toggleSql(type);
    mQuery.exec(QueryTable);
    mQuery.first();
    int r = row;
    while (row-- && mQuery.next()) {};
    auto var = mQuery.value(field);
    qDebug()<<"the "<<r+1<<" row, on the field "<<field<<" value = "<<var.toString();
    return var.toString();
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
        mQuery = QSqlQuery(mSqliteDataBase);
    else  mQuery = QSqlQuery(mMysqlDataBase);
}

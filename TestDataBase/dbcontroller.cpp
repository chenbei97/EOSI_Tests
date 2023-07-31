#include "dbcontroller.h"




void DBController::openMysql(const QString&db,const QString&user,const QString&pwd,const QString& ip, int port)
{
    if (mysql().isValid()) return;

    mMysqlDataBase = QSqlDatabase::addDatabase("QMYSQL","mysql");
    mMysqlDataBase.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=1;");
    mMysqlDataBase.setDatabaseName(db);
    mMysqlDataBase.setUserName(user);
    mMysqlDataBase.setPassword(pwd);
    mMysqlDataBase.setHostName(ip);
    mMysqlDataBase.setPort(port);
    mMysqlDataBase.open();
    mExecuter = QSqlQuery(mMysqlDataBase);
}

void DBController::openSqlite(const QString& dbpath)
{
    if (sqlite().isValid())
        return;

    mSqliteDataBase = QSqlDatabase::addDatabase("QSQLITE","sqlite");
    mSqliteDataBase.setDatabaseName(dbpath);
    mSqliteDataBase.open();
    mExecuter = QSqlQuery(mSqliteDataBase);
}

const QSqlDatabase DBController::mysql() const
{
    return QSqlDatabase::database("mysql");
}

const QSqlDatabase DBController::sqlite() const
{
    return QSqlDatabase::database("sqlite");
}


void DBController::closeMysql()
{
    mMysqlDataBase.close();
}

void DBController::closeSqlite()
{
    mSqliteDataBase.close();
}


bool DBController::mysqlIsOpen() const
{
    return mMysqlDataBase.isOpen();
}

bool DBController::sqliteIsOpen() const
{
    return mSqliteDataBase.isOpen();
}

void DBController::createTable()
{
    auto c = QString("create table if not exists experments"
                     " (type varchar(100) ,datetime varchar(100), name varchar(100), "
                     "  description varchar(100) );");
    mExecuter.exec(c);
}

bool DBController::haveTable()
{
    return true;
}

void DBController::addField()
{

}


void DBController::removeField()
{

}

bool DBController::haveField()
{
    return true;
}

void DBController::addRecord()
{

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

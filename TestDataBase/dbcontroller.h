#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include "dbsql.h"

class DBController :  QObject
{
    Q_OBJECT
public:
    enum SQLType {SQLite,MySQL};
    static DBController& instance() {
        static DBController instance;
        return instance;
    }

    void open(const QString &db, const QString &user="", const QString &pwd="",
              const QString &ip="", int port=-1, SQLType type = SQLite);

    const QSqlDatabase database(SQLType type = SQLite) const;

    void close(SQLType type= SQLite);

    bool isOpen(SQLType type = SQLite) const;

    bool createTable(SQLType type = SQLite);
    bool haveTable(SQLType type = SQLite);

    bool addRecord(const QVector<QPair<QString,QString>>&pairs,SQLType type = SQLite);
    bool addRecord(const QStringList&keys,const QVector<QStringList> &multivalues,SQLType type = SQLite);

    int tableRows(SQLType type = SQLite) ;
    int tableColumns(SQLType type = SQLite) ;

    bool haveField(const QString&field,SQLType type = SQLite);

    void updateRecord();
    void removeRecord();

private:
    explicit DBController(QObject* parent = 0);
    void toggleSql(SQLType type);
    QSqlDatabase mMysqlDataBase;
    QSqlDatabase mSqliteDataBase;
    QSqlQuery query;
};

#endif // DBCONTROLLER_H

#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlIndex>
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

    bool query(const QString&q,SQLType type = SQLite);
    QString lastError() const;
    QSqlRecord lastRecord() const;

    const QSqlDatabase database(SQLType type = SQLite) const;

    void close(SQLType type= SQLite);

    bool isOpen(SQLType type = SQLite) const;

    bool createTable(SQLType type = SQLite);
    bool haveTable(SQLType type = SQLite);

    int tableRows(SQLType type = SQLite) ;
    int tableColumns(SQLType type = SQLite) ;

    bool haveField(const QString&field,SQLType type = SQLite);
    bool containField(const QString&field,SQLType type = SQLite);

    QString fieldName(int index, SQLType type = SQLite);
    int fieldIndex(const QString&field,SQLType type = SQLite);

    QString fieldValue(int row, int col, SQLType type = SQLite);
    QString fieldValue(int row, const QString&field,SQLType type = SQLite);

    bool addRecord(const QVector<QPair<QString,QString>>&pairs,SQLType type = SQLite);
    bool addRecord(const QStringList&keys,const QVector<QStringList> &multivalues,SQLType type = SQLite);
    void updateRecord();
    void removeRecord();

private:
    explicit DBController(QObject* parent = 0);
    void toggleSql(SQLType type);
    QSqlDatabase mMysqlDataBase;
    QSqlDatabase mSqliteDataBase;
    QSqlQuery mQuery;
};

#endif // DBCONTROLLER_H

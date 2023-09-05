#ifndef SQLREADWRITE_H
#define SQLREADWRITE_H

#include "sqlstatements.h"

class SqlReadWrite : public QObject
{
    Q_OBJECT
protected:
    QSqlDatabase mDB;
    QSqlQuery mQuery;
    SQLType mType;
public:
    explicit SqlReadWrite(QObject *parent = nullptr);

    void setType(SQLType type);
    SQLType type() const;
    void close();

    const QSqlDatabase database() const;
    QString currentDataSource();
    bool isValid() const;
    bool isOpen() const;

    bool createTable(QCString statement);
    bool createTable(QCString table,QCString statement,QCString init);
    bool createEmptyTable(QCString table);
    bool dropTable(QCString table);
    bool haveTable(QCString table);
    bool containTable(QCString table);

    int tableRows(QCString table);
    virtual int tableColumns(QCString table);

    bool haveField(QCString table,QCString field);
    bool containField(QCString table,QCString field);
    bool fieldsRight(QCString table,QCFieldsList fieldNames);

    QString fieldName(QCString table,int index);
    QFieldsList fieldNames(QCString table);
    int fieldIndex(QCString table,QCString field);

    QString fieldValue(QCString table,int row, int col);
    QString fieldValue(QCString table,int row, const QString&field);

    bool query(QCString q);
    QString dbError() const;
    QString lastError() const;
    QSqlRecord lastRecord() const;
    QSqlQuery lastQuery() const;

    bool addRecord(QCString table,QCFieldsList fieldList, QCValuesList values); // 多值
    QBoollist addRecord(QCString table,QCFieldsList fieldList, QCValuemap map); // 多值
    bool addRecord(QCString table,QCFieldsList fieldList, QCString value);//单组值
    bool addRecord(QCString table,QCFieldsList fieldList, QCValuelist values); // 单组值

    bool haveRecord(QCString table,QCString condition);
    bool haveRecord(QCString table,QCString field,QCString condition);
    bool haveRecord(QCString table,int row);

    bool removeRecord(QCString table, QCString condition);
    bool removeRecord(QCString table, int row);

    bool updateRecord(QCString table,QCString dict, QCString condition);
    bool updateRecord(QCString table,QCString dict, int row);
    bool updateRecord(QCString table,QCString key, QCString value,QCString condition);
    bool updateRecord(QCString table,QCString key, QCString value,int row);
    bool updateRecord(QCString table,QFieldsList keys, QValuesList values,QCString condition);
    bool updateRecord(QCString table,QFieldsList keys, QValuesList values,int row);
signals:

};

#endif // SQLREADWRITE_H

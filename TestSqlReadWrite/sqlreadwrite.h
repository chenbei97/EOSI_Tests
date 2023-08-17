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

    SQLType type() const;
    void close();

    const QSqlDatabase database() const;
    bool isValid() const;
    bool isOpen() const;

    bool createTable(QCString statement);
    bool createEmptyTable(QCString table);
    bool dropTable(QCString table);
    virtual bool haveTable(QCString table);
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
    QString lastError() const;
    QSqlRecord lastRecord() const;

    bool addRecord(QCString table,QCFieldsList fieldList, QCFieldsList values);

signals:

};

#endif // SQLREADWRITE_H

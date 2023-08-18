#ifndef SQLITEREADWRITE_H
#define SQLITEREADWRITE_H

#include "sqlreadwrite.h"
#include "qstandardpaths.h"
#include "qdir.h"

class SqliteReadWrite : public SqlReadWrite
{
    Q_OBJECT
public:
    static SqliteReadWrite& instance();
    bool open(QCString db,QCString path = QString());
    bool haveDataSource(QCString source,QCString path = QString());
    bool createDataSource(QCString source,QCString path = QString());
    bool dropDataSource(QCString source,QCString path = QString());
private:
    explicit SqliteReadWrite(QObject*parent = nullptr);
    ~SqliteReadWrite();
    QString mStandardPath;
};

#define SqliteReadWritePointer (&SqliteReadWrite::instance())
#endif // SQLITEREADWRITE_H

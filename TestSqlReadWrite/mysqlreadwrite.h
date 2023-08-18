#ifndef MYSQLREADWRITE_H
#define MYSQLREADWRITE_H

#include "sqlreadwrite.h"
/*
 *  "Unknown database 'cell1' QMYSQL: Unable to connect"
 *  "Access denied for user 'roo'@'localhost' (using password: YES) QMYSQL: Unable to connect"
 * "Access denied for user 'root'@'localhost' (using password: YES) QMYSQL: Unable to connect"
 *  "Can't connect to MySQL server on '192.0.0.1:3306' (10060) QMYSQL: Unable to connect"
 *  "Can't connect to MySQL server on '127.0.0.1:3305' (10060) QMYSQL: Unable to connect"
*/
enum class MySqlLoginError {
    DataSourceUnFinded,
    UserOrPwdError,
    IPOrPortError,
    NoError
};

class MySqlReadWrite : public SqlReadWrite
{
    Q_OBJECT
public:
    static MySqlReadWrite& instance();
    MySqlLoginError open(QCString db, QCString user, QCString pwd,QCString ip, int port);

    bool haveDataSource(QCString source);
    bool createDataSource(QCString source);
    bool dropDataSource(QCString source);

    int tableColumns(QCString table) override;
private:
    explicit MySqlReadWrite(QObject*parent = nullptr);
    ~MySqlReadWrite();
};

#define MysqlReadWritePointer (&MySqlReadWrite::instance())

#endif // MYSQLREADWRITE_H

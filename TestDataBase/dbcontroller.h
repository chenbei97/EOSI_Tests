#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

static const char * ExpermentTableName = "experments";
static const char * ExpermentFields[] = {
    "type",
    "datetime",
    "name",
    "describe",
};

class DBController :  QObject
{
    Q_OBJECT
public:
    static DBController& instance() {
        static DBController instance;
        return instance;
    }

    void openMysql(const QString&db,const QString&user,const QString&pwd,const QString& ip, int port);
    void openSqlite(const QString& dbpath);

    const QSqlDatabase mysql() const; // 设定const 不允许外部操作
    const QSqlDatabase sqlite() const;

    void closeMysql();
    void closeSqlite();

    bool mysqlIsOpen() const;
    bool sqliteIsOpen() const;

    void createTable();
    bool haveTable();

    void addField();
    void removeField();
    bool haveField();

    void addRecord();
    void updateRecord();
    void removeRecord();

private:
    explicit DBController(QObject* parent = 0);
    QSqlDatabase mMysqlDataBase;
    QSqlDatabase mSqliteDataBase;
    QSqlQuery mExecuter;
};

#endif // DBCONTROLLER_H

#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#define mysql

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<QSqlDatabase ::drivers();
#ifdef sqlite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//QMYSQL
#else
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");  //连接本地主机
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("199791");
#endif
    db.setDatabaseName("mdb"); // 会自动创建
    if (!db.open())
    {
        qDebug()<<db.lastError().text();
    }else {qDebug()<<"successful!";}
    return a.exec();
}

#include <QCoreApplication>
#include <QtSql>
#include <QDebug>
#define sqlite 0
//#define mysql 1
#define odbc 2

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<QSqlDatabase ::drivers();
    QSqlDatabase db;

#ifdef mysql
    qDebug()<<"mysql is running";
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");  //连接本地主机
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("199791");
    db.setDatabaseName(QString::fromLocal8Bit("cell"));
#elif odbc
    qDebug()<<"odbc is running";
    db = QSqlDatabase::addDatabase("QODBC3");
    //db.setHostName("127.0.0.1");  //连接本地主机
    //db.setPort(3306);
    db.setUserName("root");
    db.setPassword("199791");
    db.setDatabaseName(QString::fromLocal8Bit("MySql")); // 这个名称是数据源名称，自己定义的
    /*
        * 如果采用的odbc数据源模式连接数据库，
        * 只需要设置数据库名称为对应新建的数据源名字，
        * 然后设置用户名和密码就行，
        * 不需要设置主机名称和端口，因为数据源那边已经设置过的，
        * 这里只需要再次验证用户信息就行
    */
#else
    qDebug()<<"sqlite is running";
    db = QSqlDatabase::addDatabase("QSQLITE");//
    db.setDatabaseName("mdb"); // 会自动创建
#endif

    if (!db.open())
    {
        qDebug()<<db.lastError().text();
    }else {qDebug()<<"successful!";}

    QSqlQuery query;
    query.exec("select  *  from employee "); //where id = 1 name = 'A' 限制条件会影响下边的rec
    qDebug()<<query.isActive(); // true
    qDebug()<<query.isValid(); // false 没有指向有效的行只会返回空记录
    qDebug()<<query.record(); // 8列字段
    qDebug()<<query.record().field("age"); // QSqlField对象
    qDebug()<<query.record().field("idcard").value(); // QVariant(QString, "")
    qDebug()<<query.record().value(2); // QVariant(QString, "")
    qDebug()<<query.record().value("idcard");// QVariant(QString, "")

    auto k = query.record();
    k.setValue(1,"abc");
    qDebug()<<k.value(1);
    qDebug()<<"----------------------------------------------";
    auto rec = query.record();
    //qDebug()<<rec.count();
    int nameCol = rec.indexOf("name"); // 姓名列
    qDebug()<<"namecol == "<<nameCol; // 2

    while (query.next()) // 访问具体的数据只能通过query.value不能通过record.value
          qDebug() << query.value(nameCol).toString(); // 遍历这列输出
    // 除非是QSqlTableModel.record(row)返回的对象可以去访问某一行的记录
    query.first();
    qDebug()<<query.value("entrydate").toString();

    return a.exec();
}

#include <QCoreApplication>
#include "mysqlreadwrite.h"

void test1();
void test2();
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); 
    // test1();// （1）测试常规函数
    test2();// （2）测试表相关函数

    return a.exec();
}

void test2()
{
    auto instance = MysqlReadWritePointer;
    instance->open("test","root","199791","127.0.0.1",3306);

    // 开始之前已有孔的数据源test
    qDebug()<<"have table kkk? "<<instance->haveTable("kkk");
    qDebug()<<"contain table kkk? "<<instance->containTable("kkk");
    instance->dropTable("kkk");

    auto statement = QString(CreateExperGeneralConfigTableMysql)
            .arg(ExperGeneralConfigTableName).arg(CreateExperGeneralConfigTableInit);
    if (!instance->haveTable(ExperGeneralConfigTableName)) // 表不存在
        instance->createTable(statement); // 创建表
    else { // 否则表存在的画检查表的正确性
        instance->fieldsRight(ExperGeneralConfigTableName,ExperGeneralConfigFields);
    }
    //qDebug()<<"have table experconfig? "<<instance->haveTable(ExperGeneralConfigTableName);
    qDebug()<<"contain table experconfig? "<<instance->containTable(ExperGeneralConfigTableName);
    qDebug()<<"experconfig's columns = "<<instance->tableColumns(ExperGeneralConfigTableName);
    qDebug()<<"experconfig's rows = "<<instance->tableRows(ExperGeneralConfigTableName);
    qDebug()<<"experconfig have field id?  "<<instance->haveField(ExperGeneralConfigTableName,"id");
    qDebug()<<"experconfig have field id1?  "<<instance->haveField(ExperGeneralConfigTableName,"id1");
    qDebug()<<"experconfig contain field id?  "<<instance->containField(ExperGeneralConfigTableName,"id");
    qDebug()<<"experconfig contain field id1?  "<<instance->containField(ExperGeneralConfigTableName,"id1");
    qDebug()<<"experconfig the 6th field is "<<instance->fieldName(ExperGeneralConfigTableName,6);
    qDebug()<<"experconfig objective'd index is "<<instance->fieldIndex(ExperGeneralConfigTableName,"objective");
    instance->fieldNames(ExperGeneralConfigTableName);
    qDebug()<<"query is ok ?"<<instance->query("show columns from experconfig");
    //qDebug()<<"query's record is "<<instance->lastRecord();

    // 手动给数据库添加4行值用于测试fieldValue函数
    instance->fieldValue(ExperGeneralConfigTableName,0,15);
    instance->fieldValue(ExperGeneralConfigTableName,1,15);
    instance->fieldValue(ExperGeneralConfigTableName,2,15);
    instance->fieldValue(ExperGeneralConfigTableName,3,15);
    instance->fieldValue(ExperGeneralConfigTableName,4,15);
    instance->fieldValue(ExperGeneralConfigTableName,2,2);
    instance->fieldValue(ExperGeneralConfigTableName,2,16);
    instance->fieldValue(ExperGeneralConfigTableName,2,"channel");
    instance->fieldValue(ExperGeneralConfigTableName,3,"ana_definition");
    instance->fieldValue(ExperGeneralConfigTableName,3,"ana_definition1");

    instance->createEmptyTable("kkk");
    instance->dropTable("kkk"); // 之前测试是不存在表的情况,现在表存在删除它
}

void test1()
{
    auto instance = MysqlReadWritePointer;
    qDebug()<<"type = mysql ? "<<(instance->type()==SQLType::Mysql);
    qDebug()<<"is valid? "<<instance->isValid();
    qDebug()<<"is open? "<<instance->isOpen();
    instance->open("cell","root","199791","127.0.0.1",3306);
    qDebug()<<"is open? "<<instance->isOpen();
    instance->close();
    qDebug()<<"is open? "<<instance->isOpen();

    auto ret = instance->open("cell1","root","199791","127.0.0.1",3306);
    Q_ASSERT(ret == MySqlLoginError::DataSourceUnFinded);
    ret = instance->open("cell","roo","199791","127.0.0.1",3306);
    Q_ASSERT(ret == MySqlLoginError::UserOrPwdError);
    ret = instance->open("cell","root","19971","127.0.0.1",3306);
    Q_ASSERT(ret == MySqlLoginError::UserOrPwdError);
    ret = instance->open("cell","root","199791","128.0.0.1",3306);
    Q_ASSERT(ret == MySqlLoginError::IPOrPortError);
    ret = instance->open("cell","root","199791","127.0.0.1",3305);
    Q_ASSERT(ret == MySqlLoginError::IPOrPortError);
    ret = instance->open("cell","root","199791","127.0.0.1",3306);
    Q_ASSERT(ret == MySqlLoginError::NoError);

    auto r = instance->haveDataSource("eosi");
    qDebug()<<"datasource eosi is exist? "<<r;
    qDebug()<<"datasource cell is exist? "<<instance->haveDataSource("cell");
    if (!r) instance->createDataSource("eosi");
    instance->dropDataSource("eosi");
    instance->dropDataSource("eosi"); // 再次删除测试,会报错
    //qDebug()<<"database ? "<<instance->database();

    instance->createDataSource("test");
    instance->close();
    instance->open("test","root","199791","127.0.0.1",3306);
   // instance->dropDataSource("test"); // 删除自身测试
    qDebug()<<"database ? "<<instance->database(); // 从结果来看可以删除自身
}

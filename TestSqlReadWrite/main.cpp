#include <QCoreApplication>
#include "mysqlreadwrite.h"
#include "sqlitereadwrite.h"
// 测试mysql
void test1();
void test2();
void test3();
// 测试sqlite
void test4();
void test5();
void test6();
bool test7();
static SqlReadWrite* currentSqlReadWritePointer();
QValuelist fakevalues();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); 
    //test1();// （1）测试常规函数
//    test2();// （2）测试表相关函数
   // test3(); // （3）测试插入和更新值
    //test4();
    //test5();
    //test6();
   test7();
    QFileInfo info("C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Data\\eosi");
    qDebug()<<info.lastRead();
    return a.exec();
}

bool test7()
{
    auto sql = MysqlReadWritePointer;
    sql->open("eosi","root","199791","127.0.0.1",3306);
//    auto sql = SqliteReadWritePointer;
//    sql->open("eosi.db3");
    auto values = fakevalues(); // QVector<QString>,把要插入的值按照顺序返回一个列表
    auto fields = ExperGeneralConfigFields;
    fields.pop_front(); // 添加新纪录时id不需要指定
    auto rows = sql->tableRows(ExperGeneralConfigTableName);

    if (!sql->haveTable(ExperGeneralConfigTableName)) {// 不存在就创建表
        if (sql->type() == SQLType::Mysql)
            sql->createTable(ExperGeneralConfigTableName,CreateExperGeneralConfigTableMysql,CreateExperGeneralConfigTableInit);
        else sql->createTable(ExperGeneralConfigTableName,CreateExperGeneralConfigTableSqlite,CreateExperGeneralConfigTableInit);
    } else {// 存在表
        if (!sql->fieldsRight(ExperGeneralConfigTableName,ExperGeneralConfigFields)) {// 不正确，删除重新创建
            sql->dropTable(ExperGeneralConfigTableName); // 删除并重新创建
            if (sql->type() == SQLType::Mysql)
                sql->createTable(ExperGeneralConfigTableName,CreateExperGeneralConfigTableMysql,CreateExperGeneralConfigTableInit);
            else sql->createTable(ExperGeneralConfigTableName,CreateExperGeneralConfigTableSqlite,CreateExperGeneralConfigTableInit);
        }
    }
     sql->addRecord(ExperGeneralConfigTableName,fields,values); // 添加新的记录
     sql->query(QString(PrimaryKeyReorderMysql).arg(ExperGeneralConfigTableName));
    if (sql->tableRows(ExperGeneralConfigTableName) == rows+1) // 确实新增1条记录
        return true;

     return true;
}

void test6()
{
    auto instance = SqliteReadWritePointer;
    instance->open("cell.db3");
    instance->haveRecord(ExperGeneralConfigTableName,2);
    instance->haveRecord(ExperGeneralConfigTableName,3);
    instance->removeRecord(ExperGeneralConfigTableName,"ana_spec2 = '0,33' ");
    instance->removeRecord(ExperGeneralConfigTableName,"ana_spec2 = 0.34 ");

    instance->updateRecord(ExperGeneralConfigTableName,
                           "ana_spec1 = '0.55', ana_spec2 = '0.01', exper_name = 'hbnfjhsdbf' ",
                           "id = 3");
    instance->updateRecord(ExperGeneralConfigTableName,
                           "ana_spec1 = '0.55', ana_spec2 = '0.01', exper_name = 'hbnfjhsdbf' ",
                           9);
    instance->updateRecord(ExperGeneralConfigTableName,"ana_spec1","100",5);

    QFieldsList fields = {"channel","view","wellsize"};
    QValuesList vals = {"channel","view","wellsize"};
    instance->updateRecord(ExperGeneralConfigTableName,fields,vals,5);

    qDebug()<<"current data source is "<<instance->currentDataSource();
}

void test5()
{
    auto instance = SqliteReadWritePointer;
    instance->createDataSource("cell.db3");
    instance->open("cell.db3");

    instance->haveTable("kkk");
    instance->containTable("kkk");
    instance->dropTable("kkk");
    instance->createEmptyTable("kkk");

    instance->createTable(ExperGeneralConfigTableName,
                          CreateExperGeneralConfigTableSqlite,
                          CreateExperGeneralConfigTableInit); // 创建表
    instance->fieldsRight(ExperGeneralConfigTableName,ExperGeneralConfigFields);

    qDebug()<<"contain table experconfig? "<<instance->containTable(ExperGeneralConfigTableName);
    qDebug()<<"contain table kkk? "<<instance->containTable("kkk");
    qDebug()<<"experconfig have field id?  "<<instance->haveField(ExperGeneralConfigTableName,"id");
    qDebug()<<"experconfig have field id1?  "<<instance->haveField(ExperGeneralConfigTableName,"id1");
    qDebug()<<"experconfig contain field id?  "<<instance->containField(ExperGeneralConfigTableName,"id");
    qDebug()<<"experconfig contain field id1?  "<<instance->containField(ExperGeneralConfigTableName,"id1");
    qDebug()<<"experconfig the 6th field is "<<instance->fieldName(ExperGeneralConfigTableName,6);
    qDebug()<<"experconfig objective'd index is "<<instance->fieldIndex(ExperGeneralConfigTableName,"objective");

    // 测试addRecord函数
    QFieldsList fields = {"ana_spec1","ana_spec2","exper_name"};
    // 版本1的测试 多组值
    QFieldsList values1 = {"('0.5','0.6','chenbei')","('0.86','0.34','chbi')","('0.98','0.16','cb')"};
//    instance->addRecord(ExperGeneralConfigTableName,fields,values1);
 // 版本2的测试 单组值 只有一个字符串
    //instance->addRecord(ExperGeneralConfigTableName,fields,"('0.64','0.29','0.48')");
    // 版本3的测试 单组值，是一个向量值
    QValuelist vals = {"0.99","0.16","hsjdkf"};
    //instance->addRecord(ExperGeneralConfigTableName,fields,vals);
    // 版本4 多组值 使用map二维表示
    QValuemap map = {
        {"0.97","0.36","opire"},
        {"0.90","0.18","ghmbs","aq"}, // 插入失败1条
        {"0.37","0.33","acb drf"}
    };
    //instance->addRecord(ExperGeneralConfigTableName,fields,map);

    qDebug()<<"experconfig's columns = "<<instance->tableColumns(ExperGeneralConfigTableName);
    qDebug()<<"experconfig's rows = "<<instance->tableRows(ExperGeneralConfigTableName);

    instance->fieldValue(ExperGeneralConfigTableName,3,"ana_spec1");
    instance->fieldValue(ExperGeneralConfigTableName,3,"ana_definition1");
}

void test4()
{
    auto instance = SqliteReadWritePointer;
    qDebug()<<"type = sqlite ? "<<(instance->type()==SQLType::Sqlite);
    qDebug()<<"is valid? "<<instance->isValid();
    //qDebug()<<"is open? "<<instance->isOpen();

    instance->open("cell.db3","C:\\Users\\22987\\AppData\\Local\\EOSI"); // 指定路径
    qDebug()<<"database ? "<<instance->database();
    instance->open("cell.db3","C:\\Users\\22987\\AppDat\\Local\\EOSI"); // 指定不存在路径

    instance->open("cell.db3");
    qDebug()<<"is open? "<<instance->isOpen();
    qDebug()<<"database ? "<<instance->database();
    instance->close();
    qDebug()<<"is open? "<<instance->isOpen();

    instance->haveDataSource("cell.db3");
    instance->haveDataSource("cell.db3","C:\\Users\\22987\\AppData\\Local\\EOSI");
    instance->haveDataSource("cell.db3","C:\\Users\\229871\\AppData\\Local\\EOSI");

    instance->createDataSource("cel.db3");
    instance->createDataSource("cell.db3","C:\\Users\\22987\\AppData\\Local\\EOSI");
    instance->createDataSource("cell.db3","C:\\Users\\229871\\AppData\\Local\\EOSI");
    instance->dropDataSource("cel.db3");
    instance->dropDataSource("cell.db3"); // 路径不存在huo'z 文件占用不能删除
    instance->dropDataSource("cell.db3","C:\\Users\\22987\\AppData\\Local\\EOSI");
    instance->dropDataSource("cell.db3","C:\\Users\\229871\\AppData\\Local\\EOSI");
}

void test3()
{
    auto instance = MysqlReadWritePointer;
    instance->open("test","root","199791","127.0.0.1",3306);

    QFieldsList fields = {"ana_spec1","ana_spec2","exper_name"};
    QFieldsList values1 = {"('0.5','0.6','chenbei')","('0.86','0.34','chbi')","('0.98','0.16','cb')"};
    //instance->addRecord(ExperGeneralConfigTableName,fields,values1);
    QFieldsList values2 = {"('0.5','0.6','chenbei','kkk')","('0.86','0.34','chbi')","('0.98','0.16','cb')"};
    instance->addRecord(ExperGeneralConfigTableName,fields,values2);
    //"Column count doesn't match value count at row 1 QMYSQL: Unable to execute query"
    //instance->addRecord(ExperGeneralConfigTableName,fields,"('0.64','0.29','0.48')");
    QValuelist vals = {"0.99","0,16","hsjdkf"};
    //instance->addRecord(ExperGeneralConfigTableName,fields,vals);

    QValuemap map = {
        {"0.97","0,36","opire"},
        {"0.90","0,18","ghmbs","aq"},
        {"0.37","0,33","acb drf"}
    };
    instance->addRecord(ExperGeneralConfigTableName,fields,map);

    instance->fieldValue(ExperGeneralConfigTableName,3,"ana_definition");
    instance->fieldValue(ExperGeneralConfigTableName,3,"ana_definition1");

    instance->removeRecord(ExperGeneralConfigTableName,3);
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
    qDebug()<<"current data source is "<<instance->currentDataSource();
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

QValuelist fakevalues()
{ //  ExperGeneralConfigFields规定的顺序,注意id是自动增长无需规定
    QValuelist list;
    list << QDateTime::currentDateTime().toString("yyyy/MM/hh hh:mm:ss");
    list << "分析定义";
    list << "是大家看法和会计师大后方会计师大后方看收到客户的数据库"
            "上的飞机和速度加快粉红色的尽快发货及时将货款收到回复即可收到回复即可收到"
            "胜多负少。，麦克拉卢卡库链接打开垃圾深刻理解的撒范德萨卡夫卡的数据库数据的v看速度加快速度"
            "的身份绝对是覅空手道解放开绿灯司法鉴定司搭街坊昆仑山地方艰苦拉萨的封建士大夫撒旦解放昆仑山搭街坊可是到了";
    list << QString::number(0.58);
    list << QString::number(0.69);
    list << "phase";
    list << "大肠杆菌";
    list << "experiment_description";
    list << "experiment_name";
    list << "experiment_person";
    list << "experiment_type";
    list << "objective";
    list << "scan_type";
    if (true) {
        list << QString::number(2);
        list << QString::number(1800);
        list << QDateTime(QDate(2023,8,23),QTime(10,30)).toString("yyyy/MM/dd hh:mm");
        list << "true";
        list << QDateTime(QDate(2023,8,23),QTime(9,30)).toString("yyyy/MM/dd hh:mm");
        list << QString::number(3600);
    } else {
        list << QString::number(8);
        list << QString::number(1800);
        list << "";
        list << "false";
        list << "";
        list << QString::number(1800*8);
    }
    list << QString::number(4);
    list << QString::number(384);

    return list;
}
static SqlReadWrite* currentSqlReadWritePointer()
{
    static SqlReadWrite * w = nullptr;
    if (CurrentSqliteType)
        w = SqliteReadWritePointer;
    else w = MysqlReadWritePointer;
    return w;
}

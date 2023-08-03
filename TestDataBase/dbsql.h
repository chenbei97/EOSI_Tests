#ifndef DBSQL_H
#define DBSQL_H
//#include <QString>

static const char * ExpermentTableName = "experments";
//static const char * ExpermentFields[] = {
//    "type",
//    "datetime",
//    "name",
//    "describe",
//};

// 创建表
static const char* CreateTableMysql = "create table if not exists experments( "
        "id integer primary key auto_increment not null unique,"
        "type varchar(100) not null default '', "
        "datetime datetime not null default '1899/12/30 00:00:00', " // noew(),不支持.zzz
        "name varchar(100) not null default '', "
        "description varchar(100) not null default '', "
        "channel varchar(100) not null default '');";

static const char* CreateTableSqlite= "create table if not exists experments( "
        "id integer primary key autoincrement not null unique,"
        "type varchar(100) not null default '', "
        "datetime datetime not null default '1899/12/30 00:00:00', "
        "name varchar(100) not null default '', "
        "description varchar(100) not null default '', "
        "channel varchar(100) not null default '' );";

// 查询表的信息
static const char* QueryTable = "select * from experments";
static const char* QueryTableOrderById = "select * from experments order by id";

// 查询表指定字段
static const char* QueryTableField = "select %1 from experments;";

// 查询指定表
static const char* QueryTableMysql = "show tables like '%1' ";
static const char* QueryTableSqlite = "select name from sqlite_master where name = '%1' ";

// 查询表格行数
static const char* QueryTableRows = "select count(*) from experments";
static const char* QueryTableColsMysql = "select count(column_name) from information_schema.columns where  table_name = 'experments';";

// 插入数据, 对于sqlite和mysql都是相同的
static const char* InsertRecord = "insert into experments(%1) values(%2)";

#endif // DBSQL_H

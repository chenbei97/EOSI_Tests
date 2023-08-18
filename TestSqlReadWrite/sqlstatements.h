#ifndef SQLSTATEMENTS_H
#define SQLSTATEMENTS_H

#include "qdebug.h"
#include "qdatetime.h"
#define LOG (qDebug()<<"["<<QTime::currentTime().toString("h:mm:ss:zzz")<<__FUNCTION__<<"] ")
#define SqlExecFailedLOG (qDebug()<<"[" \
    <<QTime::currentTime().toString("h:mm:ss:zzz")<<__FUNCTION__<<"] sql exec failed! error is ")
typedef  const QString& QCString;
typedef  QStringList QFieldsList;
typedef  QStringList QValuesList;
typedef QVector<QString> QValuelist;
typedef QVector<QVector<QString>> QValuemap;
typedef QVector<bool> QBoollist;
typedef  const QFieldsList& QCFieldsList;
typedef  const QValuesList& QCValuesList;
typedef  const QValuelist& QCValuelist;
typedef  const QValuemap& QCValuemap;

#include "qsqlindex.h"
#include "qsqlrecord.h"
#include "qsqlerror.h"
#include "qsqlfield.h"
#include "qsqlquery.h"
#include "qsqldatabase.h"

enum class SQLType {Mysql,Sqlite};

// （1）表信息，表架构等
// （1.1）数据源固定名称
static const char*  DataBaseName = "eosi";
// （1.2）表的名称
static const char* ExperGeneralConfigTableName = "experconfig";
// （1.3）每张表的所有字段，按照顺序存储
static QFieldsList ExperGeneralConfigFields = {
        "id", "datetime",
        "ana_definition","ana_notes","ana_spec1","ana_spec2",
        "channel",
        "exper_celltype","exper_description","exper_name","exper_person","exper_type",
        "objective","scan_type","view","wellsize"
};

// （2）通用命令
static const char* SelectXFromTable = "select * from %1 ";
static const char* SelectXFromTableWhere = "select * from %1 where %2 ";
static const char* SelectTableRows = "select count(*) from %1 "; // 查询行数
static const char* SelectXFromTableOrderById = "select * from %1 order by id"; // id保证都i有
static const char* SelectFieldFromTable = "select %1 from %2";
static const char* DropTable = "drop table %1";
static const char* CreateEmptyTableMySql = "create table if not exists %1( "
        "id integer primary key auto_increment not null unique, "
        "datetime datetime not null default '1899/12/30 00:00:00' );"; // 空表
static const char* CreateEmptyTableSqlite = "create table if not exists %1( "
        "id integer primary key autoincrement not null unique, "
        "datetime datetime not null default '1899/12/30 00:00:00' );"; // 空表
//insert into experconfig (channel,view,wellsize)
//values ('phase','2','96'),('red','4','24'),('green','8','384')
// 通用型,%3可以是多个()括起来的值,%2可以是ExperGeneralConfigFields每个表的每个字段逗号隔开
static const char* InsertRecord = "insert into %1 (%2) values %3";
static const char* RemoveRecord = "delete from %1 where %2";
static const char* UpdateRecord = "update %1 set %2 where %3";

// （3）数据库特有命令
// （3.1）查询指定表是否存在
static const char*  ShowTablesLike = "show tables like '%1' "; // 仅限于mysql
static const char*  SelectTableExistedFromInformationSchema =
    "select table_name from information_schema.tables where table_schema= '%1' and table_name = '%2' ";// 仅限于mysql
static const char* SelectTableExistedFromSqliteMaster = "select name from sqlite_master where name = '%1' ";// 仅限于sqlite
// （3.2）查询表格列数
static const char* SelectTableColumnsFromInformationSchema =
        "select count(column_name) from information_schema.columns where  table_name = '%1' ";// 仅限于mysql
// （3.2）创建表
// （3.2.1）实验流程通用配置表 时间和ID一定存在
static const char * CreateExperGeneralConfigTableInit =
        "ana_definition varchar(100) not null default '', "
        "ana_notes varchar(200) not null default '', "
        "ana_spec1 varchar(20) not null default '', "
        "ana_spec2 varchar(20) not null default '', "
        "channel varchar(100) not null default '', "
        "exper_celltype varchar(100) not null default '', "
        "exper_description varchar(100) not null default '', "
        "exper_name varchar(100) not null default '', "
        "exper_person varchar(100) not null default '', "
        "exper_type varchar(100) not null default '', "
        "objective varchar(100) not null default '', "
        "scan_type varchar(100) not null default '', "
        "view varchar(20) not null default '', "
        "wellsize varchar(20) not null default '' ";

static const char* CreateExperGeneralConfigTableMysql = "create table if not exists %1( "
        "id integer primary key auto_increment not null unique, "
        "datetime datetime not null default '1899/12/30 00:00:00',"// now(),不支持.zzz
        "%2 );";
static const char* CreateExperGeneralConfigTableSqlite = "create table if not exists %1( "
        "id integer primary key autoincrement not null unique, "
        "datetime datetime not null default '1899/12/30 00:00:00',"// now(),不支持.zzz
        "%2 );";

// （3.3）数据源是否存在
static const char* ShowDataSourceLike = "show databases like %1";// 仅限于mysql
static const char* SelectDataSourceExistedFromInformationSchema=
        "select count(1) from information_schema.schemata where schema_name = '%1' ";// 仅限于mysql
// （3.4）创建数据源
static const char*  CreateDataSource = "create database if not exists %1 character set 'utf8mb4'";// 仅限于mysql
// （3.5）删除数据源
static const char*  DropDataSource = "drop database %1";// 仅限于mysql
// （3.6）列出数据源
static const char* CurrentDataSourceMysql = "select database() ";
static const char* CurrentDataSourceSqlite = "PRAGMA database_list";


#endif // SQLSTATEMENTS_H

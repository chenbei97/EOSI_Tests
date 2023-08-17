#include "sqlreadwrite.h"

SqlReadWrite::SqlReadWrite(QObject *parent) : QObject(parent)
{
}

SQLType SqlReadWrite::type() const
{
    return mType;
}

void SqlReadWrite::close()
{
    mDB.close();
}

bool SqlReadWrite::isValid() const
{
    return mDB.isValid();
}

bool SqlReadWrite::isOpen() const
{
    return mDB.isOpen();
}

bool SqlReadWrite::dropTable(QCString table)
{
    if (!haveTable(table)) {
        LOG<<table<<" table is not existed, can't drop!";
        return true;
    }
    auto statement = QString(DropTable).arg(table);
    mQuery.exec(statement);
    if (mQuery.isActive()) {
        LOG<<"drop table "<<table<<" successful!";
        return true;
    } else {
        SqlExecFailedLOG<<lastError();
    }
    LOG<<"drop table "<<table<<" failed!";
    return false;
}

bool SqlReadWrite::haveTable(QCString table)
{
    Q_UNUSED(table);
    return false;
}

bool SqlReadWrite::createTable(QCString statement)
{
    mQuery.exec(statement);
    if (!mQuery.isActive()) {
        SqlExecFailedLOG<<lastError();
        return false;
    }
    LOG<<"create table is successful";
    return true;
}

bool  SqlReadWrite::createEmptyTable(QCString table)
{
    //空表至少有id和datetime
    auto statement = QString(CreateEmptyTable).arg(table);

    mQuery.exec(statement);
    if (!mQuery.isActive()) {
        SqlExecFailedLOG<<lastError();
        return false;
    }
    LOG<<"create empty table is successful";
    return true;
}

bool SqlReadWrite::containTable(QCString table)
{
    return mDB.tables().contains(table);
}

const QSqlDatabase SqlReadWrite::database() const
{
    return mDB;
}

int SqlReadWrite::tableRows(QCString table)
{
    auto statements = QString(SelectTableRows).arg(table);
    mQuery.exec(statements);
    mQuery.first();
    if (!mQuery.isValid()) return 0; // 可能是无效的没有查到结果
    auto rows = mQuery.value(0).toInt();
    LOG<<"table's rows = "<<rows;
    return rows;
}

int SqlReadWrite::tableColumns(QCString table)
{ // 默认实现通过查询表后,record本身提供的功能返回
    // 对于mysql可以使用其他命令得到
    auto statements = QString(SelectXFromTable).arg(table);
    mQuery.exec(statements);
    auto cols = lastRecord().count();
    LOG<<"table's cols = "<<cols;
    return cols;
}

bool SqlReadWrite::haveField(QCString table,QCString field)
{ // 直接使用查询字段的sql命令
    auto statements = QString(SelectFieldFromTable).arg(field).arg(table);
    mQuery.exec(statements);

    if (mQuery.isActive()) { // 查询字段只要没执行失败就说明有这个字段
       LOG<<"field ["<<field<<"] is exist!";
       return true;
    } else {
        SqlExecFailedLOG<<lastError();
    }
    LOG<<"field ["<<field<<"] is not exist!";
    return false;
}

bool SqlReadWrite::containField(QCString table,QCString field)
{ // 不直接查询字段,查表后利用record实现
    auto statements = QString(SelectXFromTable).arg(table);
    mQuery.exec(statements);
    if (lastRecord().contains(field)) {
        LOG<<"field ["<<field<<"] is contains!";
        return true;
    }
    LOG<<"field ["<<field<<"] is not contains!";
    return false;
}

bool SqlReadWrite::fieldsRight(QCString table,QCFieldsList fields)
{ // 查询表中的字段,和事先规定的字段是否匹配,fields来自sqlstatements.h
    auto tableFields = fieldNames(table);
    // 1.检查数量
    if (tableFields.count() != fields.count()) {
        LOG<<"field's count not right, expect count = "<<fields.count()
          <<" infact count = "<<tableFields.count();
        return false;
    }
    // 2.逐顺序比较字段是否对应正确
    auto count = tableFields.count();
    LOG<<"field's count is right, count = "<<count;
    for (int i = 0; i < count; ++i ) {
        if (tableFields.at(i) != fields.at(i)) {
            return false;
        }
    }
    LOG<<"field's count and order and name is right";
    return true;
}

QString SqlReadWrite::fieldName(QCString table,int index)
{
    auto statements = QString(SelectXFromTable).arg(table);
    mQuery.exec(statements);
    auto name = lastRecord().fieldName(index);
    LOG<<"the "<<index<<" field is "<<name;
    return name;
}

QFieldsList SqlReadWrite::fieldNames(QCString table)
{
    auto statements = QString(SelectXFromTable).arg(table);
    mQuery.exec(statements);
    QStringList ret;
    auto rec = lastRecord();
    for (int i = 0; i < rec.count(); ++i)
        ret.append(rec.fieldName(i));
    LOG<<table<<"'s fields is "<<ret;
    return ret;
}

int SqlReadWrite::fieldIndex(QCString table,QCString field)
{
    auto statements = QString(SelectXFromTable).arg(table);
    mQuery.exec(statements);
    auto idx = lastRecord().indexOf(field);
    LOG<<"the "<<field<<"'s index  is "<<idx;
    return idx;
}

QString SqlReadWrite::fieldValue(QCString table,int row, int col)
{ // 查询指定行指定列的值,要求必须查询返回的表是有序的,id是主键
    if (row<0 || row > tableRows(table)-1) {
        LOG<<"row is out of range";
        return "row is out of range";
    }
    if (col<0 || col > tableColumns(table) -1) {
        LOG<<"column is out of range";
        return "column is out of range";
    }

    auto statements = QString(SelectXFromTableOrderById).arg(table);
    mQuery.exec(statements);
    int r = row;
    mQuery.first();
    while (row-- && mQuery.next()) {}; // 移动到指定行
    auto var = mQuery.value(col); // 拿到指定列的值
    LOG<<"["<<r<<","<<col<<"] 's value = "<<var.toString();
    return var.toString();
}

QString SqlReadWrite::fieldValue(QCString table,int row, const QString&field)
{
    if (row<0 || row > tableRows(table)-1) {
        LOG<<"row is out of range";
        return "row is out of range";
    }
    if (!haveField(table,field)) {
        LOG<<field<<" is not exists!";
        return field+" is not exists!";
    }

    auto statements = QString(SelectXFromTableOrderById).arg(table);
    mQuery.exec(statements);
    mQuery.first();
    int r = row;
    while (row-- && mQuery.next()) {}; // 移动到指定行
    auto var = mQuery.value(field);
    LOG<<"["<<r<<","<<field<<"] 's value = "<<var.toString();
    return var.toString();
}

bool SqlReadWrite::query(QCString q)
{
    auto r = mQuery.exec(q);
    if (!r)
        SqlExecFailedLOG<<lastError();
    return r;
}

QString SqlReadWrite::lastError() const
{
    return  mQuery.lastError().text();
}

QSqlRecord SqlReadWrite::lastRecord() const
{
    return mQuery.record();
}

bool SqlReadWrite::addRecord(QCString table,QCFieldsList fieldList, QCFieldsList values)
{ // fieldList是所有字段的列表,要拆成逗号分隔的QString,即QString("channel,view,wellsize") 不需要单引号
    // values是个列表,每个元素都是小括号包裹起来逗号分隔的字符串,需要单引号
   // QFieldsList vals = {"('phase','2','96')", "('red','4','24')", "('green','8','384')"};
}

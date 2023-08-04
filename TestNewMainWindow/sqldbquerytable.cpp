#include "sqldbquerytable.h"

SqlDBQueryTable::SqlDBQueryTable(QWidget *parent) : QWidget(parent)
{
    auto dbname = QSqlDatabase::connectionNames();
    Q_ASSERT(dbname.count() == 1);// 软件只会出现1个
    db = QSqlDatabase::database(dbname[0],true);
    mView = new QTableView(this);
    mView->setEditTriggers(QTableView::NoEditTriggers);
    mModel = new SqlTableModel(mView,db);
    mQueryModel = new QSqlQueryModel(mView);
    mSelection = new QItemSelectionModel(mModel);
    mView->setModel(mModel);
    mView->setSelectionModel(mSelection);
    mView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 表头居中

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addWidget(mView);

    mSchemaModel = new QStandardItemModel(mView);
    mSchemaModel->insertColumns(0, 10);
    mSchemaModel->setHeaderData(0, Qt::Horizontal, "name"); // "id"
    mSchemaModel->setHeaderData(1, Qt::Horizontal, "type"); // QVariant::QDateTime
    mSchemaModel->setHeaderData(2, Qt::Horizontal, "length"); // 11
    mSchemaModel->setHeaderData(3, Qt::Horizontal, "precision"); // 0
    mSchemaModel->setHeaderData(4, Qt::Horizontal, "value"); // ""
    mSchemaModel->setHeaderData(5, Qt::Horizontal, "defaultValue"); // ""
    mSchemaModel->setHeaderData(6, Qt::Horizontal, "isRequired"); // 1=requierd,0=optional,-1=unknow
    mSchemaModel->setHeaderData(7, Qt::Horizontal, "isGenerated"); // true
    mSchemaModel->setHeaderData(8, Qt::Horizontal, "isAutoValue"); // true
    mSchemaModel->setHeaderData(9, Qt::Horizontal, "isReadOnly"); // false

}

void SqlDBQueryTable::showTable(const QString&table)
{
    //mModel->setTable(db.driver()->escapeIdentifier(table,QSqlDriver::TableName));

    mModel->setTable(table);
    for (int i = 0 ; i < mModel->rowCount(); ++ i) {
        for(int j = 0; j < mModel->columnCount(); ++j) {
            mModel->setData(mSchemaModel->index(i, j), Qt::AlignCenter,Qt::TextAlignmentRole);
        }
    }
    mView->setModel(mModel);
    mModel->select();

    if (mModel->lastError().type() != QSqlError::NoError)
        emit queryResult(mModel->lastError().text());
    else emit queryResult("query successful!");

    QStringList fields;
    auto record  = mModel->record();
    for(int i = 0; i < record.count(); ++i)
        fields.append(record.fieldName(i));

    emit tableNameFields(table,fields);

}

void SqlDBQueryTable::showSchema(const QString&table)
{
    auto record = db.record(table);
    mSchemaModel->setRowCount(record.count());
//    qDebug()<<record;
    for (int i = 0; i < record.count(); ++i) {
        QSqlField fld = record.field(i);
//        qDebug()<<"name = "<<fld.name()<<"  value = "<<fld.value().toString()
//               <<" length = "<<fld.length()<<" precision = "<<fld.precision()
//              <<" isReadOnly = "<<fld.isReadOnly()<<" isAutoValue = "<<fld.isAutoValue()
//             <<" isGenerated = "<<fld.isGenerated() <<" defaultvalue = "<<fld.defaultValue().toString()
//            <<" isRequired = "<<fld.requiredStatus()<<" type = "<<fld.type();
        //qDebug()<<"value = "<<fld.value()<<fld.defaultValue();
        QString value;
        if (!fld.value().isValid() || fld.value().toString().isEmpty()) value ="null";
        else value = fld.value().toString();
        QString defaultValue;
        if (!fld.defaultValue().isValid() || fld.defaultValue().toString().isEmpty()) defaultValue ="null";
        else defaultValue = fld.defaultValue().toString();

        mSchemaModel->setData(mSchemaModel->index(i, 0), fld.name());
//        mSchemaModel->setData(mSchemaModel->index(i, 1), fld.typeID() == -1
//                ? QString(QMetaType::typeName(fld.type()))
//                : QString("%1 (%2)").arg(QMetaType::typeName(fld.type())).arg(fld.typeID())); // typeName=>QString, typeID=>253
        mSchemaModel->setData(mSchemaModel->index(i, 1),QMetaType::typeName(fld.type()));
        mSchemaModel->setData(mSchemaModel->index(i, 2), fld.length());
        mSchemaModel->setData(mSchemaModel->index(i, 3), fld.precision());
        mSchemaModel->setData(mSchemaModel->index(i, 4), value);
        mSchemaModel->setData(mSchemaModel->index(i, 5), defaultValue);
        mSchemaModel->setData(mSchemaModel->index(i, 6), fld.requiredStatus() == -1 ? QVariant("?"): QVariant(bool(fld.requiredStatus())));
        mSchemaModel->setData(mSchemaModel->index(i, 7), fld.isGenerated());
        mSchemaModel->setData(mSchemaModel->index(i, 8), fld.isAutoValue());
        mSchemaModel->setData(mSchemaModel->index(i, 9), fld.isReadOnly());

        mSchemaModel->setData(mSchemaModel->index(i, 0), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 1), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 2), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 3), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 4), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 5), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 6), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 7), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 8), Qt::AlignCenter,Qt::TextAlignmentRole);
        mSchemaModel->setData(mSchemaModel->index(i, 9), Qt::AlignCenter,Qt::TextAlignmentRole);

    }
    mView->setModel(mSchemaModel);
}


void SqlDBQueryTable::execQuery(const QString&command)
{
    mQueryModel->setQuery(QSqlQuery(command, db));
    mView->setModel(mQueryModel);

    if (mQueryModel->lastError().type() != QSqlError::NoError)
        emit queryResult(mQueryModel->lastError().text());
    else if (mQueryModel->query().isSelect())
        emit queryResult(tr("query successful!"));
}

void SqlDBQueryTable::filterTableByField(const QString& filter)
{
    //mModel->setFilter("datetime > 2023/04/02 and datetime < 20230602");
    mModel->setFilter(filter);
    mModel->select();
    mView->setModel(mModel);
    if (mModel->lastError().type() != QSqlError::NoError)
        emit queryResult(mModel->lastError().text());
    else if (mModel->query().isSelect())
        emit queryResult(tr("filter successful!"));
}

void SqlDBQueryTable::filterTableByTime(const QString&start,const QString&end)
{
    if (mModel->tableName().isEmpty()) return; // 防止还没双击显示表用户就点了时间控件

    auto command = "select * from "+mModel->tableName()+" where datetime between "+start
            +" and "+end;
    mQueryModel->setQuery(QSqlQuery(command, db));
    mView->setModel(mQueryModel);

    if (mQueryModel->lastError().type() != QSqlError::NoError)
        emit queryResult(mQueryModel->lastError().text());
    else if (mQueryModel->query().isSelect())
        emit queryResult(tr("sort by time successful!"));
}

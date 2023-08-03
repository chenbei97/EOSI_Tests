#include "sqldbquerytable.h"

SqlDBQueryTable::SqlDBQueryTable(QWidget *parent) : QWidget(parent)
{
    auto dbname = QSqlDatabase::connectionNames();
    Q_ASSERT(dbname.count() == 1);// 软件只会出现1个
    db = QSqlDatabase::database(dbname[0],true);
    mView = new QTableView(this);
    mView->setEditTriggers(QTableView::NoEditTriggers);
    mModel = new QSqlTableModel(mView,db);
    mSelection = new QItemSelectionModel(mModel);
    mView->setModel(mModel);
    mView->setSelectionModel(mSelection);
    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addWidget(mView);

    mSchemaModel = new QStandardItemModel(mView);
    mSchemaModel->insertColumns(0, 9);
    mSchemaModel->setHeaderData(0, Qt::Horizontal, "field");
    mSchemaModel->setHeaderData(1, Qt::Horizontal, "type");
    mSchemaModel->setHeaderData(2, Qt::Horizontal, "length");
    mSchemaModel->setHeaderData(3, Qt::Horizontal, "precision");
    mSchemaModel->setHeaderData(4, Qt::Horizontal, "required");
    mSchemaModel->setHeaderData(5, Qt::Horizontal, "generated");
    mSchemaModel->setHeaderData(6, Qt::Horizontal, "typeId");
    mSchemaModel->setHeaderData(7, Qt::Horizontal, "autoValue");
    mSchemaModel->setHeaderData(8, Qt::Horizontal, "readOnly");
}

void SqlDBQueryTable::showTable(const QString&table)
{
    //mModel->setTable(db.driver()->escapeIdentifier(table,QSqlDriver::TableName));
    mView->setModel(mModel);
    mModel->setTable(table);
    mModel->select();
    if (mModel->lastError().type() != QSqlError::NoError)
        emit queryResult(mModel->lastError().text());
    else emit queryResult("query is ok");
}

void SqlDBQueryTable::showSchema(const QString&table)
{
    auto record = db.record(table);
//    qDebug()<<record;
    mView->setModel(mSchemaModel);
}

//QSharedPointer<QStandardItemModel> SqlDBQueryTable::createTmpModel(const QSqlRecord&rec) const
//{

//    auto model = new QStandardItemModel(mView);
//    model->insertRows(0, rec.count());
//    model->insertColumns(0, 9);

////    model->setHeaderData(0, Qt::Horizontal, "field");
////    model->setHeaderData(1, Qt::Horizontal, "type");
////    model->setHeaderData(2, Qt::Horizontal, "length");
////    model->setHeaderData(3, Qt::Horizontal, "precision");
////    model->setHeaderData(4, Qt::Horizontal, "required");
////    model->setHeaderData(5, Qt::Horizontal, "generated");
////    model->setHeaderData(6, Qt::Horizontal, "typeId");
////    model->setHeaderData(7, Qt::Horizontal, "autoValue");
////    model->setHeaderData(8, Qt::Horizontal, "readOnly");

////    for (int i = 0; i < rec.count(); ++i) {
////        QSqlField fld = rec.field(i);
////        model->setData(model->index(i, 0), fld.name());
////        model->setData(model->index(i, 1), fld.typeID() == -1
////                ? QString(QMetaType::typeName(fld.type()))
////                : QString("%1 (%2)").arg(QMetaType::typeName(fld.type())).arg(fld.typeID()));
////        model->setData(model->index(i, 2), fld.length());
////        model->setData(model->index(i, 3), fld.precision());
////        model->setData(model->index(i, 4), fld.requiredStatus() == -1 ? QVariant("?")
////                : QVariant(bool(fld.requiredStatus())));
////        model->setData(model->index(i, 5), fld.isAutoValue());
////        model->setData(model->index(i, 6), fld.defaultValue());
////    }


//    QSharedPointer<QStandardItemModel> ptr = QSharedPointer<QStandardItemModel>(model);
//    return ptr;
//}

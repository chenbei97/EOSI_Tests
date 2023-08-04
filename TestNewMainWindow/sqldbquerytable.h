#ifndef SQLDBQUERYTABLE_H
#define SQLDBQUERYTABLE_H

#include <QWidget>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlDriver>
#include <QVBoxLayout>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QDebug>

class SqlTableModel : public QSqlTableModel
{
public:
    explicit SqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase())
        : QSqlTableModel(parent, db) {}
    QVariant data(const QModelIndex &idx, int role) const override
    {
        if (role == Qt::BackgroundRole && isDirty(idx))
            return QBrush(QColor(Qt::yellow)); // 修改过数据
        if (role == Qt::TextAlignmentRole)
            return  Qt::AlignCenter;
        return QSqlTableModel::data(idx, role);
    }
};

class SqlDBQueryTable : public QWidget
{
    Q_OBJECT
public:
    explicit SqlDBQueryTable(QWidget *parent = nullptr);
public slots:
    void showTable(const QString&table);
    void showSchema(const QString&table);
    void execQuery(const QString&command);
    void filterTableByTime(const QString&start,const QString&end);
    void filterTableByField(const QString& filter);
private:

private:
    SqlTableModel * mModel;
    QStandardItemModel * mSchemaModel;
    QSqlQueryModel * mQueryModel;
    QTableView * mView;
    QItemSelectionModel * mSelection;
    QSqlDatabase db;
signals:
    void queryResult(const QString&msg);
    void tableNameFields(const QString&table,const QStringList& fields);
};

#endif // SQLDBQUERYTABLE_H

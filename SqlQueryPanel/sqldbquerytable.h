#ifndef SQLDBQUERYTABLE_H
#define SQLDBQUERYTABLE_H

#include <QWidget>
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

class SqlDBQueryTable : public QWidget
{
    Q_OBJECT
public:
    explicit SqlDBQueryTable(QWidget *parent = nullptr);
public slots:
    void showTable(const QString&table);
    void showSchema(const QString&table);
private:
    //QSharedPointer<QStandardItemModel> createTmpModel(const QSqlRecord&rec) const;
private:
    QSqlTableModel * mModel;
    QStandardItemModel * mSchemaModel;
    QTableView * mView;
    QItemSelectionModel * mSelection;
    QSqlDatabase db;
signals:
    void queryResult(const QString&msg);
};

#endif // SQLDBQUERYTABLE_H

﻿#ifndef SQLDBQUERYTREE_H
#define SQLDBQUERYTREE_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSqlDatabase>
#include <QAction>
#include <QDebug>
#include <QVBoxLayout>

static void setTreeItemBold(QTreeWidgetItem*item, bool bold = true)
{
    auto font = item->font(0);
    font.setBold(bold);
    item->setFont(0,font);
}

class SqlDBQueryTree : public QWidget
{
    Q_OBJECT
public:
    explicit SqlDBQueryTree(QWidget *parent = nullptr);
public slots:
    void refreshTree();
    void showSchema();
private:
    void setBold(QTreeWidgetItem*item,bool bold = true);
    void onItemActivated(QTreeWidgetItem*item,int column);
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
private:
    QTreeWidget * mTreeView;
    QAction * mRefresh;
    QAction * mSchema;

signals:
    void schemaShowed(const QString&n);
    void tableShowed(const QString&n);
};

#endif // SQLDBQUERYTREE_H

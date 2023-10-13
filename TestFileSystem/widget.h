#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QLayout>
#include <QFileSystemModel>
#include <QDebug>
#include <QHeaderView>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QImageReader>
#include <QSplitter>
#include "qapplication.h"
#include "imagedelegate.h"

#define ImageSize 250
#define CellSize 300

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void onDirectoryLoaded(const QString &path);
    void onFileRenamed(const QString &path, const QString &oldName, const QString &newName);
    void onRootPathChanged(const QString &newPath);

    void onCollapsed(const QModelIndex &index);
    void onExpanded(const QModelIndex &index);
    void onItemClicked(const QModelIndex &index);
private:
    QStandardItemModel * imagemodel;
    QTableView * imageview;
};
#endif // WIDGET_H

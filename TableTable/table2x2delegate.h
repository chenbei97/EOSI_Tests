﻿#ifndef TABLE2X2DELEGATE_H
#define TABLE2X2DELEGATE_H

#include    <QStyledItemDelegate>
#include "tablewidgetbase.h"
#include <QDebug>
#include <QPixmap>

class Table2x2Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    Table2x2Delegate(QObject *parent=0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // TABLE2X2DELEGATE_H

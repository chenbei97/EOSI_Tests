#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include "qstyleditemdelegate.h"
#include "qpainter.h"
#include "qevent.h"
#include "qlabel.h"

class ImageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
//    void setModelData(QWidget *editor, QAbstractItemModel *model,
//                      const QModelIndex &index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) Q_DECL_OVERRIDE;
};

#endif // IMAGEDELEGATE_H

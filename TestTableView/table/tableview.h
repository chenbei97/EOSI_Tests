#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <qtableview.h>
#include <qheaderview.h>
#include <qevent.h>
#include "Constant.h"

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr);
    void updateGeometries() override;
    void rowsInserted(const QModelIndex &parent, int start, int end) override;
    bool edit(const QModelIndex &index, QAbstractItemView::EditTrigger trigger, QEvent *event) override;
//    void openPersistentEditor(const QModelIndex &index);
    void updateCellSize();
private:
    void initGeneralConfig();
private slots:
    void onClicked(const QModelIndex &index);
    void onDoubleClicked(const QModelIndex &index);
    void onPressed(const QModelIndex &index);

};

#endif // TABLEVIEW_H

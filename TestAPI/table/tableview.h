#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <qtableview.h>
#include <qheaderview.h>
#include "Constant.h"

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr);
    void updateGeometries() override;
    void rowsInserted(const QModelIndex &parent, int start, int end) override;

    void updateCellSize();
private:
    void initGeneralConfig();

};

#endif // TABLEVIEW_H

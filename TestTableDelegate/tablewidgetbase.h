#ifndef TABLEWIDGETBASE_H
#define TABLEWIDGETBASE_H

#include <qtablewidget.h>
#include <qheaderview.h>
#include <qtabbar.h>
#include <qscrollbar.h>
#include "Constant.h"
#include "Style.h"

class TableWidgetBase : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableWidgetBase(int rows,int cols,QWidget * parent = nullptr);
    TableWidgetBase* clone();
};

#endif // TABLEWIDGETBASE_H

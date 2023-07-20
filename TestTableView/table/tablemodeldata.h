#ifndef TABLEMODELDATA_H
#define TABLEMODELDATA_H

#include <qvariant.h>
#include <qdatastream.h>
#include "Constant.h"

/*
重载抽象表格模型项目内部使用的数据结构对象，指定角色和数据
每个项存储了不同角色的值
*/
/*自定义的数据角色*/
enum TableModelDataRole {
    MousePosition = Qt::UserRole + 1,
    HighlightBorderColor = Qt::UserRole + 2,
    HighlightBackColor = Qt::UserRole + 3,
};

Q_ENUMS(TableModelDataRole)
Q_DECLARE_METATYPE(TableModelDataRole)

class TableModelData
{
public:
    TableModelData();
    TableModelData(int r,const QVariant&v);
    int role;
    QVariant value;

    bool operator==(const TableModelData &other) const;
};
Q_DECLARE_TYPEINFO(TableModelData, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(TableModelData)

#endif // TABLEMODELDATA_H

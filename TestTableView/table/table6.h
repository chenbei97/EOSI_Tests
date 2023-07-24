#ifndef TABLE6_H
#define TABLE6_H

#include "table.h"

class Table6 : public Table
{
    Q_OBJECT
public:
    explicit Table6(QWidget *parent = nullptr);
    void initialize() override;
};


#endif // TABLE6_H

#ifndef TABLEVIEWWIDGET2X2_H
#define TABLEVIEWWIDGET2X2_H

#include <qevent.h>
#include "label.h"

class TableViewWidget2x2: public QWidget
{
    Q_OBJECT
private:
    QVector<Label*> mLabels;
    QVector<QPixmap*> mPixs;
public:
    explicit TableViewWidget2x2(QWidget *parent = nullptr);

    void setPixmap(int index,QPixmap*pix);
    QPixmap* pixmap(int index) const;
    QVector<QPixmap*> pixmaps() const;
signals:

};

Q_DECLARE_METATYPE(QVector<QPixmap*>)
#endif // TABLEVIEWWIDGET2X2_H

#ifndef FLITER_H
#define FLITER_H

#include <QObject>
#include <QEvent>

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:

};

#endif // FLITER_H

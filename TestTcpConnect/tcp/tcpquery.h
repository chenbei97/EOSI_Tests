#ifndef TCPQUERY_H
#define TCPQUERY_H

#include <QObject>
#include "tcploader.h"

class TcpQuery : public QObject
{
    Q_OBJECT
public:
    explicit TcpQuery(QObject *parent = nullptr);
    bool exec(int frame);
    QString result() const;
    QString error() const;
private:
    TcpSocket * socket;
signals:

};

#endif // TCPQUERY_H

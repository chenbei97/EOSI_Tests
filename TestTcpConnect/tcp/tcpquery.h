#ifndef TCPQUERY_H
#define TCPQUERY_H

#include <QObject>
#include <QMessageBox>
#include "tcploader.h"

class TcpQuery : public QObject
{
    Q_OBJECT
public:
    explicit TcpQuery(QObject *parent = nullptr);
    bool exec(int frame);
    QString result() const;
    QString error() const;
    QString errorCode() const;
private:
    TcpSocket * socket;
    QString mIP;
    int mPort;
    TcpErrorCode mErrorCode;
signals:

};

#endif // TCPQUERY_H

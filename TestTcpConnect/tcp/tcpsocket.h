#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include "tcpdealer.h"

enum TcpErrorCode {
    NoResponse = -1,
    EmptyData = -2,
    FrameError = -3,
    RequestError = -4,
    NoError=1,
};
Q_ENUMS(TcpErrorCode)
Q_DECLARE_METATYPE(TcpErrorCode)

class TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = nullptr);
    ~TcpSocket();

    void connectToHost(const QHostAddress &address, quint16 port,
                       QIODevice::OpenMode openMode = QIODevice::ReadWrite);
    void connectToHost(const QString &hostName, quint16 port,
                       QIODevice::OpenMode openMode = QIODevice::ReadWrite);

    void disconnectFromHost();

    bool isOpen() const;

    bool waitForConnected(int msecs = 30000);

    bool setSocketDescriptor(qintptr socketDescriptor);
    qintptr socketDescriptor() const;

    TcpErrorCode exec(int frameID);
    QString result() const ;
    QString error() const;
private:
    QTcpSocket * socket = nullptr;
    int command;
    QByteArray message;
    QHash<int,QString> data;
    TcpDealer * dealer;
    void onReadyReadSlot();
signals:
    void commandChanged(int);
};

#endif // TCPSOCKET_H

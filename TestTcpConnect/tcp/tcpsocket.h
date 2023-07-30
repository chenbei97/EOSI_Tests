#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QApplication>
#include <QTimer>
#include <QThread>
#include <QEventLoop>
#include <QTimer>
#include <QMessageBox>
#include "tcpdealer.h"

enum TcpErrorCode {
    EmptyDataError,
    FrameError,
    RequestError,
    ResponseError,
    UnConnectedError,
    NoError,
};
static const char* TcpErrorString[] = {
    "EmptyDataError",
    "FrameError",
    "RequestError",
    "ResponseError",
    "UnConnectedError",
    "NoError",
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
    bool isConnected() const;

    bool waitForConnected(int msecs = 30000);

    bool setSocketDescriptor(qintptr socketDescriptor);
    qintptr socketDescriptor() const;

    TcpErrorCode exec(int frameID);
    QString result() const ;
    QString error() const;
private:
    QTcpSocket * socket = nullptr;
    int command ;
    QByteArray message;
    QHash<int,QString> data;
    TcpDealer * dealer;
    bool mConnected;
    void onReadyReadSlot();

//    QTimer timer;

signals:
    void commandChanged(int);
};

#endif // TCPSOCKET_H

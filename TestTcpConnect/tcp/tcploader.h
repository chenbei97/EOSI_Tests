#ifndef TCPLOADER_H
#define TCPLOADER_H

#include "tcpsocket.h"

class TcpQuery;
class TcpLoader : public QObject
{
    Q_OBJECT
public:
    friend class TcpQuery;
    static TcpLoader& instance();
    void open(const QString &ip, quint16 port,
              QIODevice::OpenMode openMode = QIODevice::ReadWrite);
    bool isOpen() const; // 不能用于判断连接上
    bool isConnected() const;

    QString ip() const;
    int port() const;
private:
    TcpSocket * mSocket = nullptr;
    QString mIP;
    int mPort;
private:
    explicit TcpLoader(QObject *parent = nullptr);
    TcpLoader(const TcpLoader&){}
    TcpLoader operator= (const TcpLoader&){return *this;}
    ~TcpLoader(){}
signals:

};



#endif // TCPLOADER_H

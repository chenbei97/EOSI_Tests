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
    bool isOpen() const;
private:
    TcpSocket * mSocket = nullptr;
private:
    explicit TcpLoader(QObject *parent = nullptr);
    TcpLoader(const TcpLoader&){}
    TcpLoader operator= (const TcpLoader&){return *this;}
    ~TcpLoader(){}
signals:

};



#endif // TCPLOADER_H

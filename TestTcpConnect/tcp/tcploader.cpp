#include "tcploader.h"

TcpLoader& TcpLoader::instance()
{
    static TcpLoader instance;
    return instance;
}

TcpLoader::TcpLoader(QObject*parent):QObject(parent)
{
    mSocket = new TcpSocket(this);
    //qDebug()<<__FUNCTION__;
}

void TcpLoader::open(const QString &ip, quint16 port, QIODevice::OpenMode openMode)
{
    //qDebug()<<"open is called";
    mSocket->connectToHost(ip,port,openMode);
    mIP = ip;
    mPort = port;
}

bool TcpLoader::isOpen() const
{
    return mSocket->isOpen();
}

bool TcpLoader::isConnected() const
{
    return mSocket->isConnected();
}

QString TcpLoader::ip() const
{
    return mIP;
}

int TcpLoader::port() const
{
    return  mPort;
}

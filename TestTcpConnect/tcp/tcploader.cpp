#include "tcploader.h"

TcpLoader& TcpLoader::instance()
{
    static TcpLoader instance;
    return instance;
}

TcpLoader::TcpLoader(QObject*parent):QObject(parent)
{
    mSocket = new TcpSocket(this);
}

void TcpLoader::open(const QString &ip, quint16 port, QIODevice::OpenMode openMode)
{
    mSocket->connectToHost(ip,port,openMode);
}

bool TcpLoader::isOpen() const
{
    return mSocket->isOpen();
}

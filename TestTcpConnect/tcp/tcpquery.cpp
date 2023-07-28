#include "tcpquery.h"

TcpQuery::TcpQuery(QObject *parent) : QObject(parent)
{
    socket = TcpLoader::instance().mSocket;
    Q_ASSERT(socket!=0);
}

bool TcpQuery::exec(int frame)
{
    qDebug()<<3;
    TcpErrorCode code =  socket->exec(frame);
    qDebug()<<"code = "<<code;
    if (code == NoError) return true;

    // ...对错误码可以做一些事
    switch (code) {
           case NoResponse:break;
           case EmptyData:break;
            default:break;
    }

    return false;
}

QString TcpQuery::result() const
{// exec成功时再调用本函数才有意义
    return socket->result();
}

QString TcpQuery::error() const
{
    return socket->error();
}

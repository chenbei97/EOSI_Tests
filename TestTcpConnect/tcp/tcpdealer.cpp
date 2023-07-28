#include "tcpdealer.h"

void TcpDealer::parse()
{

}


TcpDealer::TcpDealer(QObject *parent) : QObject(parent)
{
    connect(this,&TcpDealer::dataChanged,this,&TcpDealer::parse);
}

TcpDealer::TcpDealer(const QByteArray&d,QObject *parent)
    :QObject(parent)
{
    connect(this,&TcpDealer::dataChanged,this,&TcpDealer::parse);
    setData(d);
}

void TcpDealer::setData(const QByteArray&d)
{
    qDebug()<<"data = "<<d;
    if (d != Data) {
        emit dataChanged();
        Data = d;
    }
}

QByteArray TcpDealer::data() const
{
    return Data;
}

QString TcpDealer::data1() const
{
    return  "";
}



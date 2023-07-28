#include "tcpsocket.h"

void TcpSocket::onReadyReadSlot()
{ // 回复的信息应该是帧头<数据>帧尾
  // 根据帧头 把数据存入不同的位置
    message = socket->readAll();
    // 处理响应command的message,把数据解析保存
    dealer->setData(message);
    data[command] = dealer->data1();
    //...
data[command] = message;
}

QString TcpSocket::result() const
{ // 用于查询完可以理解得到结果
    return *data.find(command);;
}

TcpErrorCode TcpSocket::exec(int frameID)
{
    //  1. 数字帧头是否有错误,应在某个范围内(自行规定)
    qDebug()<<4;
    if (frameID <0)
        return FrameError;

    //command = frameID; // 要在write之前赋值,否则槽函数响应很快command还没改变就会出错
    if (command != frameID)
        emit commandChanged(frameID); // 用信号机制可能更快
qDebug()<<5;
    // 2. 写入是否有错误
    int count = socket->write(QByteArray::number(frameID));
    if (count <= 0) return RequestError;
qDebug()<<6;
    // 3. 数据尚未有此帧头,说明没有收到回复
    if (data.keys().contains(command))
        return NoResponse;
qDebug()<<7;
    // 4. 数据是不是空的
qDebug()<<data<<"  command = "<<command;
    auto d = data.find(command);
    if (d == data.end()) return EmptyData;
qDebug()<<8;
    return NoError;
}

TcpSocket::TcpSocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    dealer = new TcpDealer(this);
    connect(socket,&QTcpSocket::readyRead,this,&TcpSocket::onReadyReadSlot);
    connect(this,&TcpSocket::commandChanged,this,[=](int frameID){command = frameID;});
}

void TcpSocket::connectToHost(const QHostAddress &address, quint16 port,
                   QIODevice::OpenMode openMode){
    socket->connectToHost(address,port,openMode);
}

void TcpSocket::connectToHost(const QString &hostName, quint16 port,
                   QIODevice::OpenMode openMode){
    socket->connectToHost(hostName,port,openMode);
}

void TcpSocket::disconnectFromHost() {
    socket->disconnectFromHost();
}

bool TcpSocket::waitForConnected(int msecs) {
    return socket->waitForConnected(msecs);
}

bool TcpSocket::setSocketDescriptor(qintptr socketDescriptor) {
    return socket->setSocketDescriptor(socketDescriptor);
}

qintptr TcpSocket::socketDescriptor() const {
    return socket->socketDescriptor();
}

QString TcpSocket::error() const {
    return socket->errorString();
}

bool TcpSocket::isOpen() const
{
    return socket->isOpen();
}

TcpSocket::~TcpSocket()
{
    if(socket) {
        socket->disconnectFromHost();
        socket->close();
    }
}

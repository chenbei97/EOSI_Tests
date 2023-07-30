#include "tcpsocket.h"


void TcpSocket::onReadyReadSlot()
{ // 回复的信息应该是帧头<数据>帧尾
  // 根据帧头 把数据存入不同的位置
    message = socket->readAll();
    // 处理响应command的message,把数据解析保存
    dealer->setData(message);
    //data[command] = dealer->data1();
    //...

    data[command] = message.simplified();
    //qDebug()<<"data["<<command<<"] = "<<data[command];
}

QString TcpSocket::result() const
{ // 用于查询完可以得到结果,可以是空的,也可能还没有command
    // 如果是因为未连接,帧和请求错误,command尚未创建
    if (data.find(command) == data.end()) return "";
    return *data.find(command);;
}

#define SYNC1 0
TcpErrorCode TcpSocket::exec(int frameID)
{
//     QTimer timer;
//     QEventLoop loop;
//    connect(&timer,&QTimer::timeout,this,[&]{
//        if (!isConnected())  {
//            QMessageBox::critical(nullptr,"错误","检测到套接字意外退出连接!",QMessageBox::Ok);
//            timer.stop();
//        }
//        loop.quit();
//    });
//    timer.start(0);
//    loop.exec();
//    if (!timer.isActive()) return UnConnectedError;

    // 0. 每次查询都要检查连接是否已连接
    //if (!socket->isOpen()) return UnConnectedError; // bu能用isOpen判断打开了但是没连接上
    if (!isConnected()) return UnConnectedError;

//    while (mConnected) {

        //  1. 数字帧头是否有错误,应在某个范围内(自行规定)
        if (frameID <0)
            return FrameError;

        //command = frameID; // 要在write之前赋值,否则槽函数响应很快command还没改变就会出错
        if (command != frameID)
            emit commandChanged(frameID); // 用信号机制可能更快

        //qDebug()<<"change command = "<<command; // 证明确实发生了响应

    #ifdef SYNC1
        // （1）写法1
        // 2. 请求是否有错误
        QEventLoop loop1;
        QTimer timer1;
        timer1.setSingleShot(true);
        connect(&timer1, &QTimer::timeout, this,[&]{ loop1.quit();});
        connect(socket,&QTcpSocket::bytesWritten,&loop1,&QEventLoop::quit);
        socket->write(QByteArray::number(frameID));
        timer1.start(3000);
        loop1.exec(); // 如果没有写入成功会一直阻塞
        if (!isConnected()) {
            QMessageBox::critical(nullptr,"错误","检测到套接字意外退出连接!",QMessageBox::Ok);
            return UnConnectedError;
        }
        if (!timer1.isActive()) return RequestError;

        // 3. 回复是否有错误
        QEventLoop loop2;
        QTimer timer2;
        timer2.setSingleShot(true);
        connect(&timer2, &QTimer::timeout, this,[&]{
                data[command] = ""; // 如果超时要清空上次数据,没超时,数据已被更新不需要清空
                loop2.quit(); // 限制没收到消息超时指定时间退出,
               // return ResponseError; // 这里无法返回,会直接跳到后边
            });
        connect(socket,&QTcpSocket::readyRead,&loop2,&QEventLoop::quit);
        timer2.start(3000);
        loop2.exec(); // 同步执行
        if (!isConnected()) {
            QMessageBox::critical(nullptr,"错误","检测到套接字意外退出连接!",QMessageBox::Ok);
            return UnConnectedError;
        }
        if (!timer2.isActive()) return ResponseError; // 如果是超时退出事件循环的
    #else
        // （2）写法2
    //       2. 请求是否有错误
            int count = socket->write(QByteArray::number(frameID));
            if (count <= 0) return RequestError;
    //         3. 回复是否有错误
        if (!socket->waitForReadyRead(2000))
        { // 这里会卡
            qApp->processEvents();
            data[command] = "";//1.command首次exec,事先没有command这个键值,先创建键值并置空
            // 2. command不是首次exec,清除之前的数据,之前的查询不能作数
            return ResponseError;
        }
    #endif
        //qDebug()<<"data["<<command<<"] = "<<data[command]; // 证明结束阻塞后,确实数据改变了
        if (!isConnected()) {
            QMessageBox::critical(nullptr,"错误","检测到套接字意外退出连接!",QMessageBox::Ok);
            return UnConnectedError;
        }
        if (data[command].isEmpty()) return  EmptyDataError; // 但是数据""本身也是数据,不能为空

        return NoError;
//    }
    //QMessageBox::critical(nullptr,"错误","意外退出!",QMessageBox::Ok);
//    return UnConnectedError;
}

TcpSocket::TcpSocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    dealer = new TcpDealer(this);

    connect(socket,&QTcpSocket::readyRead,this,&TcpSocket::onReadyReadSlot);
    connect(this,&TcpSocket::commandChanged,this,[=](int frameID){command = frameID;});
    //connect(socket,&QTcpSocket::bytesWritten,this,[=]{qDebug()<<"socket's bytesWritten is emit";});
    //connect(socket,&QTcpSocket::readyRead,this,[=]{qDebug()<<"socket's readyRead is emit";});
}

void TcpSocket::connectToHost(const QHostAddress &address, quint16 port,
                   QIODevice::OpenMode openMode){
    socket->connectToHost(address,port,openMode);

}

void TcpSocket::connectToHost(const QString &hostName, quint16 port,
                   QIODevice::OpenMode openMode){
    socket->connectToHost(hostName,port,openMode);
//    qDebug()<<"socket = "<<socket->peerAddress()<<" "<<socket->peerPort()<<"  "<<socket->peerName()
//           <<"  "<<socket->localAddress()<<"  "<<socket->localPort();
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

bool TcpSocket::isConnected() const
{
    return socket->state() == QTcpSocket::ConnectedState;
}

TcpSocket::~TcpSocket()
{
    if(socket) {
        socket->disconnectFromHost();
        socket->close();
    }
}

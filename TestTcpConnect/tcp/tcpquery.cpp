#include "tcpquery.h"

TcpQuery::TcpQuery(QObject *parent) : QObject(parent)
{
    socket = TcpLoader::instance().mSocket;
    mIP = TcpLoader::instance().mIP;
    mPort = TcpLoader::instance().mPort;
    Q_ASSERT(socket!=0);
}

bool TcpQuery::exec(int frame)
{
    mErrorCode =  socket->exec(frame);

    if (mErrorCode == NoError) return true;

    while  (mErrorCode == UnConnectedError)
    {
         unsigned int i = 0;
         bool r = false;
         int ret ;
         while (!r && i<5)
         {
              ret = QMessageBox::critical(nullptr,tr("错误"),tr("未连接,尝试重连? [%1]").arg(i+1),
                                          QMessageBox::Yes | QMessageBox::No);
             if (ret == QMessageBox::Yes) {
                 socket->connectToHost(mIP, mPort);
                 bool r = socket->waitForConnected(20000);
                 if (!r) QMessageBox::critical(nullptr,"错误","重连失败!",QMessageBox::Ok);
                 else break;
             }
             else break;
             ++i;
         }
         if (ret == QMessageBox::No) break;

         if (i >= 5) {
             QMessageBox::critical(nullptr,"错误","已尝试5次,退出!",QMessageBox::Ok);
             break;
         }
        else {
             QMessageBox::information(nullptr,"消息","重连成功,正在重发消息!",QMessageBox::Ok);
             mErrorCode = socket->exec(frame);
         }
    }

    switch (mErrorCode) {
        case ResponseError:
            QMessageBox::critical(nullptr,"错误","回复超时!",QMessageBox::Ok);
            break;
        case RequestError:
            QMessageBox::critical(nullptr,"错误","请求超时!",QMessageBox::Ok);
            break;
        case FrameError:
            QMessageBox::critical(nullptr,"错误","发送帧错误!",QMessageBox::Ok);
            break;
        case EmptyDataError:
            QMessageBox::critical(nullptr,"错误","回复空数据!",QMessageBox::Ok);
            break;
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

QString TcpQuery::errorCode() const
{
    return TcpErrorString[mErrorCode];
}

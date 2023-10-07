#include <QApplication>
#include <QProcess>
#include <QDir>
#include <QDebug>
#include <Python.h>
#include <QMainWindow>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QTcpSocket * socket = new QTcpSocket();
//    socket->connectToHost ("127.0.0.1",3011);

    //socket->waitForConnected (1000);
//    qDebug()<<socket->isOpen ();
    qDebug()<<QDir::currentPath ();
    Py_SetPythonHome ((wchar_t*)(L"python310"));
    wchar_t * str = Py_GetPythonHome();
    qDebug()<<QString::fromWCharArray(str);
    Py_Initialize ();
    if (!Py_IsInitialized()){qDebug()<< "inital python failed!";return -1;
    }else qDebug()<< "inital python successful!";
    //PyRun_SimpleString("import os,sys");
    //PyRun_SimpleString("print(os.getcwd())");
    PyObject* pModule = PyImport_ImportModule("test_socket");

    if (!pModule){ qDebug()<<"cant open python file!";return -1;
     } else qDebug()<<"open python file successful!";

    PyObject* pFunc= PyObject_GetAttrString(pModule,"test_server"); // 调用函数

    if(!pFunc){qDebug()<<"load tcp server failed";return -1;
    } else qDebug()<<"load tcp server successful";

     PyObject_CallFunction(pFunc,Q_NULLPTR);

//    socket->write ("{\"frame\":\"0x0002\",\"point.x\":3,\"point.y\":5}");
//    qDebug()<<socket->readAll ();
    Py_Finalize ();


    return a.exec();
}

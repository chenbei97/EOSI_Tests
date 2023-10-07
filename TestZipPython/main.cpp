#include <QApplication>
#include <QProcess>
#include <QDir>
#include <QDebug>
#include <Python.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug()<<QDir::currentPath ();
    Py_SetPythonHome ((wchar_t*)(L"python310"));
    wchar_t * str = Py_GetPythonHome();
    qDebug()<<QString::fromWCharArray(str);
    Py_Initialize ();
    if (!Py_IsInitialized())
        {
            qDebug() << "inital python failed!";
            return -1;
        }
    PyRun_SimpleString("import os,sys");
    PyRun_SimpleString("print(os.getcwd())");

    PyObject* pModule = PyImport_ImportModule("test_socket");
    if (!pModule)
     {
         qDebug()<<"Cant open python file!\n";
         return -1;
     }
    PyObject* pFunshow= PyObject_GetAttrString(pModule,"test_server"); // 调用函数
        if(!pFunshow){
            qDebug()<<"load server failed";
            return -1;
        }
     PyObject_CallFunction(pFunshow,Q_NULLPTR);
    Py_Finalize ();
    return a.exec();
}

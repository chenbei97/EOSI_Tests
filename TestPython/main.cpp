#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QDir>

//#include <Python.h>

int main(int argc, char *argv[])
{
    auto path = "../../EOSI_Tests/TestPython/cos.py";
    QCoreApplication a(argc, argv);
    QProcess process;
    QObject::connect(&process, &QProcess::readyReadStandardOutput,[&](){
        //qDebug()<<process.readAll();
        auto output = QString(process.readAllStandardOutput()); // 直接读读不到
        auto res = output.split("\r\n",QString::SkipEmptyParts);// 必须槽函数内才能读到
        qDebug()<<res;
        //qDebug()<<process.readAll(); // 读完就没了
    });
    process.setProgram("python");
    process.setArguments(QStringList()<<path<<"chenbei");
    process.start();

//    process.start("python",QStringList()<<"-c"<<"print('hello qt!')"); // 可以打印出信息
    //process.start("cmd.exe", QStringList() << "/c" << "dir");
    // 静态阻塞可以直接打印信息，但是只是终端打印不能拿来用
    //QProcess::execute(QString("python %1 '123' ").arg(path));


    //Py_Initialize();
    //py::object test = py::module::import("test"); // 导入 Python 中的 test 模块
//    py::object result = test.attr("test_function")(); // 调用 test_function 函数
//    qDebug() << (result.cast<QString>()); // 输出函数返回的结果

    return a.exec();
}


void test1()
{
    auto path = "../../EOSI_Tests/TestPython/cos.py";
    QProcess *process = new QProcess;
    process->setReadChannel(QProcess::StandardOutput);
    process->setProcessChannelMode(QProcess::MergedChannels);
//    QObject::connect(process,&QProcess::finished,[](int exitCode, QProcess::ExitStatus exitStatus)
//    {qDebug()<<"started!";});
    QObject::connect(process,&QProcess::errorOccurred,[=]{qDebug()<<process->errorString();});
    process->start("python", QStringList()<<path<<"kkkk");
    qDebug() << process->workingDirectory();
    qDebug() << process->nativeArguments();
    qDebug() << process->program();
    //qDebug()<<QProcess::systemEnvironment();
    qDebug()<<QProcess::nullDevice();
    if (process->waitForStarted()) {
//        qDebug() << process->readAllStandardOutput();
//        qDebug() << process->readAllStandardError();
        qDebug()<<process->readAll();

    } else {

    }
    qDebug()<<process->exitCode();
    qDebug()<<QDir::currentPath();
    //process->close();

    //QProcess::execute("python", QStringList() <<path );

}

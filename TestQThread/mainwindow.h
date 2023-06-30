#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <qboxlayout.h>
#include <QDebug>
#include <QRandomGenerator>
#include <QStatusBar>
#include <QGroupBox>
#include <QThread>
#include <QTime>

#define MAXCOUNT 100000000

class MyThread : public QThread{
    Q_OBJECT
private:
    void run() override
    {
        QRandomGenerator RG(QTime::currentTime().msec());
        long long result = 0;
        QTime s;
        s.start();
        for (long long i = 0; i < MAXCOUNT; ++i)
        {
            //result += RG.bounded(low,high); // 无法传递外部参数
            result += RG.bounded(-50,88);
        }
        auto t = s.elapsed() / 1000.0;
        emit ready(QString("耗时: %1 s  结果: %2\n").arg(t).arg(result));
    }
signals:
    void ready(const QString&res);
};

class  Calculator : public QObject
{
        Q_OBJECT
public slots:
    void doRandom(int low, int high) // 相比重载run外部还可以提供参数进来更灵活
    {
        QRandomGenerator RG(QTime::currentTime().msec());
        long long result = 0;
        QTime s;
        s.start();
        for (long long i = 0; i < MAXCOUNT; ++i)
        {
            result += RG.bounded(low,high);
        }
        auto t = s.elapsed() / 1000.0;
        emit ready(QString("耗时: %1 s  结果: %2\n").arg(t).arg(result));
    }
signals:
    void ready(const QString&res);
};

class Controller:public QObject
{
    Q_OBJECT
    QThread mThread;
    QStatusBar * mBar;
public:
    Controller(QStatusBar*bar) :mBar(bar) {
        Calculator *worker = new Calculator;// ① 新建一个工作对象(如果是属于类的下方不需要连接deleteLater)
        worker->moveToThread(&mThread); // ② 工作对象移入子线程
        connect(&mThread, &QThread::finished, worker, &QObject::deleteLater); // ③ 线程结束后删除workder对象

        connect(this, &Controller::start, worker, &Calculator::doRandom); // ④ 按钮需要操作start信号,这个信号绑定了要执行的计算
        connect(worker, &Calculator::ready, this, &Controller::handleResults); // ⑤ 工作对象的完成信号可以反馈给控制器也要绑定好
        mThread.start();
    }
    ~Controller() {
        mThread.quit();
        mThread.wait();
    }
private slots:
    void handleResults(const QString& res)
    {
        mBar->showMessage(res);
    }
signals:
    void start(int low,int high); // 这个信号可以和按钮的信号绑定
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
    MyThread mThread;
    Controller * mController;
private:
    QPushButton * btn1;
    QPushButton * btn2;
    QPushButton * btn3;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
//    void onbtn1();
//    void onbtn2();
//    void onbtn3();
};
#endif // MAINWINDOW_H

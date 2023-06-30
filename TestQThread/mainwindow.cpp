#include "mainwindow.h"
//#define MAXCOUNT 1000000000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    btn1 = new QPushButton(tr("没有线程"));
    btn2 = new QPushButton(tr("重载线程"));
    btn3 = new QPushButton(tr("移动线程"));

    connect(btn1,&QPushButton::clicked,[this] { // 主线程会卡死
        QRandomGenerator RG(QTime::currentTime().msec());
        long long val = 0;
        QTime s;
        s.start();
        for (long long i = 0; i < MAXCOUNT; ++i)
        {
            val += RG.bounded(-50,100);
            //qDebug()<<val;
        }
        auto t = s.elapsed() / 1000.0;
        statusBar()->showMessage(QString("耗时: %1 s  结果: %2\n").arg(t).arg(val));
    });

    // 重载run的线程
    // button-clicked=>mThread.start()=>run()=>ready=>showmessage
    connect(&mThread, &MyThread::ready, this,[this](const QString&res){statusBar()->showMessage(res);});
    //connect(&mThread, &MyThread::finished, &mThread, &QObject::deleteLater); // 不能删除否则再次点击异常
    connect(btn2,&QPushButton::clicked,this,[this]{mThread.start();});

    // 移动线程的做法
    // mController::start(emit start)=>Calculator::doRandom=>emit ready => mController::handle
    mController = new Controller(statusBar());
    connect(btn3,&QPushButton::clicked,[this] {
            mController->start(-100,100);
    });

    QHBoxLayout * lay = new QHBoxLayout;
    lay->addStretch();
    lay->addWidget(btn1);
    lay->addWidget(btn2);
    lay->addWidget(btn3);
    lay->addStretch();
    QGroupBox * box = new QGroupBox;
    box->setLayout(lay);
    setCentralWidget(box);
    resize(800,600);
    setFont(QFont("Times New Roman",12));
}

MainWindow::~MainWindow()
{
}

//void MainWindow::onbtn1(){

//    for (long long i = 0; i < MAXCOUNT; ++i)
//    {
//        statusBar()->showMessage(QString::number(RG.bounded(0,100)));
//    }
//}
//void MainWindow::onbtn2(){

//}
//void MainWindow::onbtn3(){

//}


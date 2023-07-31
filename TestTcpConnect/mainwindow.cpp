#include "mainwindow.h"
#include "fliter.h"
#include <QPushButton>
#include <QStatusBar>
#include <QDebug>
#include <QSplitter>
#include <QHoverEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    TcpLoader* instance = &TcpLoader::instance();
    instance->open("192.168.1.168",3000); // 192.168.31.36 127.0.0.1 192.168.1.168
    //qDebug()<<"instance's addr = "<<instance<<" isOpen? "<< instance->isOpen();

        Filter * filter = new Filter; // 必须是指针,临时对象不起作用
    QPushButton * btn = new QPushButton("查询");
    //btn->installEventFilter(filter); // 会拦截鼠标事件
//    setCentralWidget(btn);
    connect(btn,&QPushButton::clicked,this,[=]{
        TcpQuery query;
         query.exec(100);
        qDebug()<<"result = "<<query.result();
        qDebug()<<query.errorCode();
        // 下方的重发逻辑不要在这写，在tcpquery内写
//        unsigned int i = 0;
//        while (!query.exec(100) && i <5) {
//            ++i;
//            qDebug()<<"i = "<<i <<" errorCode = "<<query.errorCode();
//        }
//        if (i >= 5) qDebug()<<"try 5 times is fail";
//       qDebug()<<"result = "<<query.result();
    });


    // 当前的事件过滤也可以拿来使用
    mLabel = new QLabel("filter");
    mLabel->installEventFilter(this);
    mBtn = new QPushButton("过滤");
    mBtn->installEventFilter(this);


    QSplitter * s = new QSplitter;
    s->addWidget(btn);
    s->addWidget(mBtn);
    s->addWidget(mLabel);
    setCentralWidget(s);
    resize(800,600);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == mLabel) {
        if (e->type() == QEvent::MouseButtonPress)
        {
            qDebug()<<"label";
        }
    }
    if (obj == mBtn) {
        if (e->type() == QEvent::MouseButtonPress)
        {
            mBtn->setStyleSheet("background-color:red");

            qDebug()<<"pushbutton";
        }
        else if (e->type() == QEvent::HoverEnter || e->type() == QEvent::HoverLeave)
        {
            mBtn->setStyleSheet("background-color:white");
        }
//        else {
//            mBtn->setStyleSheet("background-color:white");
//        }
    }
    return QMainWindow::eventFilter(obj, e);
}

MainWindow::~MainWindow()
{
}


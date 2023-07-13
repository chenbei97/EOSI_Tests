#include "widget.h"
#include <QDebug>
#include <QPushButton>
#include <QLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    CreateWin * win = new CreateWin;
    win->moveToThread(&mThread);

    connect(&mThread, &QThread::finished, win, &QObject::deleteLater);
    connect(win, &CreateWin::createStarted, this, [=]{
        qDebug()<<"started";
    });
    connect(win, &CreateWin::createFinished, this, [=]{
        qDebug()<<"finished";

    });
    mThread.start();

    QPushButton * btn = new QPushButton("创建");
    connect(btn,&QPushButton::clicked,win,&CreateWin::create);
//ASSERT failure in QWidget: "Widgets must be created in the GUI thread.",
    QVBoxLayout * lay = new QVBoxLayout;
    lay->addWidget(btn);
    setLayout(lay);
    resize(400,300);
}

Widget::~Widget()
{
    mThread.quit();
    mThread.wait();
}


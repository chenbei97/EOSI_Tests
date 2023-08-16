#include "mainwindow.h"
#include "picture.h"
#include <QTimer>
#include <QApplication>
#include <QDebug>
#include <QEventLoop>

//#define t1 0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    V2::Picture w;
    QString path(":%1.jpg");
    QPixmap pix;
    QTimer timer;
    w.show(); // 先显示窗口再开启定时器有利于感官效果
#ifdef t1
    pix.load(path.arg(1)); // 先加载第1张,超时加载第2张
    w.setPixmap(&pix);
    int i = 2;
    QObject::connect(&timer, &QTimer::timeout, [&]{
                pix.load(path.arg(i));
                w.setPixmap(&pix); // 定时设置图片
                ++i;
                if (i == 5) timer.stop();
    });

    timer.start(2000);
 #else
    QEventLoop loop; // 借助同步
    //timer.setSingleShot(true);
    QObject::connect(&timer, &QTimer::timeout, &loop,&QEventLoop::quit); // 超时就停止
    timer.start(1200);
    for(int i = 1; i <=4; ++i) { // 开始循环加载图片,加载后阻塞等待超时退出阻塞
        pix.load(path.arg(i));
        w.setPixmap(pix);
        //timer.start(2000); // 每次循环重启定时器
        loop.exec(); // 每次循环都要阻塞
    }
    timer.stop();
    // 也可以timer设为单次触发在循环里重新start,那么结束循环不需要手动stop
#endif
    return a.exec();
}

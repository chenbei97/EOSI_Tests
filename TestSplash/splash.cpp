#include "splash.h"
#include <QDebug>

Splash::Splash(const QPixmap &pixmap)
{
    setPixmap(pixmap);
    setWindowFlag(Qt::WindowStaysOnTopHint);

    int ratio = 3;
    auto rect = screen()->availableGeometry();
    resize(rect.width()/ratio,rect.height()/ratio);
    move((rect.width()-width())/2,(rect.height()-height())/2);

    mBar = new QProgressBar(this);
    mBar->setGeometry(0,pixmap.height()-50,pixmap.width(),30);  // 高度-50是Y位置,也就到底部距离50
    mBar->setStyleSheet("QProgressBar {color:black;font:30px;text-align:center; }"
                        "QProgressBar::chunk {background-color:none}" //  rgb(202, 165, 14);
                        );
    mBar->setRange(0, 100);
    mBar->setValue(0);

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addStretch();
    lay->addWidget(mBar);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i =0;i<100;i++)
    {
        mValueList.append(qrand()%101);
    }

    std::sort(mValueList.begin(),mValueList.end()); //递增排序

    double tempTime=200;   // 2500ms  分成100份，每份执行25ms
    for(int i=0;i<100;i++)
    {   // 执行100次延时设置,
       QTimer::singleShot(i*tempTime, this, SLOT(updateProgress()));
    }
    //QTimer::singleShot(2500, this, SLOT(close()));  // 2.5s的时候就关掉
}

void Splash::mousePressEvent(QMouseEvent *e)
{
    e->ignore();
}

void Splash::updateProgress()
{
    static int num=0;
    mBar->setValue(mValueList[num]);

    //qDebug()<<num<<mValueList[num];
    num++;
    if (num == 100)
    {
        emit end();
        close();
    }
}

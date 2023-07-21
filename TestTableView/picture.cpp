#include "picture.h"


Picture::Picture(QWidget *parent) : QWidget(parent)
{
    mPix = new Label;
    mInfo = new Label;

    mMenu = new QMenu(this);
    mAction = new QAction(tr("导出"),this);
    mMenu->addAction(mAction);
    connect(mAction,&QAction::triggered,[=]{
        auto pix = mPix->pixmap();
        auto dir = QFileDialog::getExistingDirectory(this,tr("选择保存目录"));
        if (dir.isEmpty()) return ;
        pix->save(dir +"/"+ QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".jpg");
    });

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addWidget(mPix);
     lay->addWidget(mInfo);

     setContextMenuPolicy(Qt::CustomContextMenu);
     connect(this,&Picture::customContextMenuRequested,[=](const QPoint&){
         mMenu->exec(QCursor::pos());
     });

    INIT_FONT;
}

void Picture::resizeEvent(QResizeEvent *event)
{
    //auto size = event->size();
    //LOG<<"size = "<<size;

//    mPix->setGeometry(0,0,size.width(),size.height()*0.9);
//    mInfo->setGeometry(0,size.height()*0.8,size.width(),size.height()*0.1);
    event->accept();
}

void Picture::setPixmap(const QPixmap& pix)
{
    mPix->setPixmap(pix);
}

QPixmap Picture::pixmap() const
{
    return *mPix->pixmap();
}

void Picture::setInfo(const QString& info)
{
    mInfo->setText(info);
    mInfo->setToolTip(info);
}

QString Picture::info() const
{
    return mInfo->text();
}

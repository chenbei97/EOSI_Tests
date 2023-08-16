#include "picture.h"

//namespace PictureVersion {

    inline namespace  V1
    {
        Picture::Picture(QWidget *parent) : QWidget(parent)
        {
            mPix = new QLabel;
            mInfo = new QLabel;
            hideInfo();

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
            if (pix.isNull()) return;
            mPix->setPixmap(pix);
        }

        QPixmap Picture::pixmap() const
        {
            if (!mPix->pixmap())
                return QPixmap();
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

        void Picture::hideInfo()
        {
            mInfo->hide();
        }

        void Picture::showInfo()
        {
            mInfo->show();
        }
    } // endV1

    namespace V2
    {
        Picture::Picture(QWidget *parent) : QWidget(parent)
        {
            pixmap = nullptr;
            mMenu = new QMenu(this);
            mAction = new QAction(tr("导出"),this);
            mMenu->addAction(mAction);
            connect(mAction,&QAction::triggered,[=]{
                auto dir = QFileDialog::getExistingDirectory(this,tr("选择保存目录"));
                if (dir.isEmpty()) return ;
                pixmap->save(dir +"/"+ QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".jpg");
            });
            setContextMenuPolicy(Qt::CustomContextMenu);
            connect(this,&Picture::customContextMenuRequested,[=](const QPoint&){
                mMenu->exec(QCursor::pos());
            });
            mMenu->setEnabled(false);

            //resize(1000,800);
        }

        void Picture::setPixmap(QPixmap *pix)
        {
            if (pix) {
                resize(pix->size());
                qDebug()<<"size = "<<pix->size()<<size();
                pixmap = pix;
                mMenu->setEnabled(true);
                update();
            }
        }

        void Picture::setPixmap(const QPixmap&pix)
        {
            if (!pix.isNull()) {
                resize(pix.size());
                qDebug()<<"size = "<<pix.size()<<size();
                pixmap = &pix;
                mMenu->setEnabled(true);
                update();
            }
        }


        void Picture::paintEvent(QPaintEvent *event)
        {
            if (pixmap != nullptr) {
                QPainter painter(this);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.drawPixmap(rect(),*pixmap);
            }
            event->accept();
        }
    } // endV2

//}

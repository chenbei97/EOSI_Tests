#ifndef PICTURE_H
#define PICTURE_H

#include <qlayout.h>
#include <qevent.h>
#include <qmenu.h>
#include <qfiledialog.h>
#include <qdatetime.h>
#include <qpainter.h>
#include <QLabel>
#include <QDebug>

//namespace PictureVersion {

    inline namespace V1 {
        class Picture : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(QPixmap pixmap READ  pixmap WRITE setPixmap)
            Q_PROPERTY(QString info READ  info WRITE setInfo)

            QLabel * mPix;
            QLabel * mInfo;
            QMenu * mMenu;
            QAction * mAction;
        public:
            explicit Picture(QWidget *parent = nullptr);
            void resizeEvent(QResizeEvent *event) override;

            void setPixmap(const QPixmap& pix);
            QPixmap pixmap() const;

            void setInfo(const QString& info);
            QString info() const;

            void hideInfo();
            void showInfo();
        signals:
        };
    } // endV1

    namespace V2
    {
        class Picture : public QWidget
        {
                Q_OBJECT
            public:
                explicit Picture(QWidget *parent = nullptr);
                void paintEvent(QPaintEvent *event) override;
                void setPixmap(QPixmap*pix);
                void setPixmap(const QPixmap&pix);
            private:
                const QPixmap * pixmap;
                QMenu * mMenu;
                QAction * mAction;
            signals:
        };
    } // endV2
//}


#endif // PICTURE_H

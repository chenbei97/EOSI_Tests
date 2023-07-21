#ifndef PICTURE_H
#define PICTURE_H

#include <qlayout.h>
#include <qevent.h>
#include <qmenu.h>
#include <qfiledialog.h>
#include <qdatetime.h>
#include "label.h"
#include "Constant.h"

class Picture : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPixmap pixmap READ  pixmap WRITE setPixmap)
    Q_PROPERTY(QString info READ  info WRITE setInfo)

    Label * mPix;
    Label * mInfo;
    QMenu * mMenu;
    QAction * mAction;
public:
    explicit Picture(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;

    void setPixmap(const QPixmap& pix);
    QPixmap pixmap() const;

    void setInfo(const QString& info);
    QString info() const;
signals:

};

#endif // PICTURE_H

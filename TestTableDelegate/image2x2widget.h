#ifndef IMAGE2X2WIDGET_H
#define IMAGE2X2WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Image2x2Widget : public QWidget
{
    Q_OBJECT
    QList<QLabel*> mLabels;
    QList<QPixmap*> mPixs;
    QStringList mFileNames;
public:
    explicit Image2x2Widget(QWidget *parent = nullptr);

        void setText(int index, const QString&text);
        QString text(int index) const;
        QStringList texts() const;
//    void setPixmap(int index,const QPixmap&pix);
//    void setPixmap(int index,const QString& filename);
    void setPixmap(int index,QPixmap*pix);
    QPixmap* pixmap(int index) const;
//    const QPixmap * pixmap(int index) const ;
//    QString pixmapName(int index) const;
//    QStringList pixmapNames() const;
//    QList<const QPixmap*> pixmaps();
        QList<QPixmap*> pixmaps() const;

signals:

};

#endif // IMAGE2X2WIDGET_H

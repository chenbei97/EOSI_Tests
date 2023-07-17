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
    QStringList mFileNames;
public:
    explicit Image2x2Widget(QWidget *parent = nullptr);

    void setPixmap(int index,const QPixmap&pix);
    void setPixmap(int index,const QString& filename);
    const QPixmap * pixmap(int index) const ;
    QString pixmapName(int index) const;
    QStringList pixmapNames() const;
    QList<const QPixmap*> pixmaps() const;

signals:

};

#endif // IMAGE2X2WIDGET_H

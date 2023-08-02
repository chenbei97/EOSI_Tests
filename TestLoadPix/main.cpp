#include <QGuiApplication>
#include "loadpix.h"
int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    auto path = ":/1.jpg";
    auto size = QSize(400,300);
    loadPixmapDirect(path,size);
    loadPixmapByImageReader(path,size);
    loadPixmapByConcurrent(path,size);
    loadPixmapByConcurrentMapped(path,size);
    auto pix =  loadPixmapByConcurrentBlockingMapped(path,size);
    //qDebug()<<pix.size();

    QStringList paths = {":/1.jpg",":/2.jpg",":/3.jpg",":/4.jpg",":/5.jpg",":/6.jpg",":/7.jpg",":/8.jpg",":/9.jpg",":/10.jpg"};
    loadPixmapsDirect(paths,size);
    loadPixmapsByImageReader(paths,size);
    loadPixmapsByConcurrent(paths,size);
    loadPixmapsByConcurrentMapped(paths,size);
    auto pixs = loadPixmapsByConcurrentBlockingMapped(paths,size);
    //foreach(auto p, pixs) qDebug()<<p.size();

    return a.exec();
}

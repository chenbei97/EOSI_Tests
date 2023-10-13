#include "widget.h"
#include "qmediarecorder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<QImageReader::supportedImageFormats();
    Widget w;
    w.show();
    return a.exec();
}

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>

class CreateWin: public QObject
{
    Q_OBJECT
public:
    QWidget * create() {
        emit createStarted();
        auto w = new QWidget;
        emit createFinished();
        return w;
    }
signals:
    void createStarted();
    void createFinished();
};

class Widget : public QWidget
{
    Q_OBJECT
    QThread mThread;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QDebug>
#include <QLabel>
#include <QLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void test1();
    void test2();
};

class Slider:public QWidget
{
    Q_OBJECT
public:
    Slider(QWidget *parent = nullptr);
    void setRange(int min,int max);
    void setPrefix(const QString& prefix);
    void setSuffix(const QString& suffix);
private:
    QSlider * slider;
    QLabel * mprefix;
    QLabel * msuffix;
    QString suffixtext;
private slots:
    void onSliderChanged(int val);
};

#endif // MAINWINDOW_H

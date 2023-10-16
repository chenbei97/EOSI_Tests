#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   test2();
}

void MainWindow::test2()
{
    auto s = new Slider;
    s->setRange(0,150000);
    s->setPrefix(tr("曝光时间: "));
    s->setSuffix("ms");
    setCentralWidget(s);

    resize(600,300);
}

void MainWindow::test1()
{
    auto s = new QSlider(Qt::Horizontal);
    auto label = new QLabel;
    auto w = new QWidget;
    auto lay = new QHBoxLayout;
    lay->addWidget(s);
    lay->addWidget(label);
    w->setLayout(lay);
    setCentralWidget(w);

    resize(600,300);
    s->setTickPosition(QSlider::NoTicks);
    s->setTickInterval(50);
    s->setMinimum(0);
    s->setMaximum(15*1000);
    qDebug()<<"current val = "<<s->value();
    qDebug()<<"current tickInterval = "<<s->tickInterval();
    qDebug()<<"current singlestep = "<<s->singleStep();

    connect(s,&QSlider::sliderMoved,this,[=](auto val){
        qDebug()<<"slider move in "<<val; // 只有一直拖着才会发出
    });
    connect(s,&QSlider::valueChanged,this,[=](auto val){
        qDebug()<<"slider valuechanged in "<<val; // 一直会发出
        label->setText(QString("%1 ms").arg(val));
    });
}

MainWindow::~MainWindow()
{
}

Slider::Slider(QWidget *parent):QWidget(parent)
{
    slider = new QSlider(Qt::Horizontal);
    msuffix = new QLabel;
    mprefix = new QLabel;

    auto hlay = new QHBoxLayout;
    hlay->addWidget(mprefix);
    hlay->addWidget(slider);
    hlay->addWidget(msuffix);
    setLayout(hlay);

    connect(slider,&QSlider::sliderMoved,this,&Slider::onSliderChanged);
}

void Slider::onSliderChanged(int val)
{
    auto text = QString("%1 %2").arg(val).arg(suffixtext);
    qDebug()<<"text = "<<text;
    msuffix->setText(text);
}

void Slider::setRange(int min,int max)
{
    slider->setRange(min,max);
}

void Slider::setPrefix(const QString& prefix)
{
    mprefix->setText(prefix);
}

void Slider::setSuffix(const QString& suffix)
{
    suffixtext = suffix;
    msuffix->setText(suffix);
}

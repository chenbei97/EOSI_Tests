#include "mainwindow.h"
//#pragma execution_character_set("utf-8")
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    connectBtn = new QPushButton(tr("连接"));
    sendBtn = new QPushButton(tr("发送"));
    edit = new QTextEdit;
    tcpSocket = new QTcpSocket(this);
    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM1");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->open(QIODevice::ReadWrite);


    QVBoxLayout * v = new QVBoxLayout;
    QHBoxLayout * h = new QHBoxLayout;

    h->addWidget(connectBtn);
    h->addWidget(sendBtn);

    v->addLayout(h);
    v->addWidget(edit);

    connect(connectBtn,&QPushButton::clicked,this,&MainWindow::on_connectButton_clicked);
connect(sendBtn,&QPushButton::clicked,this,&MainWindow::on_sendButton_clicked);

    setLayout(v);
}

void MainWindow::on_connectButton_clicked()
{
       QString ssid = "beihui-5G";
       QString password = "beihui2021";
qDebug()<<1;
       QProcess process;
       QString cmd = "netsh wlan connect ssid=\"" + ssid + "\" name=\"" +
               ssid + "\" keyMaterial=\"" + password + "\"";
       process.start(cmd);
       process.waitForFinished();
        qDebug()<<2;
       tcpSocket->connectToHost("127.0.0.1", 45);
qDebug()<<3;
serialPort->open(QIODevice::ReadWrite);
       connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void MainWindow::on_sendButton_clicked()
{

        qDebug()<<"w1";
    QString data = "hello wifi!";
    serialPort->write(data.toUtf8());
    qDebug()<<"w";
}

void MainWindow::readData()
{
        qDebug()<<"4";
    QByteArray data = tcpSocket->readAll();
    edit->append(data);
        qDebug()<<"o";
}

MainWindow::~MainWindow()
{
    tcpSocket->close();
     serialPort->close();
}


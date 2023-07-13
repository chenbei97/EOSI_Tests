#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLayout>
#include <QSerialPort>
#include <QProcess>
#include <QPushButton>
#include <QTextEdit>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void readData();
private:
    QPushButton * connectBtn;
    QPushButton * sendBtn;
    QTextEdit * edit;
    QTcpSocket *tcpSocket;
    QSerialPort *serialPort;
};
#endif // MAINWINDOW_H

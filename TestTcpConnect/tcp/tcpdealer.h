#ifndef TCPDEALER_H
#define TCPDEALER_H

#include <QObject>
#include <QDebug>

class TcpDealer : public QObject
{
    Q_OBJECT
public:
    explicit TcpDealer(QObject *parent = nullptr);
    explicit TcpDealer(const QByteArray&d,QObject *parent = nullptr);

    void setData(const QByteArray&d);
    QByteArray data() const;

    QString data1() const;

private:
    QByteArray Data;
    void parse();
signals:
    void dataChanged();
};

#endif // TCPDEALER_H

#ifndef JSONREADWRITE_H
#define JSONREADWRITE_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QtDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QPoint>

class JsonReadWrite : public QObject
{
    Q_OBJECT
public:
    explicit JsonReadWrite(QObject *parent = nullptr);
    bool dirExisted();
    QByteArray readJson(const QString&filename);
    void parseJson(const QByteArray&json);
    void writeJson(const QString&filename,const QJsonObject&object);
    void writeJson(const QString&filename,const QJsonArray&array);
    void writeJson(const QString&filename,const QByteArray&json);

    QVariantMap map() const;
    QVariantList list() const;
private:
    void parseObject(const QJsonObject& object);
    void parseArray(const QJsonArray& array);
    QString appdataPath;
    QVariantMap parseData;
    QVariantList constantData;
signals:

};

#endif // JSONREADWRITE_H

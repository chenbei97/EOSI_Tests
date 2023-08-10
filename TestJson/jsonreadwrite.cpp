#include "jsonreadwrite.h"

JsonReadWrite::JsonReadWrite(QObject *parent) : QObject(parent)
{

}

void JsonReadWrite::parseObject(const QJsonObject& object)
{
    foreach(auto key,object.keys())
    {
        if (key == "points") {
            auto arr = object.value(key).toArray();
            QVector<QPair<QPoint,QString>> points(arr.count());
            foreach (auto ele, arr)
            {
                auto obj = ele.toObject();
                auto x = obj.value("x").toInt();
                auto y = obj.value("y").toInt();
                auto n = obj.value("pname").toString();
                auto o = obj.value("order").toInt();
                points[o] = qMakePair(QPoint(x,y),n); // 按照次序已经放好了
            }
            QVariant v;
            v.setValue(points);
            parseData[key] = v;
            continue;
        }

        auto var = object.value(key);
        if (var.isObject())
            parseObject(var.toObject());
        else if (var.isArray())
        {
            auto arr = var.toArray();
            if (arr.isEmpty()) parseData[key] = "[]";
            else parseArray(arr);
        }
        else {
            auto v = var.toVariant();
            parseData[key] = v;
        }
    }
}

void JsonReadWrite::parseArray(const QJsonArray& array)
{
    foreach(auto var, array)
    {
        if (var.isObject())
            parseObject(var.toObject());
        else if (var.isArray())
            parseArray(var.toArray());
        else constantData.append(var.toVariant());
    }
}

bool JsonReadWrite::dirExisted()
{
    // 自动创建项目名称的文件夹
    appdataPath = QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);
    QDir dir;
    if (!dir.exists(appdataPath))
        dir.mkpath(appdataPath);

    if (dir.exists(appdataPath))
        return true;
    return false;
}

QByteArray JsonReadWrite::readJson(const QString&filename)
{
    QByteArray json;
    if (!dirExisted()) return  json;

    auto path = appdataPath + "/" + filename;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        stream.setCodec("utf-8");
        //json = stream.readAll().toUtf8();
        json = file.readAll();
        file.close();
    }
    return json;
}

void JsonReadWrite::parseJson(const QByteArray &json)
{
    parseData.clear();
    constantData.clear();
    auto doc = QJsonDocument::fromJson(json);

    if (!doc.object().isEmpty()) {
        parseObject(doc.object());
        return;
    }

    if (!doc.array().isEmpty()) {
        parseArray(doc.array());
        return;
    }
}

void JsonReadWrite::writeJson(const QString&filename,const QJsonObject&object)
{
    auto doc = QJsonDocument(object);
    auto json = doc.toJson();
    writeJson(filename,json);
}

void JsonReadWrite::writeJson(const QString&filename,const QJsonArray&array)
{
    auto doc = QJsonDocument(array);
    auto json = doc.toJson();
    writeJson(filename,json);
}

void JsonReadWrite::writeJson(const QString&filename,const QByteArray&json)
{
    if (!dirExisted()) return;
    auto path = appdataPath + "/" + filename;
    QFile file(path);
    if (file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        stream.setCodec("utf-8");
       // stream <<QString::fromUtf8(json);
        stream << json;
        //file.write(json);
        file.close();
    }
}

QVariantMap JsonReadWrite::map() const
{
    return parseData;
}

QVariantList JsonReadWrite::list() const
{
    return constantData;
}

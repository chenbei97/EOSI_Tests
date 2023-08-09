#include "mainwindow.h"
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
        auto data = Data();
        auto obj = data.object();
        JsonReadWrite m;
        //auto bytes = m.readJson("eosi_config_object.json");
        m.writeJson("eosi_config.json",obj);

        //test_read();
//    QFile jsonFile("D:\\1.json");
//            if (!jsonFile.open(QIODevice::ReadWrite | QIODevice::Text))
//                qDebug() << "1111";

//            QTextStream sss(&jsonFile);
//            sss.setCodec("utf-8");
//            QJsonDocument json_doc;//创建json文件
//            QString str = "你好";
//            QJsonObject json_obj;//创建json对象
//            json_obj.insert("name2",str);
//            json_obj.insert("age2",14);
//            json_obj.insert("age3",QString("哈哈哈哈"));
//            json_doc.setObject(json_obj);//将json对象转为json文件
//            jsonFile.write(json_doc.toJson(QJsonDocument::Indented));//写入文件
//            //sss<<json_doc.toJson(QJsonDocument::Indented);
//            jsonFile.close();
}

MainWindow::~MainWindow()
{
}

void MainWindow::test_read()
{
    JsonReadWrite m;
    auto str1 = m.readJson("eosi_config_object.json");
    auto str2 = m.readJson("eosi_config_array.json");
    m.parseJson(str1);
    //m.parseJson(str2);

    auto mao = m.map();
    auto iter = mao.begin();
    qDebug()<<"count = "<<mao.count();
    for(; iter != mao.end(); ++iter){
        if (iter.key() == "points") {
            auto points = iter.value().value<QVector<QPair<QPoint,QString> >>();
            qDebug()<<"["<<iter.key()<<","<<points<<"]";
        }
        else qDebug()<<"["<<iter.key()<<","<<iter.value()<<"]";
    }

    foreach(auto l, m.list())
        qDebug()<<l;
}

void MainWindow::test()
{
    // obj
    QJsonObject obj1;
    obj1.insert("a",QJsonValue(3.14));
    obj1.insert("b",QJsonValue(true));
    obj1.insert("c",QJsonValue(5));
    obj1.insert("c",QJsonValue(8));//会覆盖
    obj1.insert("d",QJsonValue());

//    qDebug()<<obj1;
//    qDebug()<<obj1.toVariantMap();
//    qDebug()<<obj1.toVariantHash();

    QVariantMap m2;
    m2["a"]='a';
    m2["c"] = 3;
    m2["b"] = QJsonValue();
    QJsonObject obj2 = QJsonObject::fromVariantMap(m2);
//    qDebug()<<obj2;


    QJsonObject obj3;
    obj3.insert("obj1",QJsonValue(obj1));
    obj3.insert("obj2",QJsonValue(obj2));
//    qDebug()<<obj3;

    // array
    QJsonArray arr1;
    arr1.append(1);
    arr1.append(QJsonValue());
    arr1.append(obj1); // 数组可以添加obj
//    qDebug()<<arr1;

    QJsonArray arr2;
    arr2.append(obj3);
    arr2.append(arr1);// 数组也可以添加数组
//    qDebug()<<arr2;

    QStringList list = {"123","456","789"};
    QJsonArray arr3 = QJsonArray::fromStringList(list);

    QVariantMap m;
    m["name"] = "chen";
    m["age"] = 23;
    QVariantList k;
    k.append(m); // 数组添加obj
    k.append(QVariantList()); // 这个空列表不会体现
    k.append(QJsonValue());
    k.append(QJsonArray());
    QVariantList v;
    v.append(1);
    v.append("abc");
    v.append(k); // 数组添加数组
    auto arr4 = QJsonArray::fromVariantList(v);

//    qDebug()<<arr1.toVariantList(); //普通值对应Variant,Object对象对应VariantMap
//    qDebug()<<arr2.toVariantList();
//    qDebug()<<arr3<<arr3.toVariantList(); // 仅仅只有值,没有键值对类型
//    qDebug()<<arr4;

    // qjsondocument
    QJsonDocument doc1(obj1);

    QVariant vv;
    vv.setValue(v);
    QJsonDocument doc2 = QJsonDocument::fromVariant(v);

    QByteArray json = "{\"obj1\":[{" // 一个带有3个键值对的大键值对
                      "\"a\":123,"
                      "\"b\":true,"
                      "\"c\":null},"
                      "null"
                      "],"
                      "\"obj2\":[]," // 值是个空列表
                      "\"obj3\":["
                            "null,123,false,"// 列表里3个值
                            "{\"abc\":4}" // 键值对必须用{}括起来
                      "]}";

    auto doc3 = QJsonDocument::fromJson(json);

    //qDebug()<<doc1.toJson(QJsonDocument::Compact);
    //qDebug()<<doc2.toJson(QJsonDocument::Compact);
    //qDebug()<<doc3.toJson(QJsonDocument::Compact);

    QDir dir; // 没有目录就创建默认目录
    QString dbdir = "C:/Users/22987/AppData/Local/EOSI";
    if (!dir.exists(dbdir))
    {
        dbdir = QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0);
        if (!dir.exists(dbdir)) dir.mkpath(dbdir);
    }
    qDebug()<<dbdir; // C:/Users/22987/AppData/Local/TestJson,自动创建项目名称的文件夹

    QFile file(dbdir+"/info.json");
    bool ok=file.open(QIODevice::WriteOnly);
    if(ok)
    {
        file.write(doc3.toJson());
        file.close();
    }

    file.open(QIODevice::ReadOnly);
    auto t = file.readAll();
    qDebug()<<QJsonDocument::fromJson(t);
    auto jj = QJsonDocument::fromJson(t);
    qDebug()<<jj.object(); // 二选一的格式
    qDebug()<<jj.array();


    auto o = jj.object();
    // 解析json，其实最终就是解析array或者object
    auto iter = o.constBegin();
    for(; iter!= o.constEnd(); ++iter) {
        if (iter.key() == "obj1") {
            auto arr1 = iter->toArray(); // 数组下方有1个对象和1个普通值
            auto arr1_o1 = arr1.begin()->toObject();
            auto arr1_o2 = arr1.begin()+1;
            qDebug()<<*arr1_o2; // null
            qDebug()<<arr1_o1.value("a").toInt();
            qDebug()<<arr1_o1.value("b").toBool();
            qDebug()<<arr1_o1.value("c");

        } else if (iter.key() == "obj2") {
                auto list1 = iter->toArray();
                qDebug()<<"list1.isEmpty()  =   "<<list1.isEmpty();
        } else if (iter.key() == "obj3") {
                auto list2 = iter->toArray();
                qDebug()<<list2.size();
                qDebug()<<list2.last().toObject().value("abc");
        }
    }
}

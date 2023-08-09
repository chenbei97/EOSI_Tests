#include "data.h"

Data::Data()
{
    scan_mode = "士大夫十分"; // New,Current,Previous
    scan_type = "s为了我率d";

    wellsize = "8x12(96)";
    channel = "red";
    view = "4";
    objective = "10xPH";
    points = {QPoint(2,3),QPoint(12,23),QPoint(32,43),QPoint(82,45)};
    names <<"A"<<"B"<<"C"<<"D";

    experiment_date = QDate::currentDate();
    experiment_name ="cell";
    experiment_person = "chenbei";
    experiment_celltype = "experiment_celltype";
    experiment_description = "experiment_description";
    experiment_type = "proliferation";

    schedule_start_datetime = QDateTime::currentDateTime();
    schedule_end_datetime = QDateTime::currentDateTime().addSecs(6874654);
    schedule_total_time = 98215;
     schedule_duration_time = 453;
    schedule_total_count = 98215/453;


     once_total_time = 787832;
     once_duration_time = 3788;
    once_total_count = 787832/3788;
    is_once = false;
}

QJsonObject Data::object() const
{
    {
        QByteArray d1("但是看见粉红色短裤就");

        QByteArray d2 ("撒旦立刻就粉红色快递费");

        QString d3 = "撒旦立刻就粉红色快递费";
        QByteArray d6 = d3.toUtf8();

        const char* d4 = d3.toStdString().c_str();
        QJsonObject object;
        object.insert("scan_mode",scan_mode);
        object.insert("scan_type",QString::fromUtf8(QByteArray("几乎不能靠近和我空间和空间")));
        //object.insert("wellsize",QStringLiteral("萨尔代付接口函数即可"));
        object.insert("channel",QString::fromUtf8("几乎不能靠近和我空间和空间"));
        object.insert("view",d3);
         //object.insert("view2",d4); // d4不可以
        object.insert("view1",QString("萨的空间花费的时间开发"));
//        object.insert("view2",QString::fromLocal8Bit("手动阀手动阀"));
//        object.insert("view3",QString::fromLatin1("手动阀手动阀"));
//        object.insert("view4",d4);
        object.insert("objective","十大富豪刷卡积分");

        QJsonArray pArray;
        for(int i = 0; i < points.count(); ++i) {
            QJsonObject obj;
            auto point = points[i];
            obj["x"] = point.x();
            obj["y"] = point.y();
            obj["pname"] = names[i];
            obj["order"] = i;
            pArray.append(obj);
        }
        object.insert("points",pArray);

        QJsonObject pObj;
        pObj["date"] = experiment_date.toString("yyyy/MM/dd");
        pObj["name"] = experiment_name;
        pObj["person"] = experiment_person;
        pObj["type"] = experiment_type;
        pObj["celltype"] = experiment_celltype;
        pObj["description"] = experiment_description;
        object.insert("experiment",pObj);


        QJsonObject tobj;
        if (is_once) {
            qDebug()<<"isOnce";
            tobj["schedule"] = false;
            tobj["total"] = once_total_time;
            tobj["duration"] = once_duration_time;
            tobj["count"] = once_total_count;
        }
        else {
            tobj["schedule"] = true;
            tobj["total"] = schedule_total_time;
            tobj["duration"] = schedule_duration_time;
            tobj["count"] = schedule_total_count;
            tobj["start"] = schedule_start_datetime.toString("yyyy/MM/dd hh:mm");
            tobj["end"] = schedule_end_datetime.toString("yyyy/MM/dd hh:mm");
        }
        object.insert("time",tobj);

        return object;
    }
}

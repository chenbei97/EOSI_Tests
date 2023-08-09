#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QPoint>

class Data
{
public:
    Data();
    QString scan_mode = "而侮辱即可"; // New,Current,Previous
    QString scan_type = "standard";

    QString wellsize = "8x12(96)";
    QString channel = "red";
    QString view = "4";
    QString objective = "10xPH";
    QVector<QPoint> points = {QPoint(2,3),QPoint(12,23),QPoint(32,43),QPoint(82,45)};
    QStringList names = {"A","B","C","D"};

    QDate experiment_date = QDate::currentDate();
    QString experiment_name ="cell";
    QString experiment_person = "chenbei";
    QString experiment_celltype = "你好";
    QString experiment_description = "十大科技发挥空间";
    QString experiment_type = "上的人反弹高位";

    QDateTime schedule_start_datetime = QDateTime::currentDateTime();
    QDateTime schedule_end_datetime = QDateTime::currentDateTime().addSecs(6874654);
    long long schedule_total_time = 98215;
    long long  schedule_duration_time = 453;
    int schedule_total_count = 98215/453;


    long long  once_total_time = 787832;
    long long  once_duration_time = 3788;
    int once_total_count = 787832/3788;
    bool is_once = true;

    QJsonObject object() const;
};

#endif // DATA_H

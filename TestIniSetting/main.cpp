#include <QCoreApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSettings * settings = new QSettings (":/config.ini", QSettings::IniFormat);
    qDebug()<< settings->value("username")<<settings->value("password")
            <<settings->value("dbdir").toString();
    //settings->deleteLater();
    return a.exec();
}

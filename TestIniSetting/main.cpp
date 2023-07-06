#include <QCoreApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSettings * settings = new QSettings (":/config.ini", QSettings::IniFormat);
    qDebug()<< settings->value("system/user")<<settings->value("system/password")
            <<settings->value("system/dbdir").toString();
    //settings->deleteLater();
    return a.exec();
}

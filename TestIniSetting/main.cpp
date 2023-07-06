#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<QDir::currentPath(); // Desktop/Debug/build-TestIniSetting-Debug
    //QSettings * settings = new QSettings (":/config.ini", QSettings::IniFormat); // 写入资源文件路径不起作用,只能写入磁盘
    //QSettings * settings = new QSettings ("C:/Users/Lenovo/Desktop/EOSI_Tests/TestIniSetting/config.ini", QSettings::IniFormat);
    QSettings * settings = new QSettings ("../../EOSI_Tests/TestIniSetting/config.ini", QSettings::IniFormat);

    settings->setIniCodec("utf-8");

    qDebug()<<settings->allKeys();

    qDebug()<< settings->value("system/user")<<settings->value("system/password")
            <<settings->value("system/dbdir").toString();

    qDebug()<<settings->isAtomicSyncRequired();

    settings->setAtomicSyncRequired(false);

    settings->setValue("system/user","chenb");
    settings->setValue("system/password","199791");
    settings->setValue("system/dbdir","C:\\Users\\Lenovo\\Desktop\\myLeetCode");

    settings->sync();

    settings->deleteLater();
    return a.exec();
}

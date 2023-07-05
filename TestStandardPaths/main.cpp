#include <QCoreApplication>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<QDir::homePath();
    typedef   QStandardPaths::StandardLocation SL;
    for (int i = SL::DesktopLocation;i<SL::AppConfigLocation;++i)
    {
       // qDebug()<<QStandardPaths::displayName(SL(i));
        //qDebug()<<QFileInfo(QStandardPaths::displayName(SL(i))).absolutePath();
        qDebug()<<"("<<i<<")  "<<QStandardPaths::standardLocations(SL(i));
    }

    /*
( 0 )   ("C:/Users/22987/Desktop")
( 1 )   ("C:/Users/22987/Documents")
( 2 )   ("C:/Windows/Fonts")
( 3 )   ("C:/Users/22987/AppData/Roaming/Microsoft/Windows/Start Menu/Programs")
( 4 )   ("C:/Users/22987/Music")
( 5 )   ("C:/Users/22987/Videos")
( 6 )   ("C:/Users/22987/Pictures")
( 7 )   ("C:/Users/22987/AppData/Local/Temp")
( 8 )   ("C:/Users/22987")
( 9 )   ("C:/Users/22987/AppData/Local/TestStandardPaths", （可以用） QStandardPaths::DataLocation
        "C:/ProgramData/TestStandardPaths",
        "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug",
        "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug/data",
        "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug/data/TestStandardPaths")
( 10 )   ("C:/Users/22987/AppData/Local/TestStandardPaths/cache")
( 11 )   ("C:/Users/22987/AppData/Local",
        "C:/ProgramData",
        "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug",
        "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug/data")
( 12 )   ("C:/Users/22987")
( 13 )   ("C:/Users/22987/AppData/Local/TestStandardPaths", （可以用）QStandardPaths::ConfigLocation
        "C:/ProgramData/TestStandardPaths",
         "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug",
        "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug/data",
        "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug/data/TestStandardPaths")
( 14 )   ("C:/Users/22987/Downloads")
( 15 )   ("C:/Users/22987/AppData/Local/cache")
( 16 )   ("C:/Users/22987/AppData/Local",
            "C:/ProgramData",
            "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug",
            "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug/data")
( 17 )   ("C:/Users/22987/AppData/Roaming/TestStandardPaths",  （可以用） QStandardPaths::AppDataLocation
            "C:/ProgramData/TestStandardPaths",
            "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug",
            "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug/data",
            "C:/Users/22987/Desktop/EOSI_Tests/build-TestStandardPaths-Desktop_Qt_5_14_2_MSVC2017_64bit-Debug/debug/data/TestStandardPaths")
*/
    return a.exec();
}

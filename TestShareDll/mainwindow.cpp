#include "mainwindow.h"
#include "qdir.h"
#include "qstandardpaths.h"
#include "qdebug.h"
#include "qapplication.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   qDebug()<<QDir::currentPath();
//    auto dir = QDir::current();
//    dir.cdUp();
//    dir.cd(QApplication::applicationName());
//    dir.cd("dll");
//auto path = "C:\\Users\\22987\\Desktop\\EOSI_Tests\\TestShareDll\\dll\\buttond.dll";
// qDebug()<<QLibrary::isLibrary(path);
//    QPushButton * btn = new QPushButton("加载",this);
//    setCentralWidget(btn);


//   Button * button = new Button("厉害",this);
//   setCentralWidget(button);
//       connect(button,&QPushButton::clicked,this,[=]{
//           QLibrary Button("button");

//           qDebug()<<Button.errorString();
//           qDebug()<<Button.fileName();
//           qDebug()<<Button.isLoaded();
//       });
//       button->click();
}

MainWindow::~MainWindow()
{
}


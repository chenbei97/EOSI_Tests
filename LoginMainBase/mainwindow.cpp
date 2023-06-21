#include "mainwindow.h"
#include <QSharedPointer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    main = new LoginMain;
    main->addButton(QSharedPointer<QPushButton>::create("abc"));
//    QSharedPointer<QPushButton> pb1(new QPushButton("123")) ;
//    main->addButton(pb1);
    main->addButton(new QPushButton("abc"));
    main->addButton(QSharedPointer<QPushButton> (new QPushButton("13")));
main->addButton(QSharedPointer<QPushButton> (new QPushButton("3")));

main->addButton(new QPushButton("sfsg"));

    LoginButton * b1 = new LoginButton;
    b1->setText("23sdf");
    connect(b1,&QPushButton::clicked,this,[=]{b1->setButtonType(qrand()%3);qDebug()<<b1->buttonType();});
    main->addButton(b1);
    setCentralWidget(main);
    resize(400,300);
}

MainWindow::~MainWindow()
{
}


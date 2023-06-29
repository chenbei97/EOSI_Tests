#include "mainwindow.h"
#include <QDebug>
#pragma execution_character_set("utf-8")

struct Info {
    QString name;
    QColor color;
    QDate birth;
    QStringList members;
    QVariant data;
    QImage * image;
    int age;
    double height;
    bool sex;
};


Q_DECLARE_METATYPE(Info)

QImage * Img = new QImage(":/table_img_eg.jpg");
QVector<float> data1 = {1.3f,2.5f,7.6f};
QVector<QString> data2 = {"2.3f","4.5f","8.6f"};
QVector<double> data3 = {7.784,9.212,89.889};

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QVariant Data1;
    Data1.setValue(data1);
    QVariant Data2;
    Data2.setValue(data2);
    QVariant Data3;
    Data3.setValue(data3);

    const Info info1 = {"chenbei","blue",QDate(1997,9,1),
                       {"dad","mom","dog"},Data1,Img,25,184.5,true};
    const Info info2 = {"chenqifu","red",QDate(1974,4,13),
                       {"儿子","妻子","dog"},Data2,Img,49,171.8,true};
    const Info info3 = {"zhangliping","green",QDate(1958,11,12),
                       {"儿子","丈夫","dog"},Data3,Img,65,158.1,false};

    QVariant d1; d1.setValue(info1);
    QVariant d2; d2.setValue(info2);
    QVariant d3; d3.setValue(info3);

    box = new QComboBox;
    QVBoxLayout * lay = new QVBoxLayout;
    box->addItem("son",d1);
    box->addItem("dad",d2);
    box->addItem("mom",d3);

    edit = new QTextEdit;

    connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(showInfo(int)));

    box->setCurrentIndex(1);

    lay->addWidget(box);
    lay->addWidget(edit);
    setLayout(lay);
    resize(1000,800);
}

void MainWindow::showInfo(int index)
{
    qDebug()<<1;
    QVariant data = box->itemData(index);

    Info info = data.value<Info>();
 qDebug()<<2;
    QString name = info.name;
    QString color = info.color.name();
    QDate birth = info.birth;
    QStringList members = info.members;
    auto m1 = members[0];auto m2 = members[1];auto m3 = members[2];
    QVariant d = info.data;
    QString dstr;
     qDebug()<<3;
    if (index == 0) {
        auto dat = d.value<QVector<float>>();
        dstr =QString("{%1, %2, %3}").arg(dat[0]).arg(dat[1]).arg(dat[2]);
    } else if (index == 1){
        auto dat = d.value<QVector<QString>>();
        dstr =QString("{%1, %2, %3}").arg(dat[0]).arg(dat[1]).arg(dat[2]);
    }else if (index == 2) {
        auto dat = d.value<QVector<double>>();
        dstr =QString("{%1, %2, %3}").arg(dat[0]).arg(dat[1]).arg(dat[2]);
    }
    QImage * image = info.image;
    int age = info.age;
    double height = info.height;
    QString sex = info.sex==true?"男":"女";
 qDebug()<<4;
    edit->setText(QString("name: %1\n"
                          "age = %2\n"
                          "height = %3\n"
                          "sex = %4\n"
                          "birth = %5\n"
                          "color = %6\n"
                          "list = {%7, %8, %9}\n"
                          "variant = %10\n").arg(name).arg(age).arg(height).arg(sex)
                  .arg(birth.toString("yyyy-MM-dd")).arg(color)
                  .arg(m1).arg(m2).arg(m3).arg(dstr));
     qDebug()<<5;
        // 插入图片方法1
        //edit->append(QString("<img src=':/table_img_eg.jpg'\n>"));
        //edit->append(QString("<img src=%1\n>").arg(":/table_img_eg.jpg"));

        // 插入图片方法2
             QTextImageFormat imageFormat;   //保存图片格式对象
             imageFormat.setName(":/table_img_eg.jpg");
             auto cursor = edit->textCursor();
             cursor.movePosition(QTextCursor::End);
             cursor.insertImage(imageFormat);   //通过编辑指针表把图片格式的文件插入到资源中
            edit->setTextCursor(cursor);

//     auto document = edit->document();
//     auto url = QUrl(":/table_img_eg.jpg");
//     document->addResource(QTextDocument::ImageResource,url, QVariant(url));
//     edit->setDocument(document);
}

MainWindow::~MainWindow()
{
}


#include "mainwindow.h"
#include <QStatusBar>

//#define TableWidgetSubClassSetDelegate 0
//#define TableWidgetSetDelegate 0
////#define TableViewSubClassSetDelegate 0
#define TableViewSetDelegate 0

Q_DECLARE_METATYPE(QList<QPixmap*>)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    QStandardItemModel * model1 = new QStandardItemModel;
//    model1->setRowCount(12);model1->setColumnCount(8);



//    auto delegate1 = new QWComboBoxDelegate;
//    delegate1->setItems(QStringList()<<"A"<<"B",true);

//    auto delegate2 = new Table2x2Delegate;

    auto delegate3 = new Image2x2Delegate;

//    auto delegate4 = new PushButtonDelegate;

//    TableWidgetBase * table1 = new TableWidgetBase(12,8);

//    QTableWidget * table2 = new QTableWidget;
//    table2->setRowCount(12);table2->setColumnCount(8);

    QTableView * view1 = new QTableView;

view1->setItemDelegate(delegate3);
view1->setEditTriggers(QAbstractItemView::AllEditTriggers);
    QStandardItemModel * model2 = new QStandardItemModel(view1);
    model2->setRowCount(2);model2->setColumnCount(2);
    QMap<int, QVariant> roles;
    //roles[Qt::DecorationRole] = QStringList()<<":/1.jpg"<<":/2.jpg"<<":/3.jpg"<<":/4.jpg";

    auto texts = QStringList()<<":/1.jpg"<<":/2.jpg"<<":/3.jpg"<<":/4.jpg";
    QList<QPixmap*> iconlist;
    iconlist<<new QPixmap(":/1.jpg")<<new QPixmap(":/2.jpg")
           <<new QPixmap(":/3.jpg")<<new QPixmap(":/4.jpg");
    //qRegisterMetaType<QList<QPixmap*>>("pixmaplist");
    QVariant v ;
    v.setValue(iconlist);
//    roles[Qt::DisplayRole] = texts;
//    roles[Qt::DecorationRole] = v;

        roles[Qt::DisplayRole] = v;


    model2->setItemData(model2->index(0,0),roles);
    model2->setItemData(model2->index(0,1),roles);

//    model2->setData(model2->index(0,0),texts,Qt::DisplayRole);
//    model2->setData(model2->index(0,0),v,Qt::DecorationRole);
//    model2->setData(model2->index(0,1),texts,Qt::DisplayRole);
//    model2->setData(model2->index(0,1),v,Qt::DecorationRole);

    view1->setModel(nullptr);
    view1->setModel(model2);
    view1->repaint();
    view1->viewport()->update();
//    view1->setIndexWidget(model2->index(0,0),new Image2x2Widget);
//    view1->setIndexWidget(model2->index(0,1),new Image2x2Widget);

//    TableView * view2 = new TableView;
//    view2->setModel(model2);

#ifdef TableWidgetSubClassSetDelegate // QTableWidget的子类设置代理不成功
    table1->setItemDelegate(delegate2);
    setCentralWidget(table1);
#elif defined(TableWidgetSetDelegate) // QTableWidget可以设置代理
//    table2->setItemDelegate(delegate4);// pushbutton
//    table2->setItemDelegate(delegate1); // combobox代理本身的初始化
//    table2->setItemDelegate(delegate3); // label的读写函数代理和QTable WidgetItem的数据不对应
    table2->setItemDelegate(delegate2); // tablewidget2x2的对应
    table2->setCellWidget(0,0,new TableWidgetBase(2,2));
    qDebug()<<(table2->item(0,0) == nullptr);
    setCentralWidget(table2);
#elif defined(TableViewSetDelegate) // QTableView可以设置代理


    view1->setColumnWidth(0,400);
    view1->setRowHeight(0,400);
    view1->setColumnWidth(1,400);
    view1->setRowHeight(1,400);

    setCentralWidget(view1);

//    auto label = new QLabel("123");
//label->setPixmap(QPixmap(":/1.jpg"));
//label->setText("345hu45u");
//    statusBar()->addWidget(label);

#else
    view2->setItemDelegate(delegate3); // QTableView子类可以设置代理
    setCentralWidget(view2);
    //view2->closePersistentEditor(model1->index(0,0));
    //view2->openPersistentEditor(model1->index(0,1)); //会让编辑框完全弹出来
#endif


//----------------------------------------------------------------------






    // 1. 用QTableWidget设置代理可以成功,QTableWidget的子类设置代理失败，QTableView和子类都可以设置代理成功
    // 3. QTableWidget2x2应该封装成新类,提供设置每个单元格数据的方法,因为是从这个代理组件拿数据的
    // 所以定义一个代理组件一定要    `设计好 赋值和取值的函数,这样在代理类重载时来setModelData和setEditorData
    // 4. 如果只是为了展示图片,可以考虑不使用QTableWidget作为代理,使用4个label组成的widget也可以(这是ok的)
    // 5. 如果不是combobox,label,lineedit,checkbox,基于QWidget的代理组件,双击会弹出这个代理组件,而不是嵌入其中(要解决不弹出的问题)

    resize(1800,1000);
}

MainWindow::~MainWindow()
{
}


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    auto delegate1 = new QWComboBoxDelegate;
    delegate1->setItems(QStringList()<<"A"<<"B",true);

    TableWidgetBase * table1 = new TableWidgetBase(12,8);
    table1->setItemDelegate(delegate1);

    QTableWidget * table2 = new QTableWidget;
    table2->setRowCount(12);table2->setColumnCount(8);
    table2->setItemDelegate(delegate1);

    QTableView * view1 = new QTableView;
    TableView * view2 = new TableView;
    QStandardItemModel * model1 = new QStandardItemModel;
    model1->setRowCount(12);model1->setColumnCount(8);
    view1->setModel(model1);
    view1->setItemDelegate(delegate1);
    view2->setModel(model1);
    view2->setItemDelegate(delegate1);


//----------------------------------------------------------------------
    auto delegate2 = new Table2x2Delegate;
    table2->setItemDelegate(delegate2);
    view2->setItemDelegate(delegate2);
    view1->setItemDelegate(delegate2);

    auto delegate3 = new Image2x2Delegate;
    QStandardItemModel * model2 = new QStandardItemModel;
    QMap<int, QVariant> roles;
    roles[Qt::DecorationRole] = QStringList()<<":/1.jpg"<<":/2.jpg"<<":/3.jpg"<<":/4.jpg";
    model2->setRowCount(2);model2->setColumnCount(2);
    model2->setItemData(model2->index(0,0),roles);
    model2->setItemData(model2->index(0,1),roles);
    view2->setModel(model2);
    view2->setItemDelegate(delegate3);
    view2->closePersistentEditor(model2->index(0,0));
    //view2->openPersistentEditor(model2->index(0,1)); //会让编辑框完全弹出来

    auto delegate4 = new PushButtonDelegate;
    view1->setItemDelegate(delegate4);
    table2->setItemDelegate(delegate4);
    table2->setItemDelegate(delegate1);

    setCentralWidget(table2);
    //setCentralWidget(view1);

    // 1. 用QTableWidget设置代理可以成功,QTableWidget的子类设置代理失败
    // 2. QTableView和子类都可以设置代理成功
    // 3. QTableWidget2x2应该封装成新类,提供设置每个单元格数据的方法,因为是从这个代理组件拿数据的
    // 所以定义一个代理组件一定要设计好 赋值和取值的函数,这样在代理类重载时来setModelData和setEditorData
    // 4. 如果只是为了展示图片,可以考虑不使用QTableWidget作为代理,使用4个label组成的widget也可以(这是ok的)
    // 5. 如果不是combobox,label,lineedit,checkbox,基于QWidget的代理组件,双击会弹出这个代理组件,而不是嵌入其中(要解决不弹出的问题)

    resize(1800,1000);
}

MainWindow::~MainWindow()
{
}


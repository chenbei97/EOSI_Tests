#include "sqldbquerytree.h"

void SqlDBQueryTree::refreshTree()
{
    mTreeView->clear();

    auto dbname = QSqlDatabase::connectionNames();
    Q_ASSERT(dbname.count() == 1);// 软件只会出现1个
    auto db = QSqlDatabase::database(dbname[0],true);
    //auto db = QSqlDatabase::database(QSqlDatabase::connectionNames()[0]);
    if (!db.isOpen()) return;

    auto drivername = "driver@"+db.driverName();
    auto user = "user@"+db.userName();
    auto ip = "ip@" + db.hostName();
    auto port = "port@" + QString::number(db.port());
    auto tables = db.tables();
    auto table = "tables@count: "+QString::number(tables.count());

    QTreeWidgetItem * driveritem = new QTreeWidgetItem(mTreeView,QStringList()<<drivername);
    QTreeWidgetItem * useritem = new QTreeWidgetItem(mTreeView,QStringList()<<user);
    QTreeWidgetItem * ipitem = new QTreeWidgetItem(mTreeView,QStringList()<<ip);
    QTreeWidgetItem * portitem = new QTreeWidgetItem(mTreeView,QStringList()<<port);
    QTreeWidgetItem * tableitem = new QTreeWidgetItem(mTreeView,QStringList()<<table);
    for (int i = 0 ; i < tables.count(); ++i) {
        auto text = "table"+QString::number(i+1)+"@" + tables[i];
        tableitem->addChild(new QTreeWidgetItem(QStringList()<<text));
    }
    mTreeView->addTopLevelItem(driveritem);
    mTreeView->addTopLevelItem(useritem);
    mTreeView->addTopLevelItem(ipitem);
    mTreeView->addTopLevelItem(portitem);
    mTreeView->addTopLevelItem(tableitem);
}

void SqlDBQueryTree::showSchema()
{
    QTreeWidgetItem *item = mTreeView->currentItem();
    if (!item || !item->parent()) // 多做一些判断总是没错的,表节点有父类,均不能为空
        return;
    setBold(item->parent());
    setBold(item);
    auto text = item->text(0); // table1@a
    auto idx = text.indexOf("@");
    text.remove(0,idx+1);
    emit schemaShowed(text);
}

SqlDBQueryTree::SqlDBQueryTree(QWidget *parent) : QWidget(parent)
{
    mTreeView = new QTreeWidget;
    mTreeView->setHeaderLabel("DataBase");
    mTreeView->setEditTriggers(QTreeView::NoEditTriggers);
    mTreeView->setSelectionMode(QTreeView::SingleSelection);
    mTreeView->setSelectionBehavior(QTreeView::SelectRows);

    mRefresh = new QAction(tr("刷新"),mTreeView);
    mSchema = new QAction(tr("表架构"),mTreeView);

    mTreeView->addAction(mRefresh);
    mTreeView->addAction(mSchema);
    mTreeView->setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(mRefresh,&QAction::triggered,this,&SqlDBQueryTree::refreshTree);
    connect(mSchema,&QAction::triggered,this,&SqlDBQueryTree::showSchema);
    connect(mTreeView,&QTreeWidget::itemActivated,this,&SqlDBQueryTree::onItemActivated);
    connect(mTreeView,&QTreeWidget::currentItemChanged,this,&SqlDBQueryTree::onCurrentItemChanged);

    QVBoxLayout * lay = new QVBoxLayout(this);
    lay->addWidget(mTreeView);

    refreshTree();

}

void SqlDBQueryTree::setBold(QTreeWidgetItem *item, bool bold)
{
    for (int i = 0; i < mTreeView->topLevelItemCount(); ++i) {
        setTreeItemBold(mTreeView->topLevelItem(i),false);
    }
    if (item->childCount() > 0) {
        for(int j = 0; j < item->childCount(); ++j)
            setTreeItemBold(item->child(j),false);
    }
    if (item->parent()) setTreeItemBold(item->parent(),bold);
    setTreeItemBold(item,bold);
}

void SqlDBQueryTree::onItemActivated(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if (item->parent()) setBold(item->parent());
    setBold(item,true); // 这2行不要调换顺序
    if (!item->parent()) return; // 没有父类的不要发送
    auto text = item->text(0); // table1@a
    auto idx = text.indexOf("@");
    text.remove(0,idx+1);
    emit tableShowed(text);
}

void SqlDBQueryTree::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    if (current &&current->parent()) // 这里current可能是nullptr,refresh的时候
        mSchema->setEnabled(true);
    else mSchema->setEnabled(false);
}


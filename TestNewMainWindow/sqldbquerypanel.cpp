#include "sqldbquerypanel.h"

SqlDBQueryPanel::SqlDBQueryPanel(QWidget *parent) : QWidget(parent)
{
        auto box1 = initleft();
        auto box2 = initright();
        mStatusBar = new QStatusBar;

        auto lay = new QHBoxLayout;
        lay->addWidget(box1);
        lay->addWidget(box2);

        auto mlay = new QVBoxLayout(this);
        mlay->addLayout(lay);
        mlay->addWidget(mStatusBar);

        connect(mStartDateEdit,&QDateEdit::dateChanged,this,&SqlDBQueryPanel::onDateChanged);
        connect(mEndDateEdit,&QDateEdit::dateChanged,this,&SqlDBQueryPanel::onDateChanged);
        connect(mFilterBtn,&QPushButton::clicked,this,&SqlDBQueryPanel::onFilterBtn);
        connect(mExecBtn,&QPushButton::clicked,this,&SqlDBQueryPanel::onQueryBtn);
        connect(mClearBtn,&QPushButton::clicked,this,[=]{mPanel->clear();});
        connect(mCommand,SIGNAL(currentIndexChanged(QString)),this,SLOT(onCommandChanged(QString)));
}

QGroupBox* SqlDBQueryPanel::initleft()
{
    mStartDateEdit = new QDateEdit;
    mEndDateEdit = new QDateEdit;
    mStartDateEdit->setMaximumDate(QDate::currentDate());
    mEndDateEdit->setMaximumDate(QDate::currentDate());
    mStartDateEdit->setDate(QDate(2021,7,1));
    mEndDateEdit->setDate(QDate::currentDate());

    mTableFields = new QComboBox;
    mSymbols = new QComboBox;
    mSymbols->addItems(QStringList()<<"="<<"<="<<">="<<"<"<<">"<<"!=");
    mKeyWordEdit = new QLineEdit;
    mFilterBtn = new QPushButton(tr("过滤"));

    QFormLayout * top = new QFormLayout;
    top->addRow(tr("开始时间:"),mStartDateEdit);
    top->addRow(tr("结束时间:"),mEndDateEdit);


    QHBoxLayout * btm = new QHBoxLayout;
    btm->addWidget(mTableFields);
    btm->addWidget(mSymbols);
    btm->addWidget(mKeyWordEdit);
    btm->addWidget(mFilterBtn);

    auto lay = new QVBoxLayout;
    lay->addLayout(top);
    lay->addLayout(btm);

    QGroupBox * box = new QGroupBox(tr("日期关键字筛选"));
    box->setLayout(lay);
    return box;
}

QGroupBox* SqlDBQueryPanel::initright()
{
    mCommand = new QComboBox;
    mPanel = new QLineEdit(tr("sql command..."));

    mExecBtn = new QPushButton(tr("查询"));
    mClearBtn = new QPushButton(tr("清除"));
    QHBoxLayout * bottomlay = new QHBoxLayout;
    bottomlay->addWidget(mExecBtn);
    bottomlay->addWidget(mClearBtn);

    QVBoxLayout * lay = new QVBoxLayout;

    lay->addWidget(mPanel);
    lay->addWidget(mCommand);
    lay->addLayout(bottomlay);

    auto box = new QGroupBox(tr("命令行筛选"));
    box->setLayout(lay);
    return  box;
}

void SqlDBQueryPanel::showQueryResult(const QString&result)
{
    mStatusBar->showMessage(result);
}

void SqlDBQueryPanel::updateCommand(const QString&table,const QStringList&fields)
{
    mCommand->clear();
    mCommand->addItem("select * from "+table);
    mCommand->addItem("select * from "+table + " where ...");
    mCommand->addItem("select count(*) from "+table);
    mCommand->addItem("select count(*) from "+table +" where ...");
    foreach (auto field, fields)
        mCommand->addItem("select "+field+" from "+table);
}

void SqlDBQueryPanel::updateKeywords(const QString&table,const QStringList&fields)
{
    Q_UNUSED(table);
    mTableFields->clear();
    foreach (auto field, fields)
        mTableFields->addItem(field);
}

void SqlDBQueryPanel::onQueryBtn()
{
     auto text = mPanel->text();
     if (text.isEmpty()) return;
     if (!text.contains("select")) {
         QMessageBox::warning(this,tr("警告"),tr("只支持查询命令select!"));
         return;
     }
     if (text.count("select")>1) {
         QMessageBox::warning(this,tr("警告"),tr("多语句查询只以最后一句为准!"));
         int index = text.lastIndexOf("select");
         text.remove(0,index);

     }
    qDebug()<<"query command = "<<text;
    emit queryCommand(text);
}

void SqlDBQueryPanel::onCommandChanged(const QString& command)
{
    mPanel->setText(command);
}

void SqlDBQueryPanel::onFilterBtn()
{
    auto text = mKeyWordEdit->text().simplified();
    if (text.isEmpty()) return;

    auto key = mTableFields->currentText();
    auto filter = key +" " + mSymbols->currentText() + " \'" + text+"\'";
    emit filterField(filter);
}

void SqlDBQueryPanel::onDateChanged()
{
    auto s = mStartDateEdit->date().toString("yyyyMMdd");
    auto e = mEndDateEdit->date().toString("yyyyMMdd");
    emit dateChanged(s,e);
}

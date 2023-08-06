#include "scandescriptionconfig.h"

ScanDescriptionConfig::ScanDescriptionConfig(QWidget *parent) : GradientHiddenWidget(parent)
{
    mExperName = new QLineEdit;
    mExperPerson = new QLineEdit;
    mCellType = new QLineEdit;
    mWorkGroup = new QComboBox;
    mNewWorkGroup = new QLineEdit;
    mAddWorkGroup = new QPushButton(tr("添加"));

    mExperName->setToolTip(tr("*表示必填项"));
    mExperPerson->setToolTip(tr("*表示必填项"));
    mWorkGroup->addItem("Everyone");
    mWorkGroup->setToolTip(tr("默认权限所有人"));

    auto flay = new QFormLayout;
    flay->addRow(tr("   实验日期"),new QLabel(QDate::currentDate().toString("yyyy/MM/dd")));
    flay->addRow(tr("* 实验名称: "),mExperName);
    flay->addRow(tr("* 实验人员: "),mExperPerson);
    flay->addRow(tr("   细胞类型: "),mCellType);

    flay->addRow(tr("  选择组别: "),mWorkGroup);
    flay->addRow(tr("  添加组别: "),mNewWorkGroup);
    flay->addRow(tr(""),mAddWorkGroup);

    mDescription = new QTextEdit;
    auto boxlay = new QHBoxLayout;
    boxlay->addWidget(mDescription);
    auto box = new QGroupBox(tr("其他实验信息描述"));
    box->setLayout(boxlay);

    header->setText(tr("设置实验信息"));
    mainlay->addLayout(flay);
    mainlay->addWidget(box);

    connect(mAddWorkGroup,&QPushButton::clicked,this,&ScanDescriptionConfig::onAddGroup);
}

void ScanDescriptionConfig::onAddGroup()
{
    auto text = mNewWorkGroup->text().simplified();
    if (text.isEmpty()) {
        QMessageBox::warning(this,tr("警告"),tr("请给添加的组别命名!"));
        return ;
    }
    if (mWorkGroup->findText(text) >=0 ) {
        QMessageBox::warning(this,tr("警告"),tr("组别不允许重名!"));
        return ;
    }
    mWorkGroup->addItem(text);
}

QString ScanDescriptionConfig::experDate() const
{
    return QDate::currentDate().toString("yyyy/MM/dd");
}

QString ScanDescriptionConfig::experName()
{
    auto n = mExperName->text().simplified();
    if (n.isEmpty()) {
        QMessageBox::warning(this,tr("警告"),tr("实验名称为必填项!"));
        return "";
    }
    return n;
}

QString ScanDescriptionConfig::personName()
{
    auto n = mExperPerson->text().simplified();
    if (n.isEmpty()) {
        QMessageBox::warning(this,tr("警告"),tr("实验人员为必填项!"));
        return "";
    }
    return n;
}

QString ScanDescriptionConfig::cellType() const
{
    auto n = mCellType->text().simplified();
    return n;
}

QString ScanDescriptionConfig::description() const
{
    return mDescription->toPlainText();
}

QString ScanDescriptionConfig::workGroup() const
{
    return mWorkGroup->currentText();
}

#ifndef SCANDESCRIPTIONCONFIG_H
#define SCANDESCRIPTIONCONFIG_H

#include "gradienthiddenwidget.h"
#include "qtextedit.h"
#include "qcombobox.h"
#include "qpushbutton.h"
#include "qlineedit.h"
#include "qgroupbox.h"
#include "qformlayout.h"
#include "qdatetime.h"
#include "qmessagebox.h"

class ScanDescriptionConfig : public GradientHiddenWidget
{
    Q_OBJECT
public:
    explicit ScanDescriptionConfig(QWidget *parent = nullptr);
    QString experDate() const;
    QString experName();
    QString personName();
    QString cellType() const;
    QString workGroup() const;
    QString description() const;
private:
    QLineEdit * mExperName;
    QLineEdit * mExperPerson;
    QLineEdit * mCellType;
    QComboBox * mWorkGroup;
    QLineEdit * mNewWorkGroup;
    QPushButton * mAddWorkGroup;
    QTextEdit * mDescription;
    void onAddGroup();
signals:

};

#endif // SCANDESCRIPTIONCONFIG_H

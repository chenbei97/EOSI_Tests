#ifndef SCANPATTERNCONFIG_H
#define SCANPATTERNCONFIG_H

#include "gradienthiddenwidget.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "qlistwidget.h"
#include "qgroupbox.h"
#include "pattern.h"
#include "qmessagebox.h"

class ScanPatternConfig : public GradientHiddenWidget
{
    Q_OBJECT
public:
    explicit ScanPatternConfig(QWidget *parent = nullptr);
    void setPatternSize(int rows,int cols);
    QVector<QPoint> sortSelectedPoints() const;
    QStringList sortNames() const;
    void clearPointsNames();
private:
    Pattern * mPattern;
    QLabel * mTreatNameLabel;
    QLineEdit * mTreatNameEdit;
    QPushButton * mAddTreatBtn;
    QPushButton * mRemoveBtn;
    QPushButton * mRemoveAllBtn;
    QGroupBox * mPatternBox;
    QListWidget * mPatternList;
private:
    QVector<QPoint> mSortSelectedPoints;
private slots:
    void onAddTreat();
    void onRemoveTreat();
    void onRemoveAllTreat();
signals:

};

#endif // SCANPATTERNCONFIG_H

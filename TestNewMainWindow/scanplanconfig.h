#ifndef SCANPLANCONFIG_H
#define SCANPLANCONFIG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QFrame>
#include <QPalette>
#include <QDebug>

class ScanPlanConfig : public QWidget
{
    Q_OBJECT
public:
    enum ScanPlan {Once,Schedule};
    Q_ENUM(ScanPlan);
    explicit ScanPlanConfig(QWidget *parent = nullptr);
private:
    QLabel * headerLabel() const;
    QFrame * horline() const;
    QRadioButton * onceButton() const;
    QRadioButton * scheduleButton() const;
    void scanPlan();
signals:
    void scanPlanChanged(ScanPlan fre);
};

#endif // SCANFPLANCONFIG_H

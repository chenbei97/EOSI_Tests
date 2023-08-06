#ifndef SCANTYPECONFIG_H
#define SCANTYPECONFIG_H

#include <QListWidget>
#include <QHBoxLayout>
#include "gradienthiddenwidget.h"

class ScanTypeConfig : public GradientHiddenWidget
{
    Q_OBJECT
public:
    enum ScanType {Standard,ImageLock,ScratchWound,WholeWell,
                   DilutionCloning,Chemotaxis,Spheroid,NeuronalActivity,EmptyType};
    explicit ScanTypeConfig(QWidget *parent = nullptr);
private:
    QListWidget * typelist;
    QLabel * info;
signals:
    void scanType(ScanType type);
};

#endif // SCANTYPECONFIG_H

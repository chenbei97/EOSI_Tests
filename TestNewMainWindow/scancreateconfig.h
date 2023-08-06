#ifndef SCANCREATECONFIG_H
#define SCANCREATECONFIG_H

#include <QRadioButton>
#include "gradienthiddenwidget.h"

class ScanCreateConfig : public GradientHiddenWidget
{
    Q_OBJECT
public:
    enum ScanCreateMode {New,Current,Previous,EmptyMode};
    Q_ENUM(ScanCreateMode);
    explicit ScanCreateConfig(QWidget *parent = nullptr);
private:
    QRadioButton * createNewButton() const;
    QRadioButton * copyCurrentButton() const;
    QRadioButton * copyPreviousButton() const;
private slots:
    void onCreateConfig();
signals:
    void createMode(ScanCreateMode mode);
};

#endif // SCANCREATECONFIG_H

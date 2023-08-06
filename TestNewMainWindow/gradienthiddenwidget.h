#ifndef GRADIENTHIDDENWIDGET_H
#define GRADIENTHIDDENWIDGET_H

#include "qlabel.h"
#include "qevent.h"
#include "qframe.h"
#include "qlayout.h"
#include "gradienthiddenanimation.h"
#include "qdebug.h"

class GradientHiddenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GradientHiddenWidget(QWidget *parent = nullptr);
    void showEvent(QShowEvent *event) override;
private:
    QLabel * headerLabel() const;
    QFrame * horline() const;
protected:
    QLabel * header;
    QFrame * line;
    QVBoxLayout * mainlay;
private:
    QPropertyAnimation * animation;
signals:

};

#endif // GRADIENTHIDDENWIDGET_H

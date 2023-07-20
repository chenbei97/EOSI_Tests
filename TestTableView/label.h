#ifndef LABEL_H
#define LABEL_H

#include <qlabel.h>
#include <qgraphicseffect.h>
#include <qpropertyanimation.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "Constant.h"
#include "Style.h"

class Label : public QLabel
{
    Q_OBJECT
private:
    QGraphicsOpacityEffect * mEffect;
    QPropertyAnimation * mAnimation;
    bool mEffectSwitch;
    bool mPressEvent;
public:
    explicit Label(QWidget*parent=nullptr);
    explicit Label(const QString&text,QWidget*parent=nullptr);

    ~Label();

    void enableEffect();
    void disableEffect();
    void mousePressEvent(QMouseEvent *e) override;

    void enablePressEvent();
    void disablePressEvent();
    void showEvent(QShowEvent*) override;

};

#endif // LABEL_H

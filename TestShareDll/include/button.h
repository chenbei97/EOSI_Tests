#ifndef BUTTON_H
#define BUTTON_H

#include <QtCore/qglobal.h>
#include "qpushbutton.h"
#include "qpropertyanimation.h"
#include "qgraphicseffect.h"

//#if defined(BUTTON_LIBRARY)
//#  define BUTTON_EXPORT Q_DECL_EXPORT
//#else
//#  define BUTTON_EXPORT Q_DECL_IMPORT
//#endif

class Q_DECL_IMPORT Button :public QPushButton
{
    Q_OBJECT
private:
    QGraphicsOpacityEffect * mEffect;
    QPropertyAnimation * mAnimation;
    bool mEffectSwitch;
public:
    bool mState;
    explicit Button(QWidget* parent = nullptr);
    explicit Button(const QString&text,QWidget* parent = nullptr);

    void resizeEvent(QResizeEvent*e) override;

    void enableEffect();
    void disableEffect();
};

#endif // BUTTON_H

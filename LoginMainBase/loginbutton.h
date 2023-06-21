#ifndef LOGINBUTTON_H
#define LOGINBUTTON_H

#include <QPushButton>
#include <QDebug>

class LoginButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int buttonType READ buttonType WRITE setButtonType NOTIFY buttonTypeChanged)
    Q_ENUMS(ButtonType)
private:
    int mButtionType;
public:
    enum ButtonType{UnDefined=-1, Initial = 1, Next = 0};

    explicit LoginButton(QWidget* parent = nullptr);
    int buttonType() const;
    void setButtonType(int type);
    void drawSkin(const QString& buttonStyle);
signals:
    void buttonTypeChanged(int type);
public slots:
     void  onButtonTypeChanged(int type);
     //void onClicked();
};

#endif // LOGINBUTTON_H

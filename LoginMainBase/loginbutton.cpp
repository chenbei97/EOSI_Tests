#include "loginbutton.h"

LoginButton::LoginButton(QWidget*parent) :QPushButton(parent),mButtionType(ButtonType::UnDefined)
{
    connect(this,&LoginButton::buttonTypeChanged,this,&LoginButton::onButtonTypeChanged);
}

void LoginButton::drawSkin(const QString& buttonStyle)
{
    setStyleSheet(buttonStyle);
}

int LoginButton::buttonType() const
{
    return mButtionType;
}

void LoginButton::setButtonType(int type)
{
    if (type == mButtionType)
        return;
    mButtionType = type;
    emit buttonTypeChanged(mButtionType);
}


void LoginButton::onButtonTypeChanged(int type)
{
    qDebug()<<"type = "<<type;
}




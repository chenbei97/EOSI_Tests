#include "loginmainbase.h"

LoginMain::LoginMain(QWidget* parent) :LoginMainBase(parent)
{
    mMainLay = new QVBoxLayout;
    setLayout(mMainLay);
}

void LoginMain::addButton(QSharedPointer<QPushButton> button)
{
    mMainLay->addWidget(button.data());
}

void LoginMain::addButton(QPushButton* button)
{
    mMainLay->addWidget(button);
}

void LoginMain::removeButton(QSharedPointer<QPushButton> button)
{
    mMainLay->removeWidget(button.get());
}

void LoginMain::drawSkin(QSharedPointer<QPushButton> button,const QString& buttonStyle)
{

}

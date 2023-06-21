#ifndef LOGINMAINBASE_H
#define LOGINMAINBASE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMap>
#include <QHBoxLayout>
#include <QVBoxLayout>

class LoginMainBase : public QWidget
{
    Q_OBJECT
public:
    explicit LoginMainBase(QWidget* parent = nullptr){};
    virtual ~LoginMainBase() {}
    virtual void addButton(QSharedPointer<QPushButton> button) = 0;
    virtual void removeButton(QSharedPointer<QPushButton>button) = 0;
    virtual void drawSkin(QSharedPointer<QPushButton> button, const QString& buttonStyle) = 0;
};

class LoginMain : public LoginMainBase
{
    Q_OBJECT
private:
    QMap<int, QList<QAbstractButton*>> mButtonList;
    QVBoxLayout * mMainLay;
public:
    explicit LoginMain(QWidget* parent = nullptr);
    virtual void addButton(QSharedPointer<QPushButton> button) override;
    virtual void removeButton(QSharedPointer<QPushButton> button) override;
    void addButton(QPushButton* button);
    virtual void drawSkin(QSharedPointer<QPushButton> button, const QString& buttonStyle) override;
};
#endif // LOGINMAINBASE_H

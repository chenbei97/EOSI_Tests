#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>

class Button : public QWidget
{
    Q_OBJECT
    bool isPress;
    QString mText;
    QIcon mIcon;
public:
    Button(QWidget*parent=nullptr);
    Button(const QString&text,QWidget*parent=nullptr);
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    QIcon icon() const;
    void setIcon(const QIcon&icon);
};

#endif // BUTTON_H

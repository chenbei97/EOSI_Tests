﻿/*** 
 * @Author: chenbei97 chenbei_electric@163.com
 * @Date: 2023-10-17 14:30:22
 * @LastEditors: chenbei97 chenbei_electric@163.com
 * @LastEditTime: 2023-10-17 14:31:25
 * @FilePath: \EOS\component\include\widgets\colorbutton.h
 * @Copyright (c) 2023 by ${chenbei}, All Rights Reserved. 
 */
#ifndef EOSI_COLORBUTTON_H
#define EOSI_COLORBUTTON_H

#include "qpushbutton.h"
#include "qcolordialog.h"
#include "widgets.h"

class  ColorButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ColorButton(QWidget*parent= nullptr);
    QColorDialog* colorDialog(const QColor&initColor);
    QColor color() const;
    void setColor(const QColor& color);
private:
    const int btnsize = ColorButtonSize ;
    QColor btncolor = Qt::white;
    void onClick();
};
#endif //EOSI_COLORBUTTON_H

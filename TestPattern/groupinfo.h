﻿/*** 
 * @Author: chenbei97 chenbei_electric@163.com
 * @Date: 2023-10-17 13:27:57
 * @LastEditors: chenbei97 chenbei_electric@163.com
 * @LastEditTime: 2023-10-17 13:28:37
 * @FilePath: \EOS\component\include\widgets\groupinfo.h
 * @Copyright (c) 2023 by ${chenbei}, All Rights Reserved. 
 */
#ifndef EOSI_GROUPINFO_H
#define EOSI_GROUPINFO_H

#include "qlabel.h"
#include "qlineedit.h"
#include "colorbutton.h"

class GroupInfo: public QDialog
{
    Q_OBJECT
public:
    explicit GroupInfo(QWidget*parent= nullptr);
    QColor groupColor() const;
    void setBtnColor(const QColor& color);
private:
    void initObjects();
    void onClick();
    QLineEdit * groupName;
    QLineEdit * tmp1;
    QLineEdit * tmp2;
    QLineEdit * tmp3;
    QPushButton * btn;
    ColorButton * cbtn;
};

#endif //EOSI_GROUPINFO_H

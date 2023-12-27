#ifndef BASICWIDGETTAB_H
#define BASICWIDGETTAB_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QToolButton>
#include <QBoxLayout>
#include <QFormLayout>
#include <QLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QDateTimeEdit>
#include <QProgressBar>
#include <QDebug>
#include <QLineEdit>

class BasicWidgetTab : public QWidget
{
    Q_OBJECT
public:
    explicit BasicWidgetTab(QWidget *parent = nullptr);
    void initObjects();
    void initLayout();
private:
    QPushButton * iconpbtn;
   QPushButton * defaultpbtn;
   QPushButton * flatpbtn;
   QPushButton * pushbutton;
   QRadioButton * radiobutton;
   QToolButton * toolbutton;
   QLineEdit * lineedit;
   QCheckBox * checkbox;

   QComboBox * combobox;
   QDateTimeEdit * datetimeedit;
   QSpinBox * spinbox;
   QDoubleSpinBox * doublespinbox;
    QSlider * slider;
    QProgressBar * progressbar;

signals:

};

#endif // BASICWIDGETTAB_H

#include "basicwidgettab.h"

BasicWidgetTab::BasicWidgetTab(QWidget *parent) : QWidget(parent)
{
    initObjects();
    initLayout();
}


void BasicWidgetTab::initLayout()
{
    auto lay_btn = new QHBoxLayout;
    auto lay_option = new QHBoxLayout;
    auto lay = new QVBoxLayout;
    {
        lay_btn->addWidget(new QLabel("button: "));
        lay_btn->addWidget(pushbutton);
        lay_btn->addWidget(defaultpbtn);
        lay_btn->addWidget(flatpbtn);
        lay_btn->addWidget(iconpbtn);
        lay_btn->addWidget(radiobutton);
        lay_btn->addWidget(checkbox);
        lay_btn->addWidget(lineedit);
        lay_btn->addWidget(toolbutton);
        lay_btn->addStretch();
    }

    {
        lay_option->addWidget(new QLabel("widget: "));
        lay_option->addWidget(combobox);
        lay_option->addWidget(spinbox);
        lay_option->addWidget(doublespinbox);
        lay_option->addWidget(datetimeedit);
        lay_option->addWidget(slider);
        lay_option->addWidget(progressbar);
        lay_option->addStretch();
    }

    lay->addLayout(lay_btn);
    lay->addLayout(lay_option);
    lay->addStretch();
    setLayout(lay);
}

void BasicWidgetTab::initObjects()
{
    {
        checkbox = new QCheckBox("check");
        pushbutton = new QPushButton("pushbtn");
        defaultpbtn = new QPushButton("default");
        iconpbtn = new QPushButton("icon");
        flatpbtn = new QPushButton("flat");
        radiobutton = new QRadioButton("radbtn");
        toolbutton = new QToolButton();
        lineedit = new QLineEdit("hello qss!");

        defaultpbtn->setDefault(true);
        flatpbtn->setFlat(true);
        iconpbtn->setIcon(QIcon("images/setting.png"));
        iconpbtn->setObjectName("iconpbtn");
        lineedit->setReadOnly(true);
    }

    {
        combobox = new QComboBox();
        datetimeedit = new QDateTimeEdit(QDateTime::currentDateTime());
        spinbox = new QSpinBox;
        doublespinbox = new QDoubleSpinBox;
        slider = new QSlider(Qt::Horizontal);
        progressbar = new QProgressBar;
        combobox->addItems(QStringList()<<"A"<<"B"<<"C");
        progressbar->setValue(50);
        progressbar->setFormat("%p%");
    }
}

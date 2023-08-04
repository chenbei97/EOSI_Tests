#ifndef SQLDBQUERYPANEL_H
#define SQLDBQUERYPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QComboBox>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QDebug>

class SqlDBQueryPanel : public QWidget
{
    Q_OBJECT
public:
    explicit SqlDBQueryPanel(QWidget *parent = nullptr);
public slots:
    void showQueryResult(const QString&result);
    void updateCommand(const QString&table,const QStringList&fields);
    void updateKeywords(const QString&table,const QStringList&fields);
private:
    QDateEdit * mStartDateEdit;
    QDateEdit * mEndDateEdit;
    QComboBox * mTableFields;
    QComboBox * mSymbols;
    QLineEdit * mKeyWordEdit;
    QPushButton * mFilterBtn;
    QLineEdit * mPanel;
    QComboBox * mCommand;
    QPushButton * mExecBtn;
    QPushButton * mClearBtn;
    QStatusBar * mStatusBar;
    QGroupBox* initleft();
    QGroupBox* initright();
private slots:
    void onDateChanged();
    void onFilterBtn();
    void onQueryBtn();
    void onCommandChanged(const QString& command);
signals:
    void queryCommand(const QString&q);
    void filterField(const QString&f);
    void dateChanged(const QString&start,const QString&end);
};

#endif // SQLDBQUERYPANEL_H

#ifndef SCANPATTERNPREVIEW_H
#define SCANPATTERNPREVIEW_H

#include "gradienthiddenwidget.h"
#include "pattern.h"
#include "qpushbutton.h"
#include "qgroupbox.h"
#include "qtimer.h"

class ScanPatternPreview : public GradientHiddenWidget
{
    Q_OBJECT
public:
    explicit ScanPatternPreview(QWidget *parent = nullptr);
    void setPatternSize(int rows,int cols);
    void setViews(int count);
    void setSortPoints(const QVector<QPoint>& points);
    void setSortNames(const QStringList& names);
    void clearPointsNames();
private:
    QPushButton * mPreviewBtn;
    Pattern * mPattern;
    QLabel * mPointLocInfo;
    QLabel * mPointNameInfo;
    QLabel * mPointOrderInfo;
    QLabel * mViewsCountInfo;
    QLabel * mPointAllInfo;
    int mViews = 0;
    QVector<QPoint> mSortPoints;
    QStringList mSortNames;
private slots:
    void onPreviewBtn();
signals:

};

#endif // SCANPATTERNPREVIEW_H

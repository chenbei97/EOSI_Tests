#ifndef SPLASH_H
#define SPLASH_H

#include <QSplashScreen>
#include <QProgressBar>
#include <QScreen>
#include <QTimer>
#include <QTime>
#include <QLayout>
#include <QMouseEvent>

class Splash : public QSplashScreen
{
    Q_OBJECT
private:
    QProgressBar * mBar;
    QList<int> mValueList;
public:
    explicit Splash(const QPixmap &pixmap);
    void mousePressEvent(QMouseEvent *) override;
private slots:
    void updateProgress();
signals:
    void end();
};

#endif // SPLASH_H

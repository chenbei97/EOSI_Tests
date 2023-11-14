#ifndef __MAIN_H__
#define __MAIN_H__

#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTimer>
#include <QCheckBox>
#include <QSlider>
#include <QString>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QMessageBox>
#include <toupcam.h>

class MainWidget : public QWidget
{
    Q_OBJECT
    ToupcamDeviceV2 camera;
    HToupcam        toupcam;
    QComboBox*      resolution;
    QCheckBox*      autoexposure;
    QSlider*        exposureTimeSlider;
    QSlider*        exposureGainSlider;
    QSlider *  adjustExposure;
    QSlider*        tempslider;
    QSlider*        tintslider;
    QLabel*         exposureTimeLabel;
    QLabel*         exposureGainLabel;
    QLabel*         m_lbl_temp;
    QLabel*         m_lbl_tint;
    QLabel*         canvas;
    QLabel*         frameRateLabel;
    QPushButton*    autoWhiteBalance;
    QPushButton*    openBtn;
    QPushButton*    captureBtn;
    QTimer*        frameRateTimer;
    unsigned        imgwidth;
    unsigned        imgheight;
    QSharedPointer<uchar> imgdata;
    int             resolutionIndex;
    int             m_temp;
    int             m_tint;
    unsigned        m_count;
private:
    QGroupBox* initResolutionBox();
    QGroupBox* initExposureBox();
    QGroupBox* initTempBox();
public:
    MainWidget(QWidget* parent = nullptr);
protected:
    void closeEvent(QCloseEvent*) override;
signals:
    void evtCallback(unsigned nEvent);
    void imageCaptured(const QImage&m);
private:
    void onBtnOpen();
    void onBtnSnap();
    void handleImageEvent();
    void print_imageInfo(ToupcamFrameInfoV3* info);
    void handleExpoEvent();
    void handleTempTintEvent();
    void handleStillImageEvent();
    void openCamera();
    void closeCamera();
    void startCamera();
    static void __stdcall eventCallBack(unsigned nEvent, void* pCallbackCtx);
    static QVBoxLayout* makeLayout(QLabel*, QSlider*, QLabel*, QLabel*, QSlider*, QLabel*);
};

#endif

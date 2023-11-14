#include <QApplication>
#include "demoqt.h"
#include "qdebug.h"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
    , toupcam(nullptr)
    , frameRateTimer(new QTimer(this))
    , imgwidth(0), imgheight(0), imgdata(nullptr)
    , resolutionIndex(0), m_temp(TOUPCAM_TEMP_DEF), m_tint(TOUPCAM_TINT_DEF), m_count(0)
{
    setMinimumSize(1000, 800);

    QGridLayout* gmain = new QGridLayout();

    auto resolutionBox = initResolutionBox();
    auto exposureBox = initExposureBox();
    auto whiteBox = initTempBox();
    adjustExposure = new QSlider(Qt::Horizontal);
    adjustExposure->setRange(100,50000);

    connect(adjustExposure,&QSlider::valueChanged,[this](auto time){
        qDebug()<<"time = "<<time;
        Toupcam_put_AutoExpoEnable(toupcam, false);
        Toupcam_put_ExpoTime(toupcam, (unsigned)time);
    });

    openBtn = new QPushButton("打开相机");
    connect(openBtn, &QPushButton::clicked, this, &MainWidget::onBtnOpen);
    captureBtn = new QPushButton("拍照");
    captureBtn->setEnabled(false);
    connect(captureBtn, &QPushButton::clicked, this, &MainWidget::onBtnSnap);

    QVBoxLayout* v1 = new QVBoxLayout();
    v1->addWidget(resolutionBox);
    v1->addWidget(exposureBox);
    v1->addWidget(whiteBox);
    v1->addWidget(openBtn);
    v1->addWidget(captureBtn);
    v1->addWidget(adjustExposure);
    v1->addStretch();
    gmain->addLayout(v1, 0, 0);

    frameRateLabel = new QLabel();
    canvas = new QLabel();

    QVBoxLayout* v2 = new QVBoxLayout();
    v2->addWidget(canvas, 1);
    v2->addWidget(frameRateLabel);
    gmain->addLayout(v2, 0, 1);

    gmain->setColumnStretch(0, 1);
    gmain->setColumnStretch(1, 4);
    setLayout(gmain);

    connect(this, &MainWidget::evtCallback, this, [this](unsigned nEvent)
    {
        /* this run in the UI thread */
        if (toupcam)
        {
            //qDebug()<<"event is "<<nEvent;
            if (TOUPCAM_EVENT_IMAGE == nEvent) // 4
                handleImageEvent();
            else if (TOUPCAM_EVENT_EXPOSURE == nEvent) // 1
                handleExpoEvent();
            else if (TOUPCAM_EVENT_TEMPTINT == nEvent) // 2
                handleTempTintEvent();
            else if (TOUPCAM_EVENT_STILLIMAGE == nEvent) // 5
                handleStillImageEvent();
            else if (TOUPCAM_EVENT_ERROR == nEvent) // 128
            {
                closeCamera();
                QMessageBox::warning(this, "Warning", "Generic error.");
            }
            else if (TOUPCAM_EVENT_DISCONNECTED == nEvent) // 129
            {
                closeCamera();
                QMessageBox::warning(this, "Warning", "Camera disconnect.");
            }
        }
    });

    connect(frameRateTimer, &QTimer::timeout, this, [this]()
    {
        unsigned nFrame = 0, nTime = 0, nTotalFrame = 0;
        if (toupcam && SUCCEEDED(Toupcam_get_FrameRate(toupcam, &nFrame, &nTime, &nTotalFrame)) && (nTime > 0))
            frameRateLabel->setText(QString::asprintf("%u, fps = %.1f", nTotalFrame, nFrame * 1000.0 / nTime));
    });

    connect(this,&MainWidget::imageCaptured,[this](auto image) {
        QImage newimage = image.scaled(canvas->width(), canvas->height(), Qt::KeepAspectRatio, Qt::FastTransformation);
        canvas->setPixmap(QPixmap::fromImage(image));
    });
}

void MainWidget::closeCamera()
{
    if (toupcam)
    {
        Toupcam_Close(toupcam);
        toupcam = nullptr;
    }
    imgdata.clear();
    imgdata = nullptr;

    openBtn->setText("打开相机");
    frameRateTimer->stop();
    frameRateLabel->clear();
    autoexposure->setEnabled(false);
    exposureGainSlider->setEnabled(false);
    exposureTimeSlider->setEnabled(false);
    autoWhiteBalance->setEnabled(false);
    tempslider->setEnabled(false);
    tintslider->setEnabled(false);
    captureBtn->setEnabled(false);
    resolution->setEnabled(false);
    resolution->clear();
}

void MainWidget::closeEvent(QCloseEvent*)
{
    closeCamera();
}

void MainWidget::startCamera()
{
    if (imgdata)
    {
        imgdata.clear();
        imgdata = nullptr;
    }
    imgdata = QSharedPointer<uchar>(new uchar[TDIBWIDTHBYTES(imgwidth * 24) * imgheight]);
    qDebug()<<"buffer size = "<<TDIBWIDTHBYTES(imgwidth * 24);

    unsigned uimax = 0, uimin = 0, uidef = 0;
    unsigned short usmax = 0, usmin = 0, usdef = 0;
    Toupcam_get_ExpTimeRange(toupcam, &uimin, &uimax, &uidef);
    exposureTimeSlider->setRange(uimin, uimax);
    Toupcam_get_ExpoAGainRange(toupcam, &usmin, &usmax, &usdef);
    exposureGainSlider->setRange(usmin, usmax);

    if (0 == (camera.model->flag & TOUPCAM_FLAG_MONO))
        handleTempTintEvent();
    handleExpoEvent();
    if (SUCCEEDED(Toupcam_StartPullModeWithCallback(toupcam, eventCallBack, this)))
    {
        resolution->setEnabled(true);
        autoexposure->setEnabled(true);
        autoWhiteBalance->setEnabled(0 == (camera.model->flag & TOUPCAM_FLAG_MONO));
        tempslider->setEnabled(0 == (camera.model->flag & TOUPCAM_FLAG_MONO));
        tintslider->setEnabled(0 == (camera.model->flag & TOUPCAM_FLAG_MONO));
        openBtn->setText("关闭相机");
        captureBtn->setEnabled(true);

        int bAuto = 0;
        Toupcam_get_AutoExpoEnable(toupcam, &bAuto);
       autoexposure->setChecked(1 == bAuto);
        
        frameRateTimer->start(1000);
    }
    else
    {
        closeCamera();
        QMessageBox::warning(this, "Warning", "Failed to start camera.");
    }
}

void MainWidget::openCamera()
{
    toupcam = Toupcam_Open(camera.id);
    if (toupcam)
    {
        Toupcam_get_eSize(toupcam, (unsigned*)&resolutionIndex);
        imgwidth = camera.model->res[resolutionIndex].width;
        imgheight = camera.model->res[resolutionIndex].height;
        {
            const QSignalBlocker blocker(resolution);
            resolution->clear();
            for (unsigned i = 0; i < camera.model->preview; ++i)
                resolution->addItem(QString::asprintf("%u*%u", camera.model->res[i].width, camera.model->res[i].height));
            resolution->setCurrentIndex(resolutionIndex);
            resolution->setEnabled(true);
        }

        Toupcam_put_Option(toupcam, TOUPCAM_OPTION_BYTEORDER, 0); //Qimage use RGB byte order
        Toupcam_put_AutoExpoEnable(toupcam, 1);
        startCamera();
    }
}

void MainWidget::onBtnOpen()
{
    if (toupcam)
        closeCamera();
    else
    {
        ToupcamDeviceV2 arr[TOUPCAM_MAX] = { 0 };
        unsigned count = Toupcam_EnumV2(arr);
        if (0 == count)
            QMessageBox::warning(this, "Warning", "No camera found.");
        else if (1 == count)
        {
            camera = arr[0];
            openCamera();
        }
        else
        {
            QMenu menu;
            for (unsigned i = 0; i < count; ++i)
            {
                menu.addAction(
#if defined(_WIN32)
                            QString::fromWCharArray(arr[i].displayname)
#else
                            arr[i].displayname
#endif
                            , this, [this, i, arr](bool)
                {
                    camera = arr[i];
                    openCamera();
                });
            }
            menu.exec(mapToGlobal(captureBtn->pos()));
        }
    }
}

void MainWidget::onBtnSnap()
{
    if (toupcam)
    {
//        if (0 == camera.model->still)    // not support still image capture
//        {
//            qDebug()<<"not support still image capture";
//            if (imgdata)
//            {
//                QImage image(imgdata.get(), imgwidth, imgheight, QImage::Format_RGB888);
//                image.save(QString::asprintf("demoqt_%u.jpg", ++m_count));
//            }
//        }
//        else
//        {
//            qDebug()<<"support still image capture still = "<<camera.model->still;
//            QMenu menu;
//            for (unsigned i = 0; i < camera.model->still; ++i)
//            {
//                menu.addAction(QString::asprintf("%u*%u", camera.model->res[i].width, camera.model->res[i].height), this, [this, i](bool)
//                {
//                    qDebug()<<"i = "<<i;
//                    Toupcam_Snap(toupcam, i); // 触发handleStillImageEvent
//                });
//            }
//            menu.exec(mapToGlobal(captureBtn->pos()));
//        }
    }
    // 不需要不同分辨率就这样即可
        if (imgdata)
        {
            QImage image(imgdata.get(), imgwidth, imgheight, QImage::Format_RGB888);
            image.save(QString::asprintf("demoqt_%u.jpg", ++m_count));
        }
}

void MainWidget::eventCallBack(unsigned nEvent, void* pCallbackCtx)
{
    MainWidget* pThis = reinterpret_cast<MainWidget*>(pCallbackCtx);
    emit pThis->evtCallback(nEvent);
}

void MainWidget::handleImageEvent()
{
//    unsigned width = 0, height = 0;
//    if (SUCCEEDED(Toupcam_PullImage(toupcam, imgdata.get(), 24, &width, &height)))
//    {
//        QImage image(imgdata.get(), width, height, QImage::Format_RGB888);
//        qDebug()<<image.size()<<_msize(imgdata.get());
//        QImage newimage = image.scaled(canvas->width(), canvas->height(), Qt::KeepAspectRatio, Qt::FastTransformation);
//        canvas->setPixmap(QPixmap::fromImage(newimage));
//        emit imageCaptured(newimage);
//    }
    int rowPitch = 0;
    int bStill = 0; // 拉取图像要求设置为0
    int bits = 24; // 默认就是24bit
    ToupcamFrameInfoV3 info;
    if (SUCCEEDED(Toupcam_PullImageV3(toupcam, imgdata.get(),
                                      bStill, bits, rowPitch, &info))){
        print_imageInfo(&info);

        // imgdata分配了多大内存读取就使用多大内存,_msize可以计算分配的内存
        //auto image = QImage::fromData(imgdata.get(), _msize(imgdata.get()),"jpg");
       //auto image = QImage(imgdata.get(), info.width, info.height, QImage::Format_BGR888);
       auto image = QImage(imgdata.get(), info.width, info.height, QImage::Format_RGB888);
        //auto image = QImage(imgdata.get(), info.width, info.height, QImage::Format_RGBX8888);
       //auto img = image.convertToFormat(QImage::Format_RGB32);
       // 不要在回调函数内作图像scaled和setPixmap
        //QImage newimage = image.scaled(canvas->width(), canvas->height(), Qt::KeepAspectRatio, Qt::FastTransformation);
       //canvas->setPixmap(QPixmap::fromImage(image));
        emit imageCaptured(image); // 在槽函数内去scaled不会卡
    } else {
         qDebug()<<"pull image failed";
    }
}

void MainWidget::print_imageInfo(ToupcamFrameInfoV3* info)
{
    qDebug()<<"w = "<<info->width<<" h = "<<info->height
    <<"exp = "<<info->expotime<<" gain = "<<info->expogain;
}

void MainWidget::handleExpoEvent()
{
    unsigned time = 0;
    unsigned short gain = 0;
    Toupcam_get_ExpoTime(toupcam, &time);
    Toupcam_get_ExpoAGain(toupcam, &gain);
    {
        const QSignalBlocker blocker(exposureTimeSlider);
        exposureTimeSlider->setValue(int(time));
    }
    {
        const QSignalBlocker blocker(exposureGainSlider);
        exposureGainSlider->setValue(int(gain));
    }
    exposureTimeLabel->setText(QString::number(time));
    exposureGainLabel->setText(QString::number(gain));
}

void MainWidget::handleTempTintEvent()
{
    int nTemp = 0, nTint = 0;
    if (SUCCEEDED(Toupcam_get_TempTint(toupcam, &nTemp, &nTint)))
    {
        {
            const QSignalBlocker blocker(tempslider);
            tempslider->setValue(nTemp);
        }
        {
            const QSignalBlocker blocker(tintslider);
            tintslider->setValue(nTint);
        }
        m_lbl_temp->setText(QString::number(nTemp));
        m_lbl_tint->setText(QString::number(nTint));
    }
}

void MainWidget::handleStillImageEvent()
{
//    unsigned width = 0, height = 0;
//    if (SUCCEEDED(Toupcam_PullStillImage(toupcam, nullptr, 24, &width, &height))) // peek
//    {
//        std::vector<uchar> vec(TDIBWIDTHBYTES(width * 24) * height);
//        if (SUCCEEDED(Toupcam_PullStillImage(toupcam, &vec[0], 24, &width, &height)))
//        {
//            QImage image(&vec[0], width, height, QImage::Format_RGB888);
//            image.save(QString::asprintf("demoqt_%u.jpg", ++m_count));
//        }
//    }

}

QVBoxLayout* MainWidget::makeLayout(QLabel* lbl1, QSlider* sli1, QLabel* val1, QLabel* lbl2, QSlider* sli2, QLabel* val2)
{
    QHBoxLayout* hlyt1 = new QHBoxLayout();
    hlyt1->addWidget(lbl1);
    hlyt1->addStretch();
    hlyt1->addWidget(val1);
    QHBoxLayout* hlyt2 = new QHBoxLayout();
    hlyt2->addWidget(lbl2);
    hlyt2->addStretch();
    hlyt2->addWidget(val2);
    QVBoxLayout* vlyt = new QVBoxLayout();
    vlyt->addLayout(hlyt1);
    vlyt->addWidget(sli1);
    vlyt->addLayout(hlyt2);
    vlyt->addWidget(sli2);
    return vlyt;
}

QGroupBox* MainWidget::initResolutionBox()
{
    QGroupBox* box = new QGroupBox("分辨率");
    resolution = new QComboBox();
    resolution->setEnabled(false);
    connect(resolution, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
    {
            if (toupcam) //step 1: stop camera
                Toupcam_Stop(toupcam);

            resolutionIndex = index;
            imgwidth = camera.model->res[index].width;
            imgheight = camera.model->res[index].height;

            if (toupcam) //step 2: restart camera
            {
                Toupcam_put_eSize(toupcam, static_cast<unsigned>(resolutionIndex));
                startCamera();
            }
    });

        QVBoxLayout* v = new QVBoxLayout();
        v->addWidget(resolution);
        box->setLayout(v);
        return box;
}

QGroupBox* MainWidget::initExposureBox()
{
        QGroupBox* box = new QGroupBox("曝光值");
       autoexposure = new QCheckBox("自动曝光");
       autoexposure->setEnabled(false);
        exposureTimeLabel= new QLabel("0");
        exposureGainLabel = new QLabel("0");
        exposureTimeSlider = new QSlider(Qt::Horizontal);
        exposureGainSlider = new QSlider(Qt::Horizontal);
        exposureTimeSlider->setEnabled(false);
        exposureGainSlider->setEnabled(false);
        connect(autoexposure, &QCheckBox::stateChanged, this, [this](bool state)
        { // 勾选自动曝光就不能手动设置曝光时间和增益
            if (toupcam)
            {
                Toupcam_put_AutoExpoEnable(toupcam, state ? 1 : 0);
                exposureTimeSlider->setEnabled(!state);
                exposureGainSlider->setEnabled(!state);
            }
        });
        connect(exposureTimeSlider, &QSlider::valueChanged, this, [this](int value)
        {
            if (toupcam)
            { // 显示曝光的值
                exposureTimeLabel->setText(QString::number(value));
                int enable = 0;
                Toupcam_get_AutoExpoEnable(toupcam,&enable);
                qDebug()<<"autoenable? "<<enable;
                if (!autoexposure->isChecked())
                   Toupcam_put_ExpoTime(toupcam, value);
            }
        });
        connect(exposureGainSlider, &QSlider::valueChanged, this, [this](int value)
        {
            if (toupcam)
            {
                exposureGainLabel->setText(QString::number(value));
                if (!autoexposure->isChecked())
                    Toupcam_put_ExpoAGain(toupcam, value);
            }
        });

        QVBoxLayout* v = new QVBoxLayout();
        v->addWidget(autoexposure);
        v->addLayout(makeLayout(new QLabel("Time(us):"), exposureTimeSlider, exposureTimeLabel, new QLabel("Gain(%):"), exposureGainSlider, exposureGainLabel));
        box->setLayout(v);
        return box;
}

QGroupBox* MainWidget::initTempBox()
{
        QGroupBox* box = new QGroupBox("白平衡");
        autoWhiteBalance = new QPushButton("自动平衡");
        autoWhiteBalance->setEnabled(false);
        connect(autoWhiteBalance, &QPushButton::clicked, this, [this]()
        {
            Toupcam_AwbOnce(toupcam, nullptr, nullptr);
        });
        m_lbl_temp = new QLabel(QString::number(TOUPCAM_TEMP_DEF));
        m_lbl_tint = new QLabel(QString::number(TOUPCAM_TINT_DEF));
        tempslider = new QSlider(Qt::Horizontal);
        tintslider = new QSlider(Qt::Horizontal);
        tempslider->setRange(TOUPCAM_TEMP_MIN, TOUPCAM_TEMP_MAX);
        tempslider->setValue(TOUPCAM_TEMP_DEF);
        tintslider->setRange(TOUPCAM_TINT_MIN, TOUPCAM_TINT_MAX);
        tintslider->setValue(TOUPCAM_TINT_DEF);
        tempslider->setEnabled(false);
        tintslider->setEnabled(false);
        connect(tempslider, &QSlider::valueChanged, this, [this](int value)
        {
            m_temp = value;
            if (toupcam)
                Toupcam_put_TempTint(toupcam, m_temp, m_tint);
            m_lbl_temp->setText(QString::number(value));
        });
        connect(tintslider, &QSlider::valueChanged, this, [this](int value)
        {
            m_tint = value;
            if (toupcam)
                Toupcam_put_TempTint(toupcam, m_temp, m_tint);
            m_lbl_tint->setText(QString::number(value));
        });

        QVBoxLayout* v = new QVBoxLayout();
        v->addLayout(makeLayout(new QLabel("Temperature:"), tempslider, m_lbl_temp, new QLabel("Tint:"), tintslider, m_lbl_tint));
        v->addWidget(autoWhiteBalance);
        box->setLayout(v);
        return box;
}

int main(int argc, char* argv[])
{
    Toupcam_GigeEnable(nullptr, nullptr);
    QApplication a(argc, argv);
    MainWidget mw;
//    QObject::connect(&mw,&MainWidget::imageCaptured,[=](auto image){
//        qDebug()<<"capture image's size = "<<image.size();
//    });
    mw.show();
    return a.exec();
}

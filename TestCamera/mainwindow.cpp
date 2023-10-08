#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    camera = new QCamera(QCameraInfo::defaultCamera());
    vwidget = new QVideoWidget();
    capture = new QCameraImageCapture(camera);
    btn = new QPushButton("capture");
    pic = new QLabel;

    camera->setViewfinder(vwidget);
   camera->setCaptureMode(QCamera::CaptureMode::CaptureViewfinder); // 设置无效

    qDebug()<<"mainwinwo--------------------------------------------";
    qDebug()<<camera->errorString();
    qDebug()<<"Supported(QCamera::CaptureViewfinder) = "<<(camera->isCaptureModeSupported(QCamera::CaptureViewfinder));
    qDebug()<<"Supported(QCamera::CaptureStillImage) = "<<(camera->isCaptureModeSupported(QCamera::CaptureStillImage));
    qDebug()<<"Supported(QCamera::CaptureVideo) = "<<(camera->isCaptureModeSupported(QCamera::CaptureVideo));
    qDebug()<<(camera->captureMode()==QCamera::CaptureStillImage);
    qDebug()<<camera->exposure();
    qDebug()<<camera->focus();
    qDebug()<<camera->imageProcessing();
    qDebug()<<camera->supportedLocks();
    //qDebug()<<camera->supportedViewfinderSettings();
    qDebug()<<"supportedViewfinderResolutions() = "<<camera->supportedViewfinderResolutions();
    qDebug()<<"supportedViewfinderPixelFormats() = "<<camera->supportedViewfinderPixelFormats();
    qDebug()<<"supportedViewfinderFrameRateRanges.count = "<<camera->supportedViewfinderFrameRateRanges().count();
    foreach(auto range, camera->supportedViewfinderFrameRateRanges())
        qDebug()<<"range: "<<range.maximumFrameRate<<range.minimumFrameRate;
    qDebug()<<"supportedViewfinderPixelFormats() = "<<camera->supportedViewfinderPixelFormats();
    auto settings = QCameraViewfinderSettings();
    settings.setResolution(640,480); // 目前试出来还有320,240可以
    //settings.setMinimumFrameRate(15.0); // 不支持任何范围
//    settings.setMaximumFrameRate(30.0);
    //settings.setPixelFormat(QVideoFrame::Format_Jpeg); // 不支持任何格式
    camera->setViewfinderSettings(settings);
    qDebug()<<camera->viewfinderSettings().resolution();
    qDebug()<<camera->viewfinderSettings().pixelFormat();
    qDebug()<<camera->viewfinderSettings().pixelAspectRatio();
    qDebug()<<camera->viewfinderSettings().maximumFrameRate();
    qDebug()<<camera->viewfinderSettings().minimumFrameRate();

//    qDebug()<<camera->exposure()->flashMode();
//    qDebug()<<camera->exposure()->exposureMode();
//    qDebug()<<camera->exposure()->isAvailable();
//    qDebug()<<camera->exposure()->isExposureModeSupported(QCameraExposure::ExposureNight);
//    qDebug()<<camera->exposure()->isoSensitivity();
//    qDebug()<<camera->exposure()->isFlashReady();
//    qDebug()<<camera->exposure()->meteringMode();
//    qDebug()<<camera->exposure()->requestedAperture();
//    qDebug()<<camera->exposure()->requestedShutterSpeed();
//    qDebug()<<camera->exposure()->requestedIsoSensitivity();
//    qDebug()<<camera->exposure()->shutterSpeed();
//    qDebug()<<camera->exposure()->supportedApertures();
//    qDebug()<<camera->exposure()->supportedShutterSpeeds();
//    qDebug()<<camera->exposure()->supportedIsoSensitivities();



    qDebug()<<"--------------------------------------------------------";
    vwidget->setBrightness(50);
    vwidget->setContrast(100); // 对比度
    vwidget->setHue(100);//此属性用于调整显示视频的色调
    qDebug()<<vwidget->aspectRatioMode();
    qDebug()<<vwidget->brightness(); // 此属性用于调整显示视频的亮度。
    qDebug()<<vwidget->contrast();
    qDebug()<<vwidget->hue();
    qDebug()<<vwidget->isFullScreen();
    qDebug()<<vwidget->saturation();

    qDebug()<<"--------------------------------------------------------";

    qDebug()<<capture->bufferFormat(); // Format_RGB32
    qDebug()<<capture->isReadyForCapture(); // false
    qDebug()<<capture->supportedImageCodecs();//("bmp", "cur", "icns", "ico", "jpeg", "jpg", "pbm", "pgm", "png", "ppm", "tif", "tiff", "wbmp", "webp", "xbm", "xpm")
    qDebug()<<capture->supportedResolutions(); // ()
    qDebug()<<capture->supportedBufferFormats(); // (Format_RGB32)
    capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    auto codec = QImageEncoderSettings();
    codec.setCodec("ico");
    //codec.setResolution(640,480); // 必须一致,否则错误
    codec.setQuality(QMultimedia::VeryHighQuality);
    capture->setEncodingSettings(codec);
    qDebug()<<"encodingSettings().codec() = "<<capture->encodingSettings().codec();
    connect(capture,&QCameraImageCapture::imageCaptured,[=](int id,const QImage&img){
        pic->setPixmap(QPixmap::fromImage(img));
        qDebug()<<"image captured id = "<<id;
    });
    connect(capture,&QCameraImageCapture::imageSaved,[=](int id,const QString& path){
        qDebug()<<"image save id = "<<id<<" path = "<<path;
       // pic->setPixmap(QPixmap(path));
    });

    auto record = new QMediaRecorder(camera);
    qDebug()<<"support record? "<<record->isAvailable();
    auto box = new QGroupBox;
    auto lay = new QVBoxLayout;
    lay->addWidget(pic);
    lay->addWidget(btn);
    box->setLayout(lay);

    auto s = new QSplitter ;
    s->addWidget(vwidget);
    s->addWidget(box);
    connect(btn,&QPushButton::clicked,[=]{
        camera->searchAndLock();
        capture->capture();
        camera->unlock();
    });

    setCentralWidget(s);

    resize(2000,1000);

    camera->start();
}

MainWindow::~MainWindow()
{
    camera->stop();
}


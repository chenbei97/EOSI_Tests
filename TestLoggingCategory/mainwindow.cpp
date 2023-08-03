#include "mainwindow.h"
//Q_LOGGING_CATEGORY(mylog, "mymodule.mylog")
//也可以加上初始日志级别
// in one source file
Q_LOGGING_CATEGORY(driverUsb, "driver.usb");
Q_LOGGING_CATEGORY(driverUsbEvents, "driver.usb.events", QtWarningMsg);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //QT_LOGGING_RULES="*.debug=false;driver.usb.debug=true";
    QLoggingCategory::setFilterRules("*.debug=false\n"
                                         "driver.usb.debug=true");
    // usbEntries() will only be called if driverUsb category is enabled
        qCDebug(driverUsb) << "devices: " << 123;

        QLoggingCategory category("driver.usb");
            qCCritical(category, "a critical message logged into category %s", category.categoryName());

}

MainWindow::~MainWindow()
{
}


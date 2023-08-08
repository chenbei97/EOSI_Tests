#ifndef CORE_H
#define CORE_H

#define SplashProgressBarMaxLimit 10000 // 进度条的最大值
#define SPLASH_LOAD_TIME 1000 // splash启动的时间 , /100是每次设置进度条的延时时间
#define MAIN_SPLASH_RELATIVE_TIME 150 // main和splash启动的最大相对时间差 150/1000= 90%~100%之间
#define MAIN_LOAD_TIME (SPLASH_LOAD_TIME-QRandomGenerator::global()->bounded(1,MAIN_SPLASH_RELATIVE_TIME+1)) // 主窗口定时启动的延迟时间

#define QTIMER_LOAD_MAIN 0 // 解决问题
//#define QINVOKE_LOAD_MAIN 1 // 从结果来看也是等待创建main完毕才启动splash
//#define QSLOT_LOAD_MAIN 2 // 总是先构造main才会启动splash,会阻塞splash
//#define DIRECT_LOAD_MAIN 3 // 直接启动,就是不再login=accepted动态创建

/*
 * 16:9 => [1366*768 1600*900](不支持) 1920*1080(最常见) 3840*2160(不支持)
 * 16:10 =>1440*900(不支持) 2560*1600(常见) 2880*1800(不支持)
 * 3:2 => 2160*1440 2256*1504 3000*2000 (不支持)
 * 1280 * 800的尺寸（小屏幕）
*/
#define SCREEN_2560X1600 (2560*1600)
//#define SCREEN_1920X1080 (1920*1080)
//#define SCREEN_1280X800 (1280*800)
//#define SCREEN_3840X2160 (3840*2160)

#endif // CORE_H

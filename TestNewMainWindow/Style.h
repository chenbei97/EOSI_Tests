#ifndef STYLE_H
#define STYLE_H

#include "core/core.h"
/*
qss不是完全支持所有的css2，比如text-align官方文档就有说明，只支持 QPushButton and QProgressBar
qss的执行是有优先级的，如果没有指定父对象，则对所有的应用
比如在窗体widget中 {color:#ff0000;} 这样会对widget以及widget的所有子对象应用该样式
你需要指定类名或者对象名，比如 #widget{color:#ff0000;} 这样就只会对widget对象应用该样式
另一种写法 QWidget#widget{color:#ff0000;}，只想对窗体本身而不是子控件按钮标签等 .QWidget{color:#ff0000;}
*/


// 主要是修改字体大小
#ifdef SCREEN_1920X1080
    #define LoginLogo_BeiHuiKeJi_Style ("QLabel#beihuikeji{font-size: 40px; font-family: '黑体'; "\
                                                                  "font: bold; border: solid 1px;color:white;}")
    // 新建用户和忘记密码2个按钮的风格
    #define LoginMain_CreateUserForgetPwdStyle ("QPushButton#createuser,#forgetpwd{border:none;color:#919191;font-size:20px;}")

    // 新建实验的实验类型按钮风格 NewExperButtonMinHeight=70,圆角半径<35至少,实际30也不管用
    #define MainNewExper_ButtonStyle ("color:white;border:2px solid black;border-radius:25px;"\
                                                                "background-color:#2F7CAD;font-size:30px;") // 圆角半径小一些
    // 登录窗口的按钮风格
    #define LoginMain_ButtonStyle ("border:2px solid black;border-radius:5px;background-color:skyblue;font-size:50px;")

    // 点击3个按钮,当前实验、新建实验和查询实验切换按钮的颜色
    //https://blog.csdn.net/goforwardtostep/article/details/53464925
    // "QPushButton:pressed{padding-left:8px;padding-top:8px;background-color:#B5E61D;}" /*凸起效果*/
    #define MainTool_ButtonStyle1 ("QPushButton{color:white;border:2px solid black;"\
                                                    "width:50px;height:50px;border-radius:25px;"\
                                                    "background-color:#0B5D18;font-size:50px;}")
    #define MainTool_ButtonStyle2 ("QPushButton{color:white;border:2px solid black;"\
                                                    "width:50px;height:50px;border-radius:25px;"\
                                                    "background-color:#B5E61D;font-size:50px;}")

#elif SCREEN_2560X1600
    #define LoginLogo_BeiHuiKeJi_Style ("QLabel#beihuikeji{font-size: 60px; font-family: '黑体'; "\
                                                                      "font: bold; border: solid 1px;color:white;}")
    // 新建用户和忘记密码2个按钮的风格
    #define LoginMain_CreateUserForgetPwdStyle ("QPushButton#createuser,#forgetpwd{border:none;color:#919191;font-size:28px;}")

    // 新建实验的实验类型按钮风格
    #define MainNewExper_ButtonStyle ("color:white;border:2px solid black;border-radius:50px;"\
                                                                "background-color:#2F7CAD;font-size:30px;")
    // 登录窗口的按钮风格
    #define LoginMain_ButtonStyle ("border:2px solid black;border-radius:5px;background-color:skyblue;font-size:50px;")

    // 点击3个按钮,当前实验、新建实验和查询实验切换按钮的颜色
    //https://blog.csdn.net/goforwardtostep/article/details/53464925
    // "QPushButton:pressed{padding-left:8px;padding-top:8px;background-color:#B5E61D;}" /*凸起效果*/
    #define MainTool_ButtonStyle1 ("QPushButton{color:white;border:2px solid black;"\
                                                    "width:50px;height:50px;border-radius:25px;"\
                                                    "background-color:#0B5D18;font-size:50px;}")
    #define MainTool_ButtonStyle2 ("QPushButton{color:white;border:2px solid black;"\
                                                    "width:50px;height:50px;border-radius:25px;"\
                                                    "background-color:#B5E61D;font-size:50px;}")
#else SCREEN_1280X800
    #define LoginLogo_BeiHuiKeJi_Style ("QLabel#beihuikeji{font-size: 30px; font-family: '黑体'; "\
                                                                      "font: bold; border: solid 1px;color:white;}")
    // 新建用户和忘记密码2个按钮的风格
    #define LoginMain_CreateUserForgetPwdStyle ("QPushButton#createuser,#forgetpwd{border:none;color:#919191;font-size:16px;}")

    // 新建实验的实验类型按钮风格
    #define MainNewExper_ButtonStyle ("color:white;border:2px solid black;border-radius:20px;"\
                                                                "background-color:#2F7CAD;font-size:20px;")
    // 登录窗口的按钮风格
    #define LoginMain_ButtonStyle ("border:2px solid black;border-radius:5px;background-color:skyblue;font-size:30px;")

    // 点击3个按钮,当前实验、新建实验和查询实验切换按钮的颜色
    //https://blog.csdn.net/goforwardtostep/article/details/53464925
    // "QPushButton:pressed{padding-left:8px;padding-top:8px;background-color:#B5E61D;}" /*凸起效果*/
    #define MainTool_ButtonStyle1 ("QPushButton{color:white;border:2px solid black;"\
                                                    "width:50px;height:50px;border-radius:25px;"\
                                                    "background-color:#0B5D18;font-size:30px;}")
    #define MainTool_ButtonStyle2 ("QPushButton{color:white;border:2px solid black;"\
                                                    "width:50px;height:50px;border-radius:25px;"\
                                                    "background-color:#B5E61D;font-size:30px;}")
#endif


// 必须使用QWidget#Widget或QWidget#LoginMain,否则子控件的背景也会被设置,只设置窗口的
#define LoginMain_Style  ("QWidget#LoginMain{background-image:url(:/images/login_back.jpg)}")



#define ExperTitle_Style ("QLabel#expertitle{background-color:yellow;"\
                    "border:none;font-size:30px;color:green;font-weight:bold;}")



// 其他, component's style
#define SplitterStyle ("QSplitter::handle { background-color: #F2A072 }")
#define ProgressBarStyle ("QProgressBar{border:2px solid grey;border-radius:5px;text-align:center;}"\
                                    "QProgressBar::chunk{background-color: #CD96CD;width: 10px;margin: 0.5px;}")





//#define MainStackStyle ("border: 2px solid black; margin:20px;")
#define MainStackStyle ("border: none")

#define LoginGroupBoxStyle ("border:1px solid black;"\
                                                "background-color:lightgrey;"\
                                                "font-size:30px;"\
                                                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"\
                                                "stop: 0 #E0E0E0, stop: 1 #FFFFFF);")

#define MainQueryExperGroupBoxStyle ("QGroupBox {border:1px solid black;color:black;"\
                                                "background-color:lightgrey;"\
                                                "margin-top:20px;"\
                                                "font-size:30px;"\
                                                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"\
                                                "stop: 0 #E0E0E0, stop: 1 #FFFFFF);}"\
                                                 "QGroupBox > QLabel {border:none;font-size:25px;}")



#define LoginUserPwdValidateStyle ("QPushButton {"\
                                                            "border: 2px solid #EA224B;"\
                                                            "border-radius: 10px;"\
                                                            "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"\
                                                                                              "stop: 0 #f6f7fa, stop: 1 #75FA8D);"\
                                                            "min-width: 80px;"\
                                                            "color:#2F79E6;"\
                                                            "}")

//#define LoginLineEditStyle ("QLineEdit{"\
//                                                "border: 2px solid green;"\
//                                                "border-radius: 10px;"\
//                                                "padding: 0 8px;"\
//                                                "background: #F7F552;"\
//                                                "selection-background-color: darkgray;"\
//                                                "};")

#define LoginDbDirLabelStyle  ("QLabel{"\
                                                "border: 2px solid green;"\
                                                "border-radius: 10px;"\
                                                "padding: 2px;"\
                                                "background-color:#F7F552;"\
                                                "}")





#define MainQueryComboBoxStyle ("QComboBoc{border: 1px solid gray;"\
                                                            "border-radius: 3px;"\
                                                            "padding: 1px 18px 1px 3px;"\
                                                            "min-width: 6em;}"\
                                                            "QComboBox>QLineEdit{color:black;font-size:25px;}"\
                                                            "QComboBox::drop-down {"\
                                                            "subcontrol-origin: padding;"\
                                                            "subcontrol-position: top right;"\
                                                            "width: 15px;"\
                                                            "border-left-width: 1px;"\
                                                            "border-left-color: black;"\
                                                            "border-left-style: solid; "\
                                                            "border-top-right-radius: 3px;"\
                                                            "border-bottom-right-radius: 3px;}"\
                                                            "QComboBox:on {padding-top: 3px;padding-left: 4px;}")




#endif // STYLE_H

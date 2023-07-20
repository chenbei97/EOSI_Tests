#ifndef CONSTANT_H
#define CONSTANT_H
//#pragma execution_character_set("utf-8")
// pro文件CONFIG   += utf8_source 也是可以的

//#if defined __cplusplus
//#include <stdlib.h>
//#include <iostream>
//#include <vector>
//#endif

#include "core/core.h"
#include <qdebug.h>
// 便捷函数

#define INIT_MINSIZE(w,h) (setMinimumSize(w,h))
#define INIT_MINWIDTH(w) (setMinimumWidth(w))
#define INIT_MINHEIGHT(w) (setMinimumHeight(w))
#define INIT_MAXSIZE(w,h) (setMaximumSize(w,h))
#define INIT_MAXWIDTH(w) (setMaximumWidth(w))
#define INIT_MAXHEIGHT(h) (setMaximumHeight(h))
#define INIT_RESIZE(w,h) (resize(w,h))
#define INIT_RESIZE_GOLDENSIZE (resize(width(),(int)(width()*0.618)))
#define SQLQUERYQDebug(q) (qDebug()<<"record => "<<q.lastError().text() <<"  "<<q.isActive()<<"  "<<q.record())
#define LOG (qDebug()<<"["<<__FUNCTION__<<"] ")

// 其它常量
#define IPLimit ("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b") // 限定输入IP地址正则表达式
#define PWDLimit ("^(?![A-Za-z0-9]+$)(?![a-z0-9\\W]+$)(?![A-Za-z\\W]+$)(?![A-Z0-9\\W]+$)[a-zA-Z0-9\\W]{8,20}$") // 限定8位数字字母大小写密码
#define AnimationDuration_1000ms 1000 // 渐变动画周期
#define TimerDuration_1000ms 1000 // 时间控件定时周期
#define SplitterHandleWidth 5 // 分隔条的手柄宽度
#define DefaultFontFamily ("Times New Roman") // 默认字体
#define TableViewHighlightColorAlpha 100 // 单元格高亮颜色的透明度0-255之间

#ifdef SCREEN_2560X1600 // 默认按照2560X1600的尺寸
    #define DefaultFontSize 12 // 默认字体大小12号字
    #define WindowWidth 1800
    #define WindowHeight 1000
    // 登录窗口设置
    #define LoginButtonHeight 180 // button的高度也是整体行布局的高度
    #define LoginButtonWidth 630 // button的宽度-和groubox一致比较好看
    #define LoginGap1 200 // button和groupbox的距离
    #define LoginGroupboxWidth 630 // groupbox 因为单行控件最小默认300宽度,宽度要调整>600
    #define LoginGroupboxHeight LoginButtonHeight // groupbox-button高度一致
    #define LoginGap2 15 // icon和groupbox的距离
    #define LoginIconSize 32 // icon的size
    #define LoginLeftMarginCompensate 150 // 左边距补偿
    #define LoginRightMargin ((WindowWidth-LoginButtonWidth-LoginGap1-\
                                                LoginGroupboxWidth-LoginGap2-LoginIconSize)/2) // 计算出应有的左右边距
    #define LoginLeftMargin (LoginRightMargin+LoginLeftMarginCompensate) // 左边距需要多增加一些距离补偿
    #define LoginLogoWidth 300 // logo的宽度
    #define LoginLogoHeight 80 // logo的高度
    #define LoginDateTimeWidth 400 // 时间控件的宽度
    #define LoginDateTimeHeight LoginLogoHeight // 和logo高度一致

    #define TableWidgetItemWidth 100 // 表格项的宽度
    #define TableWidgetItemHeight 100 // 表格项的高度
    #define TableWidgetItemMinWidth 20 // 默认15改为20
    #define TableNx2WidgetItemNameWidth 100
    #define TableNx2WidgetItemDescriptionWidth (TableNx2WidgetItemNameWidth*8)
    #define TableNx2WidgetItemHeight 30

    #define MainToolButtonMinWidth 250 // 当前,查询和新建实验3个按钮降低默认最小宽度

    #define RunRightPanelMinWidth 400 // 当前实验显示信息面板的最小宽度
    #define RunRightPanelFontSize 25 // 信息面板的字体

    #define QueryTopPanelMaxHeight 250 // 防止查询实验的查询面板向下挤压Table的空间
    #define QueryRightPanelMinWidth 450 // 查询实验的右侧显示面板最小宽度
    #define SummaryPanelComponentMinWidth 200 // 查询实验的label和pushbutton默认宽度300变为200
    #define SummaryPanelTitlePointSize 40 // 查询实验"总结"字体大小
    #define SummaryPanelTitleMinHeight 200 // "总结"的最小高度
    #define SummaryPanelTitleLabelGapHeight 150 // "总结"和第一个"label"之间的距离 不要太多否则会导致title被挤压
    #define SummaryPanelLabelGap 50 // "label"之间的距离
    #define AnalyzePanelPushButtonSpacing 30 // "分析","重新分析","应用全部"按钮之间的距离
    #define AnalyzePanelPushButtonMaxHeight 200 // 防止3个按钮合起来挤压左边的表格

    #define NewExperPushButtonMinWidth 350 // 新建实验的按钮最小宽度
    #define NewExperButtonMinHeight 100 // 新建实验的按钮最小高度
    #define PreviewPicFixedSize (QSize(700,600)) // 预览图片的固定尺寸

    #define TableViewRowHeight 400
    #define TableViewColumnWidth 400

    // 单行控件的最小最大尺寸: spinbox,pushbutton,label,combobox,lineedit
    #define ComponentMinWidth 300
    #define ComponentMaxWidth 600
    #define ComponentMinHeight 30
    #define ComponentMaxHeight 50

    // progress稍有变化
    #define ProgressBarMinWidth 400
    #define ProgressBarMaxWidth 800
    #define ProgressBarMinHeight 30
    #define ProgressBarMaxHeight 50

// 1080尺寸 1920/2560=0.75 1080/1600=0.675
#elif SCREEN_1920X1080
    #define DefaultFontSize 12 // 默认字体大小12号字
    #define WindowWidth 1400 // 1800*0.75=1350
    #define WindowHeight 1000*0.675
    // 登录窗口设置
    // 水平距离 500+500+100
    #define LoginButtonHeight 200*0.5 // button的高度也是整体行布局的高度 用0.5再小一些
    #define LoginButtonWidth 420 // button的宽度-和groubox一致比较好看
    #define LoginGap1 200*0.75 // button和groupbox的距离
    #define LoginGroupboxWidth 420 // groupbox 因为单行控件最小默认修改为200,宽度要调整>400
    #define LoginGroupboxHeight LoginButtonHeight // groupbox-button高度一致
    #define LoginGap2 16*0.75 // icon和groupbox的距离
    #define LoginIconSize 24 // icon的size
    #define LoginLeftMarginCompensate 150*0.4 // 左边距补偿 少一些不用0.75
    #define LoginRightMargin ((WindowWidth-LoginButtonWidth-LoginGap1-\
                                                LoginGroupboxWidth-LoginGap2-LoginIconSize)/2*0.75) // 计算出应有的左右边距
    #define LoginLeftMargin (LoginRightMargin+LoginLeftMarginCompensate) // 左边距需要多增加一些距离补偿
    #define LoginLogoWidth 300*0.75 // logo的宽度
    #define LoginLogoHeight 80*0.675 // logo的高度
    #define LoginDateTimeWidth 400*0.75 // 时间控件的宽度
    #define LoginDateTimeHeight LoginLogoHeight // 和logo高度一致

    #define TableWidgetItemWidth 100*0.75 // 表格项的宽度
    #define TableWidgetItemHeight 100*0.75 // 表格项的高度 正方形要一致
    #define TableWidgetItemMinWidth 20 // 默认15改为20
    #define TableNx2WidgetItemNameWidth 100
    #define TableNx2WidgetItemDescriptionWidth (TableNx2WidgetItemNameWidth*6) // 描述列不要x8,小一些
    #define TableNx2WidgetItemHeight 30*0.675

    #define MainToolButtonMinWidth 250 // 当前,查询和新建实验3个按钮降低默认最小宽度 这个不变

    #define RunRightPanelMinWidth 200 // 当前实验显示信息面板的最小宽度
    #define RunRightPanelFontSize 20 // 信息面板的字体

    #define QueryTopPanelMaxHeight 250 // 防止查询实验的查询面板向下挤压Table的空间
    #define QueryTopPanelMinHeight 150 // 查询面板不挤压了但是被下边的表格挤压,根据三排至少60高度,加上裕量
    #define QueryRightPanelMinWidth 450*0.5 // 查询实验的右侧显示面板最小宽度

    #define SummaryPanelComponentMinWidth 200*0.75 // 查询实验的label和pushbutton默认宽度300变为200
    #define SummaryPanelTitlePointSize 40*0.675 // 查询实验"总结"字体大小
    #define SummaryPanelTitleMinHeight 200*0.675 // "总结"的最小高度
    #define SummaryPanelTitleLabelGapHeight 150*0.5 // "总结"和第一个"label"之间的距离 不要太多否则会导致title被挤压
    #define SummaryPanelLabelGap 50*0.5 // "label"之间的距离
    #define AnalyzePanelPushButtonSpacing 30*0.75 // "分析","重新分析","应用全部"按钮之间的距离
    #define AnalyzePanelPushButtonMaxHeight 200*0.675 // 防止3个按钮合起来挤压左边的表格

    #define NewExperPushButtonMinWidth 260 // 350*0.75 // 新建实验的按钮最小宽度
    #define NewExperButtonMinHeight 70 // 100*0.675 // 新建实验的按钮最小高度
    #define PreviewPicFixedSize (QSize(700*0.75,700*0.75)) // 预览图片的固定尺寸
    #define PreviewPicFixedSizeV1 (QSize(350,350)) // 细胞增殖-预览界面图片尺寸过大挤压了 "预览"和"运行"按钮小一些
    #define PreviewPicFixedSizeV2 (QSize(450,450)) // 细胞增值-运行界面 图片尺寸用V1有点小

    // 单行控件的最小最大尺寸: spinbox,pushbutton,label,combobox,lineedit
    #define ComponentMinWidth 200
    #define ComponentMaxWidth 400
    #define ComponentMinHeight 20
    #define ComponentMaxHeight 40

    // progress稍有变化
    #define ProgressBarMinWidth 300
    #define ProgressBarMaxWidth 600
    #define ProgressBarMinHeight 20
    #define ProgressBarMaxHeight 40

// 1280/2560=0.5 800/1600=0.5
#else
    #define DefaultFontSize 10 // 默认字体大小10号字
    #define WindowWidth 1000
    #define WindowHeight 600
    // 登录窗口设置
    #define LoginButtonHeight 80 // 200*0.5 // button的高度也是整体行布局的高度 用0.5再小一些
    #define LoginButtonWidth 220 // button的宽度-和groubox一致比较好看
    #define LoginGap1 80// 200*0.5 // button和groupbox的距离
    #define LoginGroupboxWidth 220 // groupbox 因为单行控件最小默认修改为100,宽度要调整>200
    #define LoginGroupboxHeight LoginButtonHeight // groupbox-button高度一致
    #define LoginGap2 16*0.5 // icon和groupbox的距离
    #define LoginIconSize 16 // icon的size
    #define LoginLeftMarginCompensate 150*0.3 // 左边距补偿 少一些不用0.75
    #define LoginRightMargin ((WindowWidth-LoginButtonWidth-LoginGap1-\
                                                LoginGroupboxWidth-LoginGap2-LoginIconSize)/2*0.5) // 计算出应有的左右边距
    #define LoginLeftMargin (LoginRightMargin+LoginLeftMarginCompensate) // 左边距需要多增加一些距离补偿
    #define LoginLogoWidth 300*0.5 // logo的宽度
    #define LoginLogoHeight 80*0.5 // logo的高度
    #define LoginDateTimeWidth 400*0.5 // 时间控件的宽度
    #define LoginDateTimeHeight LoginLogoHeight // 和logo高度一致

    #define TableWidgetItemWidth 100*0.5 // 表格项的宽度
    #define TableWidgetItemHeight 100*0.5 // 表格项的高度 正方形要一致
    #define TableWidgetItemMinWidth 20 // 默认15改为20
    #define TableNx2WidgetItemNameWidth 60
    #define TableNx2WidgetItemDescriptionWidth (TableNx2WidgetItemNameWidth*6) // 描述列不要x8,小一些
    #define TableNx2WidgetItemHeight 30*0.5

    #define MainToolButtonMinWidth 250 // 当前,查询和新建实验3个按钮降低默认最小宽度 这个不变

    #define RunRightPanelMinWidth 200 // 当前实验显示信息面板的最小宽度
    #define RunRightPanelFontSize 16 // 信息面板的字体 再缩放一些

    #define QueryTopPanelMaxHeight 250 // 防止查询实验的查询面板向下挤压Table的空间
    #define QueryTopPanelMinHeight 150 // 查询面板不挤压了但是被下边的表格挤压,根据三排至少60高度,加上裕量
    #define QueryRightPanelMinWidth 450*0.5 // 查询实验的右侧显示面板最小宽度

    #define SummaryPanelComponentMinWidth 70// 200*0.5 // 查询实验的label和pushbutton默认宽度300变为70
    #define SummaryPanelTitlePointSize 40*0.5 // 查询实验"总结"字体大小
    #define SummaryPanelTitleMinHeight 200*0.5 // "总结"的最小高度
    #define SummaryPanelTitleLabelGapHeight 150*0.5 // "总结"和第一个"label"之间的距离 不要太多否则会导致title被挤压
    #define SummaryPanelLabelGap 50*0.5 // "label"之间的距离
    #define AnalyzePanelPushButtonSpacing 30*0.5 // "分析","重新分析","应用全部"按钮之间的距离
    #define AnalyzePanelPushButtonMaxHeight 200*0.5 // 防止3个按钮合起来挤压左边的表格

    #define NewExperPushButtonMinWidth 175 // 350*0.5 // 新建实验的按钮最小宽度
    #define NewExperButtonMinHeight 50 // 100*0.5 // 新建实验的按钮最小高度
    #define PreviewPicFixedSize (QSize(700*0.5,700*0.5)) // 预览图片的固定尺寸
    #define PreviewPicFixedSizeV1 (QSize(300,300)) // 细胞增殖-预览界面图片尺寸过大挤压了 "预览"和"运行"按钮小一些
    #define PreviewPicFixedSizeV2 (QSize(450,450)) // 细胞增值-运行界面 图片尺寸用V1有点小

    // 单行控件的最小最大尺寸: spinbox,pushbutton,label,combobox,lineedit
    #define ComponentMinWidth 80
    #define ComponentMaxWidth 200
    #define ComponentMinHeight 25
    #define ComponentMaxHeight 50

    // progress稍有变化
    #define ProgressBarMinWidth 200
    #define ProgressBarMaxWidth 400
    #define ProgressBarMinHeight 25
    #define ProgressBarMaxHeight 50

#endif // 结束尺寸条件

#define INIT_FONT (setFont(QFont("Times New Roman",DefaultFontSize)))
#define INIT_WINDOW_MINSIZE (INIT_MINSIZE(WindowWidth,WindowHeight))
#define INIT_COMPONENT_MINSIZE (INIT_MINSIZE(ComponentMinWidth,ComponentMinHeight))
#define INIT_COMPONENT_MAXSIZE (INIT_MAXSIZE(ComponentMaxWidth,ComponentMaxHeight))
#define INIT_PROGRESSBAR_MINSIZE (INIT_MINSIZE(ProgressBarMinWidth,ProgressBarMinHeight))
#define INIT_PROGRESSBAR_MAXSIZE (INIT_MAXSIZE(ProgressBarMaxWidth,ProgressBarMaxHeight))
#define INIT_BUTTON_MINSIZE (INIT_MINSIZE(LoginButtonWidth,LoginButtonHeight)) // 登录窗口的按钮尺寸
#define INIT_VERIFYDB_MINSIZE (INIT_MINSIZE((ComponentMinWidth*2+50),\
                                            (ComponentMinHeight*5+100))) // 验证数据库对话框的宽度和高度
#define INIT_MODIFYPWD_MINSIZE (INIT_MINSIZE((ComponentMinWidth*2+100),\
                                            (ComponentMinHeight*4+50))) // 修改密码对话框的宽度和高度
#endif // CONSTANT_H

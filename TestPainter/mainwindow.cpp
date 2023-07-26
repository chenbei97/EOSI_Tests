#include "mainwindow.h"
#include <QDebug>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    resize(mw,mh);
}

MainWindow::~MainWindow()
{
}


void MainWindow::paintEvent(QPaintEvent *e)
{

    static const double rato = 3.1415926535 / 180.0;

    static const QImage image(":/img.jpg");

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect(0,0,mw,mh);

    auto brush = painter.brush();
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    painter.setBrush(brush);

    auto pen = painter.pen();
    pen.setWidth(2);
    pen.setColor(Qt::green);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

#define Log(s) (qDebug()<<QString("%1 = ").arg(s))

// #define StylePainter 0
// #define FillPath 0
// #define FillRect 0

//#define DrawPath 0
// #define DrawRects 0

// #define DrawLine 0
// #define DrawImage 0

// #define DrawEllipse 0
// #define DrawPoints

// #define DrawPolyLine 0
// #define DrawPolygon 0
// #define DrawConvexPolygon 0

// #define DrawArc 0
// #define DrawChord 0
// #define DrawPie 0

 #define  DrawText 0
// #define SetViewPort 0
// #define SetWindow 0
// #define SetWindowAndViewPort 0

//#define SetWindowBeforeViewPort 0
// #define SetViewPortBeforeWindow 0
//#define  DrawPathBeforeSet 0
// #define  DrawPathAfterSet 0

//#define ReadProperties 0

#ifdef ReadProperties
    qDebug()<<"background() = "<<painter.background(); // 背景画刷
    qDebug()<<"backgroundMode() = "<<painter.backgroundMode(); // 背景模式,Opaque,Transparent
    Log("brushOrigin()")<<painter.brushOrigin(); // 当前画刷起点
    Log("clipBoundingRect()")<<painter.clipBoundingRect(); // 如果存在剪辑返回逻辑坐标表示的区域否则空矩形
    Log("clipPath()")<<painter.clipPath();// 返回逻辑坐标中的当前剪辑路径
    Log("compositionMode()")<<painter.compositionMode(); // 合成模式
    Log("opacity()")<<painter.opacity(); // 透明度
    Log("window()")<<painter.window(); // 默认window和viewport都一样
    Log("viewport()")<<painter.viewport();// QRect(0,0 800x800)
    Log("hasClipping()")<<painter.hasClipping();// false
    Log("clipPath()")<<painter.clipPath();// QPainterPath: Element count=0
    Log("clipRegion()")<<painter.clipRegion();// QRegion(null)
    Log("clipBoundingRect()")<<painter.clipBoundingRect();// QRectF(0,0 0x0)
    Log("layoutDirection()")<<painter.layoutDirection(); // Qt::LeftToRight
    Log("renderHints()")<<painter.renderHints();// QFlags<QPainter::RenderHint>(Antialiasing|TextAntialiasing)
    Log("transform()")<<painter.transform(); // QTransform(type=TxNone, 11=1 12=0 13=0 21=0 22=1 23=0 31=0 32=0 33=1)
    Log("viewTransformEnabled()")<<painter.viewTransformEnabled(); // false
    Log("worldMatrixEnabled()")<<painter.worldMatrixEnabled(); // false
    Log("worldTransform()")<<painter.worldTransform();//QTransform(type=TxNone, 11=1 12=0 13=0 21=0 22=1 23=0 31=0 32=0 33=1)
    Log("end()")<<painter.end(); // 结束绘画 true
    Log("isActive()")<<painter.isActive(); // false, 如果已调用begin而未调用end返回true否则返回false
#elif defined (StylePainter)

    QStyleOptionFocusRect option;
    option.initFrom(new QComboBox);
    option.backgroundColor = palette().color(QPalette::Background);
#ifdef UseStyleOption
    style()->drawPrimitive(QStyle::PE_FrameFocusRect, &option, &painter, this);
#else
    QStylePainter stylepainter(this);//使用小部件的样式绘制由QStyleOption选项指定的基本元素
    stylepainter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
#endif

#elif defined(FillPath)
    QPainterPath p;
    p.arcTo(QRect(200,200,400,400),0,360); // 画一个中心圆
    // 以百分比t返回路径切线的角度。参数t必须介于0和1之间。
    //角度的正值表示逆时针方向，负值表示顺时针方向。零度位于3点钟位置
    qDebug()<<"QPainterPath.angleAtPercent(0) = "<<p.angleAtPercent(0); // 326.31°
    qDebug()<<"QPainterPath.angleAtPercent(0.5) = "<<p.angleAtPercent(0.5); // 166.38°
    qDebug()<<"QPainterPath.angleAtPercent(1.0) = "<<p.angleAtPercent(1.0); // 90°
    qDebug()<<"QPainterPath.slopeAtPercent(0) = "<<p.slopeAtPercent(0); //0.666667
    qDebug()<<"QPainterPath.slopeAtPercent(1.0) = "<<p.slopeAtPercent(1.0); //-inf
    qDebug()<<"QPainterPath.pointAtPercent(0) = "<<p.pointAtPercent(0); // QPointF(0,0)
    qDebug()<<"QPainterPath.pointAtPercent(1.0) = "<<p.pointAtPercent(1.0); // QPointF(600,400)
    qDebug()<<"QPainterPath.boundingRect() = "<<p.boundingRect(); // QRectF(0,0 600x600) 将此绘制器路径的边界矩形返回为具有浮点精度的矩形
    qDebug()<<"QPainterPath.capacity() = "<<p.capacity(); // 16 返回QPainterPath分配的元素数
    qDebug()<<"QPainterPath.currentPosition() = "<<p.currentPosition(); //QPointF(600,400) 在 起点处
    qDebug()<<"QPainterPath.elementCount() = "<<p.elementCount(); // 14个 返回绘制器路径中的路径元素数
    qDebug()<<"QPainterPath.elementAt(0) = "<<p.elementAt(0); // QPointF(0,0)
    qDebug()<<"QPainterPath.elementAt(14) = "<<p.elementAt(13); // QPointF(600,400)
    qDebug()<<"QPainterPath.contains(QRectF(300,300,50,50)) = "<<p.contains(QRectF(300,300,50,50)); // true 包含这个小矩形
    qDebug()<<"QPainterPath.intersects(QRectF(200,200,50,50)) = "<<p.intersects(QRectF(200,200,50,50)); // 和这个矩形没交集
    qDebug()<<"QPainterPath.length() = "<<p.length(); // 1978.05
    qDebug()<<"QPainterPath.elementAt(0) = "<<p.elementAt(0); // QPointF(0,0)
    //QPainterPath p1; p1.moveTo(600,200); p1.lineTo(800,800); p1.closeSubpath();
    //qDebug()<<"QPainterPath.intersected(p) = "<<p.intersected(p); // 会返回和指定路径交集的点
    p.closeSubpath();
    painter.setBrush(QBrush(Qt::red,Qt::Dense1Pattern));
    painter.fillPath(p,painter.brush());

    static const double deg = 72.0*3.1415926535/180.0;
    auto r = 200;
    QVector<QPointF> points;
    painter.setPen(QPen(Qt::green,30));
    painter.setFont(QFont("Times New Roman",30));
    for (int i = 0 ;i < 6; ++i){
        auto point = QPointF(300+r * cos(deg*i),300+r * sin(i*deg));
        qDebug()<<"point = "<<point;
        painter.drawPoint(point);
        if (i != 5)
            painter.drawText(point,QString::number(i+1));
        points.append(point);
    }
    QPainterPath p1;
    p1.moveTo(300+r,300);
    for(int i = 0; i < 6; ++i)
        p1.lineTo(points[i]);
    painter.setPen(QPen(Qt::blue,1));
    painter.drawPath(p1);

    painter.save();
    painter.translate(200,30);// 坐标进行了平移
    painter.drawText(0,30,"123455"); // 把文字基于200,30的位置向下移动30
    painter.restore();
    painter.translate(200,200); // 平移200
    painter.drawText(100,100,"782485"); // 基于200,200的位置继续平移100
#elif defined (FillRect)
    painter.fillRect(QRectF(200,200,400,400),Qt::yellow);
    painter.eraseRect(300,300,200,200);

    painter.setClipping(true); // 这3个好像没什么作用
    painter.setClipRect(QRectF(0,0,800,800));
    painter.setClipRegion(QRegion(QRect(100,100,50,50)));

#elif defined (SetWindowAndViewPort)
    painter.setBrush(Qt::white);
    //auto r1 = QRect(0,0,600,600);
    auto r1 = QRect(200,200,600,600); // 规定了起点坐标(200,200) ,600长度的正方形
    auto r2 = QRect(-100,-100,200,200); // 窗口基于这个起点生成1个200的正方形
    auto r3 = QRect(0,0,100,100); // 矩形基于窗口坐标去绘制,那就是在窗口的中心位置继续绘制小矩形

#ifdef SetWindowBeforeViewPort
    painter.setWindow(r2); // 先设置哪个没有区别,展示的效果没有影响
    painter.setViewport(r1);
#else
    painter.setViewport(r1);
    painter.setWindow(r2);
#endif
    painter.setPen(QPen(Qt::red,3));
    painter.drawRect(r2);
    painter.setPen(QPen(Qt::black,1));
    painter.drawRect(r3);

#elif defined (SetViewPort)
    // 单独设置viewport有以下几条规律
    // 1. 如果没设置过viewport, widget,window和viewport的size都会同步1:1变化; 如果设置过viewport,就会固定下来
    // 2. 设置过viewport然后绘制的矩形会随着resize缩放,size变大相反矩形变小,size缩小矩形则变大
    // 3. viewport是一个独立系统方便绘制,绘制完后会自动等比例相反的缩放至widget的大小
    // 4. 可以通过总是取值widget宽高较小的那个来保证不变形
    // 5. 设置的viewport起点会变化,所有绘制的矩形都会基于新的起点去绘制
     painter.setBrush(Qt::white);

#ifdef DrawPathBeforeSet
     // 没设置viewport使用的是widget物理坐标,path位置根本不随widget改变
     QPainterPath path;
     path.moveTo(400,0);
     path.lineTo(800,300);
     path.arcTo(QRectF(0,0,800,600),0,-90); // 这里不用x16,用的就是角度, 默认水平3点钟方向,矩形区域是整体,顺时针绘制一段90°圆弧
     // 最快的理解方法: 把圆弧补齐成圆就知道这个矩形,起始角度和绘制角度多少合适的
     path.arcTo(QRectF(-400,300,800,600),0,90); //是一个只有右上角1/4的部分在可见区域矩形
     path.quadTo(0,0,400,0);
     path.closeSubpath(); // 回到最初的起点400,0
     painter.drawPath(path);
#endif

 #ifdef   SetViewPortTest1
    int side = qMin(width(), height());
    int x = (width() - side )/ 2;
    int y = (height() - side ) / 2;
    painter.setPen(Qt::blue);
    painter.setViewport(x, y, side, side);
    //painter.setViewport(0,0,1600,1600);
    //painter.setViewport(0,0,600,600);
    painter.drawRect(x, y, side, side);
 #else
    //auto r1 = QRect(0,0,600,600);
    auto r1 = QRect(300,300,600,600);
    auto r2 = QRect(0,0,300,300);
    auto r3 = QRect(0,0,100,100);
    //auto r2 = QRect(0,0,400,400); // 视口和窗口正好左上角重合
    //auto r2 = QRect(0,0,1300,1300); // 视口很大,矩形看起来很大无法显示完全
    //auto r2 = r1; // 视口的起点在左上角外部
    painter.setViewport(r1);

    painter.setPen(QPen(Qt::red,3));
    painter.drawRect(r1);
    painter.setPen(QPen(Qt::blue,3));
    painter.drawRect(r2);
    painter.setPen(QPen(Qt::black,1));
    painter.drawRect(r3);
#endif
#ifdef DrawPathAfterSet
    // 设置viewport后,使用的是viewport物理坐标,path位置会随着widget改变,同时起点也会变化
    QPainterPath path;
    path.moveTo(400,0);
    path.lineTo(800,300);
    path.arcTo(QRectF(0,0,800,600),0,-90); // 这里不用x16,用的就是角度, 默认水平3点钟方向,矩形区域是整体,顺时针绘制一段90°圆弧
    // 最快的理解方法: 把圆弧补齐成圆就知道这个矩形,起始角度和绘制角度多少合适的
    path.arcTo(QRectF(-400,300,800,600),0,90); //是一个只有右上角1/4的部分在可见区域矩形
    path.quadTo(0,0,400,0);
    path.closeSubpath(); // 回到最初的起点400,0
    painter.drawPath(path);
#endif

    qDebug()<<"width = "<<width()<<" height = "<<height();
    qDebug()<<"window width = "<<painter.window().width()<<" window height = "<<painter.window().height();
    qDebug()<<"viewport width = "<<painter.viewport().width()<<" viewport height = "<<painter.viewport().height();

//    QRegion r1(QRect(0, 0, 200, 80), QRegion::Ellipse);// r1: elliptic region
//    QRegion r2(QRect(0, 0, 90, 30));    // r2: rectangular region
//    QRegion r3 = r1.intersected(r2);        // r3: intersection
//    painter.setBrush(Qt::yellow);
//    painter.setClipRegion(r3);

#elif defined (SetWindow)
        // 单独设置window有以下几条规律
        // 1. 如果没设置过window, widget,window和viewport的size都会同步1:1变化; 如果设置过window,就会固定下来
        // 2. 设置过window,然后绘制的矩形会随着resize缩放,size变大矩形也变大,size缩小矩形也变小
        // 3. window是一个独立系统方便绘制,绘制完后会自动等比例缩放至widget的大小
        // 4. 矩形都是依据(0,0)绘制的,如果(0,0)位置不放在窗口中间位置,也就是左上角不是(-200,-200)这样
        // 其实就是相当于设备坐标了,逻辑坐标就失去意义,所以设置window左上角坐标都设为负的
        painter.beginNativePainting();
        painter.setBrush(Qt::white);

#ifdef DrawPathBeforeSet
        // 如果setWindow之前设置,使用的还是widget物理坐标系
        QPainterPath path;
        path.moveTo(400,0);
        path.lineTo(800,300);
        path.arcTo(QRectF(0,0,800,600),0,-90); // 这里不用x16,用的就是角度, 默认水平3点钟方向,矩形区域是整体,顺时针绘制一段90°圆弧
        // 最快的理解方法: 把圆弧补齐成圆就知道这个矩形,起始角度和绘制角度多少合适的
        path.arcTo(QRectF(-400,300,800,600),0,90); //是一个只有右上角1/4的部分在可见区域矩形
        path.quadTo(0,0,400,0);
        path.closeSubpath(); // 回到最初的起点400,0
        //path.lineTo(800,600);
        painter.drawPath(path);
#endif
 #ifdef   SetViewPortTest1
        // path先设置好，再setWindow，这样会自动缩放到window的尺寸
        painter.setWindow(QRect(-1800,-1800,3600,3600));
        //painter.setWindow(QRect(-300,-300,600,600));
        //painter.setWindow(QRect(-200,-200,400,400)); // setWindow规定了一个窗口,是逻辑坐标系统
        painter.drawRect(QRect(-50,-50,100,100)); // 绘制的时候以逻辑坐标参照,限于drawxx系列函数 //然后会自动映射到viewport等比例放大
#else
        auto r1 = QRect(0,0,600,600); // 坐标中心位置变成(300,300),矩形会依据(0,0)去绘制,结果都基于左上角绘制的
        //auto r1 = QRect(-300,-300,600,600); // (0,0)变成坐标中心,那么后边2个矩形是基于中心位置绘制,窗口上就是中间位置右下角
        auto r2 = QRect(0,0,300,300);
        auto r3 = QRect(0,0,100,100);
        //auto r2 = QRect(0,0,400,400); // 视口和窗口正好左上角重合
        //auto r2 = QRect(0,0,1300,1300); // 视口很大,矩形看起来很大无法显示完全
        //auto r2 = r1; // 视口的起点在左上角外部
        painter.setWindow(r1);

        painter.setPen(QPen(Qt::red,3));
        painter.drawRect(r1);
        painter.setPen(QPen(Qt::blue,3));
        painter.drawRect(r2);
        painter.setPen(QPen(Qt::black,1));
        painter.drawRect(r3);
#endif
#ifdef DrawPathAfterSet
        // 如果setWindow之后设置,使用的是window逻辑坐标系
        QPainterPath path;
        path.moveTo(400,0);
        path.lineTo(800,300);
        path.arcTo(QRectF(0,0,800,600),0,-90); // 这里不用x16,用的就是角度, 默认水平3点钟方向,矩形区域是整体,顺时针绘制一段90°圆弧
        // 最快的理解方法: 把圆弧补齐成圆就知道这个矩形,起始角度和绘制角度多少合适的
        path.arcTo(QRectF(-400,300,800,600),0,90); //是一个只有右上角1/4的部分在可见区域矩形
        path.quadTo(0,0,400,0);
        path.closeSubpath(); // 回到最初的起点400,0
        //path.lineTo(800,600);
        painter.drawPath(path);
#endif
        qDebug()<<"width = "<<width()<<" height = "<<height();
        qDebug()<<"window width = "<<painter.window().width()<<" window height = "<<painter.window().height();
        qDebug()<<"viewport width = "<<painter.viewport().width()<<" viewport height = "<<painter.viewport().height();

        painter.endNativePainting();// 在手动发出本机绘制命令后恢复绘制者。在调用任何其他painter命令之前，允许painter恢复其所依赖的任何原生状态
#elif defined (DrawPath)
    // 路径: 添加封闭图形,ellipse,path,rect,region,text,connectPath
    // 非封闭: lineTo, cubicTo, moveTo, addPloygon
    // moveTo隐式的关闭路径,开始新的子路径; closeSubpath关闭子路径,当前路径位置currentPosition移动到之前的起点
    QPainterPath path;
    path.addRect(mw/4, mh/4, mw/2, mh/2);

    // 贝塞尔曲线3个点控制 C = (1-t)A+ tB
    path.moveTo(0, 0);
    path.cubicTo(mw, 0,  mw/2, mh/2,  mw, mh); // A点是TopRight,B点是CenterC点是BottomRight
    path.cubicTo(0, mh,  mw/4, 3*mh/4,  0, 0); // 注意,现在起点位置是BottomRight, A点是BottomLeft,B点是靠近A的左下侧,终点是(0,0)

    painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,Qt::FlatCap, Qt::MiterJoin));//墨绿
    painter.setBrush(QColor(122, 163, 39)); // 鲜绿

    path.setFillRule(Qt::WindingFill); // 全填充
    painter.drawPath(path);

#elif defined (DrawRects)
    QVector<QRectF> rectangles;
    auto rect_w = 300, rect_h = 200;
    for(int i = 0; i < 5; ++i){
        rectangles.append(QRectF((mw-rect_w)/2-100 + i * 50,(mh-rect_h)/2,rect_w,rect_h));
    }
    painter.drawRects(rectangles);
    QRectF rectangle((mw-rect_h)/2,(mh-rect_h)/2+200,rect_h,rect_h);

    painter.setPen(Qt::red);
    auto radius = 100;
    painter.drawRoundedRect(rectangle, radius, radius,  Qt::RelativeSize); // 这里会变成1个圆
#elif defined (DrawLine)
    // (const QLineF *lines, int lineCount)
    // const QVector<QLineF> &lines QLineF的指针或者向量
    // (const QPointF *pointPairs, int lineCount) QPointF的指针或向量
    // (const QVector<QPointF> &pointPairs)
    auto cx = mw/2.0; auto cy = mh/2.0; double r = 200.0;
#ifdef DrawLineByLineF
    QVector<QLineF> lines;
#else
    QVector<QPointF> points;
#endif
    for (int i = 0; i < 12; ++i)
    {
        auto p1 = QPointF(cx+r*cos((30*i)*rato),cy-r*sin((30*i)*rato));
        auto p2 = QPointF(cx+r*cos((30*(i+1))*rato),cy-r*sin((30*(i+1))*rato));
#ifdef DrawLineByLineF
        lines.append(QLineF(p1,p2));
#else
        points.append(p1);
        points.append(p2);
#endif
    }
#ifdef DrawLineByLineF
    painter.drawLines(lines);
#else
    painter.drawLines(points);
#endif



#elif defined (DrawImage)
    // 将给定图像的矩形部分源绘制到绘制设备中的目标矩形中
#ifdef DrawImage1
    auto imw=200.0, imh = 150.0;
    QRectF source(45.0, 30.0, imw, imh); // 把图像像素起点(45.0,30.0)的矩形这块区域取出来绘制
    QRectF target((mw-imw)/2, (mh-imh)/2, imw, imh);  // 绘制的位置居中
    painter.drawImage(target, image, source);
#elif defined (DrawImage2)
    auto imw=200.0, imh = 150.0;
    QPointF center((mw-imw)/2, (mh-imh)/2);
    painter.drawImage(center, image, source); // 直接指定绘制的原点更方便,大小自动就是source一样的大小
#elif defined (DrawImage3)
    // 图像的size是 (474,323)
    QRectF target((mw-image.width())/2, (mh-image.height())/2, image.width(), image.height());
    painter.drawImage(target, image); // 不选择一部分,是全部图像
#elif defined (DrawImage4)
    QPointF center((mw-image.width())/2, (mh-image.height())/2);
    painter.drawImage(center, image); // 不选择一部分,是全部图像,但是不指定矩形，给定中心位置
#else
    // 在给定的矩形内绘制平铺的像素图，其原点位于给定的位置 ,这个原点一般指定矩形的中心
    painter.drawTiledPixmap(QRectF(0,0,600,600),QPixmap::fromImage(image),QPointF(200,100));
#endif



#elif defined (DrawPoints)
     auto cx = mw/2.0; auto cy = mh/2.0; double r = 200.0;
#ifdef DrawEllipse
     painter.setPen(QPen(Qt::red,2));
     painter.setBrush(QBrush(Qt::white));
     //painter.drawEllipse(QRect(200,200,r*2,r*2));
     painter.drawEllipse(QPointF(cx,cy),r,r);
#endif
    auto p1 = QPointF(cx+r,cy); // 正x轴 第1个点 (700,300) 逆时针开始
    auto p2 = QPointF(cx+r*cos(30*rato),cy-r*sin(30*rato)); // 第1象限30和60的2个点
    auto p3 = QPointF(cx+r*cos(60*rato),cy-r*sin(60*rato));
    auto p4 = QPointF(cx,cy-r); // 正y轴
    auto p5 = QPointF(cx+r*cos(120*rato),cy-r*sin(120*rato)); // 第2象限, -cos(60) , -sin(60)
    auto p6 = QPointF(cx+r*cos(150*rato),cy-r*sin(150*rato));  // -cos(30) , -sin(30)
    auto p7 = QPointF(cx-r,cy); // 负x轴
    auto p8 = QPointF(cx+r*cos(210*rato),cy-r*sin(210*rato)); // 第3象限, -cos(30) , +sin(30)
    auto p9 = QPointF(cx+r*cos(240*rato),cy-r*sin(240*rato));  // -cos(60), +sin(60)
    auto p10 = QPointF(cx,cy+r); // 负y轴 +cos(90), +sin(90)
    auto p11 = QPointF(cx+r*cos(300*rato),cy-r*sin(300*rato));  // 第4象限 +cos(60) ,-sin(-60)= +sin(60)
    auto p12 = QPointF(cx+r*cos(330*rato),cy-r*sin(330*rato)); // +cos(30) +sin(30)
    static const QPointF points[] = { // 要声明为静态的不占资源
       p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12
    };
    pen = painter.pen();
    pen.setWidth(20);
    pen.setColor(Qt::blue);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawPoints(points, 12);



#elif defined (DrawConvexPolygon) || defined(DrawPolygon) || defined(DrawPolyLine)
    // 绘制凸多边形，在x11会比drawPolygon更快，必须是凸的 , 第一个点和最后一个点会隐式连接
    auto cx = mw/2; auto cy = mh/2; int r = 300; // 定义坐标中心和半径
//    static const QPointF points[5] {
//        QPointF(cx+r,cy),
//        QPointF(cx+0,cy-r),
//        QPointF(cx-r,cy),
//        QPointF(cx+0,cy+r), // 绘制的菱形
//        QPointF(cx+r,cy),
//    };
    auto p1 = QPointF(cx+r,cy); // 正x轴 第1个点 (700,300) 逆时针开始
    auto p2 = QPointF(cx+r*cos(30*rato),cy-r*sin(30*rato)); // 第1象限30和60的2个点
    auto p3 = QPointF(cx+r*cos(60*rato),cy-r*sin(60*rato));
    auto p4 = QPointF(cx,cy-r); // 正y轴
    auto p5 = QPointF(cx+r*cos(120*rato),cy-r*sin(120*rato)); // 第2象限, -cos(60) , -sin(60)
    auto p6 = QPointF(cx+r*cos(150*rato),cy-r*sin(150*rato));  // -cos(30) , -sin(30)
    auto p7 = QPointF(cx-r,cy); // 负x轴
    auto p8 = QPointF(cx+r*cos(210*rato),cy-r*sin(210*rato)); // 第3象限, -cos(30) , +sin(30)
    auto p9 = QPointF(cx+r*cos(240*rato),cy-r*sin(240*rato));  // -cos(60), +sin(60)
    auto p10 = QPointF(cx,cy+r); // 负y轴 +cos(90), +sin(90)
    auto p11 = QPointF(cx+r*cos(300*rato),cy-r*sin(300*rato));  // 第4象限 +cos(60) ,-sin(-60)= +sin(60)
    auto p12 = QPointF(cx+r*cos(330*rato),cy-r*sin(330*rato)); // +cos(30) +sin(30)
    static const QPointF points[] = { // 要声明为静态的不占资源
       p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12
    };
#ifdef DrawConvexPolygon
    painter.drawConvexPolygon(points, 12);
#elif defined(DrawPolygon)
    painter.drawPolygon(points, 5); // 绘制多边形 效果一样
#else
    painter.drawPolyline(points, 5); // 绘制线,但是不会连接到一起 如果指定起始和终止点相同会连到一起
#endif


#elif defined (DrawChord)
    // 绘制给定矩形,起始角度和延展角度的圆弦,闭合内部的填充风格就是brush()
    int startangle = 90 * 16; // 起始角度
    int spanagnle = 180 * 16 ; // 延展180度,应该是个闭合左半圆
    auto r = QRect((mw-400)/2,(mh-300)/2,400,300);
    painter.drawcyord(r,startangle,spanagnle);

#elif defined (DrawPie)
    // 画饼
    int startangle = 90 * 16; // 起始角度
    int spanagnle = 180 * 16 ; // 延展180度,应该是个闭合左半圆
    auto r = QRect((mw-400)/2,(mh-300)/2,400,300);
    painter.drawPie(r,startangle,spanagnle);

#elif  defined(DrawArc)
    // 绘制给定矩形,起始角度和延展角度的圆弧
    // 起始和延展角度必须指定为1/16度,即一个完整的圆等于5760（16*360）
    // 正角度逆时针,负值顺时针,零度位于3点钟位置
    int startangle = 90 * 16; // 起始角度
    int spanagnle = 180 * 16 ; // 延展180度,应该是个开放左半圆
    auto r = QRect((mw-400)/2,(mh-400)/2,400,400);
    painter.drawArc(r,startangle,spanagnle);
    //painter.drawArc(rect,startangle,spanagnle);



#elif defined(DrawText)
    auto font = painter.font();
    font.setPointSize(50);
    font.setFamily("Times New Roman");
    painter.setFont(font);

    QRect boundingRect;
    painter.drawText(rect, Qt::AlignCenter, QString::fromLocal8Bit("陈北"),&boundingRect);
    qDebug()<<"drawText() boundingRect = "<<boundingRect;

    /*QStaticText比drawText更有效,后者每次调用都会重新计算布局信息
    *如果每次迭代都更改文本或其布局，drawText()是更有效的替代方案，因为必须重新计算静态文本的布局以考虑新状态*/
    painter.drawStaticText(50,50,QStaticText(QString::fromLocal8Bit("帅哥")));

#endif

    e->accept();
}


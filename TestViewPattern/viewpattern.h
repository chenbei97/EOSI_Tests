#ifndef EOSI_VIEWPATTERN_H
#define EOSI_VIEWPATTERN_H

#include "qwidget.h"
#include "alias.h"
#include "fields.h"
#include "constant.h"
#include "qaction.h"
#include "qevent.h"
#include "qpainter.h"

typedef QPair<QRectF,bool> QRectFMask;
typedef QVector<QRectFMask> QRectFMaskVector;

#define PointToIDCoefficient 1000 // kx1+y1=kx2+y2=> k=(y2-y1)/(x1-x2),k取什么值?找不到这样的2个坐标能等于k,由于wellsize最大384,实际上k>384就能保证id唯一了

class ViewPattern: public QWidget
{
    Q_OBJECT
public:
    explicit ViewPattern(QWidget*parent= nullptr);
    void setViewInfo(const ViewInfo& info);
    ViewInfo viewInfo() const;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void clearViewWindowCache(const QPoint& holepoint);
    void clearAllViewWindowCache(int viewsize);
    void updateViewWindowCache(QCPoint holepoint,QCPointVector viewpoints,int viewsize);
private:
    int mSize = 0;
    QBool2DVector mViewMask;
    void initViewMask();
    void viewRectsMapToViewMask();
    QRectF mapToSize(const QRectF& source,const QPointF&ref_point,int ref_w,int ref_h);
    QRectF mapFromSize(const QRectF& source,const QPointF&ref_point,int ref_w,int ref_h);
private:
    ViewInfo mViewInfo;
    QPointF mMousePos;
    QRectF mMouseRect;
    QRectF mDrapRectF;
    QMap<int,ViewRectFVector> mViewRects;
    QMap<int,ViewRectFVector> mTmpRects;

private:
    QAction * saveviewact;
    QAction * removeviewact;
    QAction * applyholeact;
    QAction * applygroupact;
    QAction * applyallact;
    void onRemoveViewAct();
    void onSaveViewAct();
    void onApplyHoleAct();
    void onApplyGroupAct();
    void onApplyAllAct();
    int holeID() const;
    bool checkField() const;
private:
    double getCircleRadius() const; // 视野圆半径
    QPointF getInnerRectTopLeftPoint() const; // 外接正方形左上角顶点
    QPointF getInnerRectTopRightPoint() const;// 外接正方形右上角顶点
    QPointF getInnerRectBottomLeftPoint() const;// 外接正方形左下角顶点
    QPointF getInnerRectBottomRightPoint() const;// 外接正方形右下角顶点
    double getInnerRectWidth() const; // 小矩形区域的宽度
    double getInnerRectHeight() const; // 小矩形区域的高度
signals:
//    void mouseClicked(const QPoint& point);
    void previewEvent(const QPointF& point); // 单击非框选时是预览
    void applyHoleEvent(const QVariantMap&m);
    void applyGroupEvent(const QVariantMap&m);
    void applyAllEvent(const QVariantMap&m);
};

#include <QStack>
#include <qmath.h>

static QPointF p0;
static void findLowestPoint(const QPointFVector& points)
{
    if (points.isEmpty());

    p0 = points[0];

    for(int i = 1; i< points.count(); ++i) {
        auto next = points[i];
        if (next.y()<p0.y())
           p0 = next; // 找y值最小的点
        else if (next.y() == p0.y()) {
            if (next.x() < p0.x())
                p0 = next; // 如果y值相同找x值最小的点
        }
    }
}

const double MAXNUM=1e10;
static bool convex_cmp(QPointF& p1,QPointF&p2)
{ // 排序算法
    if (p1.x() == p0.x() && p1.y() == p0.y()) return true; // 前1个点和p0重合为真
    if (p2.x() == p0.x() && p2.y() == p0.y()) return false; // 后1个不为真

    //计算极角（等于0则赋予一个极大值）
    double angle1 = p1.x()==p0.x()? MAXNUM:(p1.y()-p0.y()) / (p1.x()-p0.x());
    double angle2=p2.x()==p0.x()? MAXNUM:(p2.y()-p0.y())/(p2.x()-p0.x());
    //小于0则赋予一个更大的值
    if(angle1<0)angle1+=2*MAXNUM;
    if(angle2<0)angle2+=2*MAXNUM;

    //极角排序
    if(angle1<angle2)return true;

    else if(angle1==angle2)
            return p1.y()>p2.y();
    else return false;
}

static double convex_cross(QPointF& p1, QPointF& p2, QPointF& p3)
{
    return (p2.x()-p1.x())*(p3.y()-p1.y())-(p3.x()-p1.x())*(p2.y()-p1.y());
}

//搜索凸包
static void find_convex_hull(QPointFVector& points,QPointFVector& aggregate)
{
    //p0和p1是凸包中的点
    QStack<QPointF> convex_hull;
    convex_hull.push(points[0]);
    convex_hull.push(points[1]);

    int i=2;
    //p1,p2为栈顶两个节点
    auto p1=points[0];
    auto p2=points[1];
    while(i<points.count()){
        //如果points[i]和points[i-1]在同一个角度，则不再对points[i]进行计算
        if((points[i-1].y()-p0.y())*(points[i].x()-p0.x())
                ==(points[i-1].x()-p0.x())*(points[i].y()-p0.y())){
            i++;
            continue;
        }

        //如果叉积大于0，将当前点压入栈
        if (convex_cross(p1, p2, points[i])>=0){
            //假设现在栈中为a,b,c,d,cross(c,d,e)大于等于0
            convex_hull.push(points[i]);//a,b,c,d,e,p1=c,p2=d
            p1=p2;//p1=d
            p2=convex_hull.top();//p2=e
            i++;
        }

        //如果叉积小于0，对栈中节点进行处理
        else{
            while(1){
                //假设现在栈中为a,b,c,d,cross(c,d,e)小于0
                convex_hull.pop();//a,b,c
                convex_hull.pop();//a,b
                p2=p1;//p2=c;
                p1=convex_hull.top();//p1=b
                convex_hull.push(p2);//a,b,c
                //cross(b,c,e)
                if(convex_cross(p1,p2,points[i])>=0){
                    convex_hull.push(points[i]);//a,b,c,e
                    p1=p2;//p1=c
                    p2=convex_hull.top();//p2=e
                    i++;
                    break;
                }
            }
        }
    }
    aggregate = convex_hull.toList().toVector();
}

#endif //EOSI_VIEWPATTERN_H

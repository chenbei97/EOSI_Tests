/***
 * @Author: chenbei97 chenbei_electric@163.com
 * @Date: 2023-10-25 09:48:48
 * @LastEditors: chenbei97 chenbei_electric@163.com
 * @LastEditTime: 2023-10-25 09:49:29
 * @FilePath: \EOS\interface\src\preview\viewpattern.cpp
 * @Copyright (c) 2023 by ${chenbei}, All Rights Reserved.
 */

#include "viewpattern.h"

void ViewPattern::setViewInfo(const QVariantMap& info)
{
    mViewInfo = info;
    //checkField();

    mMousePos = {-1.0,-1.0};
    mMouseRect = QRectF();
    mDrapRectF = QRectF();

    auto id = holeID();
    mViewRects[id].clear();

    auto size =  mViewInfo[HoleViewSizeField].toInt();

    if(!mTmpRects[id].isEmpty() && size == mSize)
        mViewRects[id] = mTmpRects[id];
    else mTmpRects[id].clear();

    mSize = size;
    initViewMask(); // 先初始mSize再重新初始化mMask

    update();
}

void ViewPattern::clearViewWindowCache(const QPoint &holepoint)
{ // 删孔时清除该孔对应的视野缓存信息
    // 1. 计算这个孔的id
    auto idx = holepoint.x()*PointToIDCoefficient+holepoint.y();// 保证索引唯一不重叠2k+y,每个孔对应唯一的idx

    // 2.此时点击视野坐标会越界所以还是需要重新分配空间
//    QBool2DVector vec;
//    for(int row = 0 ; row < mrows; ++ row) {
//        QBoolVector var;
//        for (int col = 0; col < mcols; ++col){
//            var.append(false);
//        }
//        vec.append(var);
//    }
//    mSelectRects[idx] = vec;
//    mTmpRects[idx] = vec;
    LOG<<"is clear "<<holepoint<<" 's cache";
    update();
}

void ViewPattern::clearAllViewWindowCache(int viewsize)
{ // 切换厂家或者物镜倍数时把所有的信息都要清空,不仅是当前孔,所有的孔信息都要清除

    update();
}

void ViewPattern::updateViewWindowCache(QCPoint holepoint, QCPointVector viewpoints,int viewsize)
{ // 导入实验配置时去更新view的ui信息

    update();
}

void ViewPattern::onSaveViewAct()
{
    auto id = holeID();
    ViewRectF info;
    info.flag = true;// 表示是保存还是删除这个区域

    // 框选的时候保存框选的矩形,不保存单击生成的矩形
    if (!mDrapRectF.isEmpty()) {

        info.rect = mDrapRectF;
        mViewRects[id].append(info);
    } else {
        info.rect = mMouseRect;
        mViewRects[id].append(info);
    }

    mMouseRect = QRectF();
    mTmpRects[id] = mViewRects[id];
    applyholeact->trigger();
    update();
}

void ViewPattern::onRemoveViewAct()
{
    auto id = holeID();
    ViewRectF info;
    info.flag = false;// 表示是保存还是删除这个区域

    // 框选的时候保存框选的矩形,不保存单击生成的矩形
    if (!mDrapRectF.isEmpty()) {
        info.rect = mDrapRectF;
        LOG<<"1: "<<info.rect;
        mViewRects[id].append(info);
    } else {
        LOG<<"2: "<<info.rect;
        info.rect = mMouseRect;
        mViewRects[id].append(info);
    }

    LOG<<info.rect<<info.flag;
    mMouseRect = QRectF();
    mTmpRects[id] = mViewRects[id];
    applyholeact->trigger();
    update();
}

void ViewPattern::onApplyHoleAct()
{
    if (mViewInfo[HoleGroupNameField].toString().isEmpty())
        return;

    QVariantMap m;
    m[HoleGroupNameField] = mViewInfo[HoleGroupNameField];// 组装组名称,方便pattern依据组名查找所有孔
    m[HoleGroupColorField] = mViewInfo[HoleGroupColorField]; // 组装组颜色,可以让pattern把同组内其他可能不相同的颜色全部统一
    m[HoleViewSizeField] = mViewInfo[HoleViewSizeField]; // 组装视野窗口尺寸
    m[HoleViewPointsField].setValue(mViewRects[holeID()]); // 视野窗口的区域信息
    m[HoleCoordinateField] = mViewInfo[HoleCoordinateField]; // 坐标信息顺带组装
    m[WellAllGroupsField] = mViewInfo[WellAllGroupsField]; // 孔板所有组名信息顺带组装
    m[WellAllHolesField] = mViewInfo[WellAllHolesField]; // 孔板所有选择的孔坐标信息顺带组装
    emit applyHoleEvent(m);

    viewRectsMapToViewMask();
    //LOG<<mViewMask;
}

void ViewPattern::onApplyGroupAct()
{
    if (mViewInfo[HoleGroupNameField].toString().isEmpty())
        return;

    QVariantMap m;
    m[HoleGroupNameField] = mViewInfo[HoleGroupNameField];// 组装组名称,方便pattern依据组名查找所有孔
    m[HoleGroupColorField] = mViewInfo[HoleGroupColorField]; // 组装组颜色,可以让pattern把同组内其他可能不相同的颜色全部统一
    m[HoleViewSizeField] = mViewInfo[HoleViewSizeField]; // 组装视野窗口尺寸
    m[HoleViewPointsField].setValue(mViewRects[holeID()]); // 视野窗口的区域信息
    m[HoleCoordinateField] = mViewInfo[HoleCoordinateField]; // 坐标信息顺带组装
    m[WellAllGroupsField] = mViewInfo[WellAllGroupsField]; // 孔板所有组名信息顺带组装
    m[WellAllHolesField] = mViewInfo[WellAllHolesField]; // 孔板所有选择的孔坐标信息顺带组装
    emit applyGroupEvent(m);

    auto holeCoordinates = mViewInfo[HoleGroupCoordinatesField].value<QPointVector>();//拿到本组其它孔的所有孔坐标
    foreach(auto pt, holeCoordinates) {
        auto pt_idx = pt.x()*PointToIDCoefficient+pt.y(); // 本组其他孔的临时数据区更新为当前孔的视野信息
        mTmpRects[pt_idx] = mViewRects[holeID()];
        mViewRects[pt_idx] = mViewRects[holeID()];
    }
}

void ViewPattern::onApplyAllAct()
{ // 应用到所有组
    QVariantMap m;
            m[HoleViewSizeField] = mViewInfo[HoleViewSizeField]; // 组装视野窗口尺寸
            m[HoleViewPointsField].setValue(mViewRects[holeID()]); // 视野窗口的区域信息
            m[HoleGroupColorField] = mViewInfo[HoleGroupColorField]; // 组装组颜色,可以把所有组颜色统一(可能没分过组默认颜色红色,无所谓)
            m[HoleGroupNameField] = mViewInfo[HoleGroupNameField];// 组装组名信息(应用到所有组时只有同组的组颜色需要覆盖)
            emit applyAllEvent(m);// 3个信息足够

            auto allholes = mViewInfo[WellAllHolesField].value<QPoint2DVector>();//拿到所有分过组的孔坐标
            foreach(auto holes, allholes) {
                foreach (auto hole, holes) {
                    auto pt_idx = hole.x()*PointToIDCoefficient+hole.y(); // 所有其他孔的临时数据区更新为当前孔的视野信息
                    mTmpRects[pt_idx] = mViewRects[holeID()];
                    mViewRects[pt_idx] = mViewRects[holeID()];
                }
            }
}

ViewPattern::ViewPattern(QWidget *parent) : QWidget(parent)
{
    saveviewact = new QAction(tr("Selecting Points"));
    removeviewact = new QAction(tr("Remove Points"));
    applyholeact = new QAction(tr("Apply To Hole"));
    applygroupact = new QAction(tr("Apply To Group"));
    applyallact = new QAction(tr("Apply To All"));
    addAction(saveviewact);
    addAction(removeviewact);
    //addAction(applyholeact); // 不显式添加
    addAction(applygroupact);
    addAction(applyallact);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(saveviewact,&QAction::triggered,this,&ViewPattern::onSaveViewAct);
    connect(removeviewact,&QAction::triggered,this,&ViewPattern::onRemoveViewAct);
    connect(applyholeact,&QAction::triggered,this,&ViewPattern::onApplyHoleAct);
    connect(applygroupact,&QAction::triggered,this,&ViewPattern::onApplyGroupAct);
    connect(applyallact,&QAction::triggered,this,&ViewPattern::onApplyAllAct);
}

int ViewPattern::holeID() const
    { // 每个孔双击打开视野窗口都是一对一的
        auto coordinate = mViewInfo[HoleCoordinateField].toPoint();
        auto id = coordinate.x()*PointToIDCoefficient+coordinate.y();// 保证索引唯一不重叠2k+y,每个孔对应唯一的idx
        return id;
    }

    bool ViewPattern::checkField() const
    { // 避免bug或者漏掉信息,审查mViewInfo的字段是否完整
        auto fields = mViewInfo.keys();

        bool r1 = fields.contains(HoleGroupNameField); // 组名称
        bool r2 = fields.contains(HoleGroupColorField);// 组颜色
        bool r3 = fields.contains(HoleViewSizeField);// 视野内部划分尺寸
        bool r4 = fields.contains(HoleViewPointsField); // 视野区域
        bool r5 = fields.contains(WellAllGroupsField); // 所有组名
        bool r6 = fields.contains(HoleCoordinateField); // 当前孔坐标
        bool r7 = fields.contains(WellAllHolesField); // 所有孔坐标
        bool r8 = fields.contains(HoleGroupCoordinatesField); // 本组的所有孔坐标

        Q_ASSERT(r1 == true);
        Q_ASSERT(r2 == true);
        Q_ASSERT(r3 == true);
        Q_ASSERT(r4 == true);
        Q_ASSERT(r5 == true);
        Q_ASSERT(r6 == true);
        Q_ASSERT(r7 == true);
        Q_ASSERT(r8 == true);

        return r1&&r2&&r3&&r4&&r5&&r6&&r7&&r8;
    }

    void ViewPattern::initViewMask()
    {
        mViewMask.clear();
        for(int r = 0; r < mSize; ++r)
        {
            QBoolVector vec;
            for(int c = 0; c < mSize; ++c) {
                vec.append(false);
            }
            mViewMask.append(vec);
        }
    }

    QRectF ViewPattern::mapToSize(const QRectF &source,const QPointF&ref_point,int ref_w,int ref_h)
    { // source已经是0-1的等比例缩放了
        auto topleft = source.topLeft();
        auto size = source.size();

        auto x = topleft.x() * ref_w + ref_point.x();// 左上角顶点(0.2,0.3),长度(0.25,0.35)
        auto y = topleft.y() * ref_h + ref_point.y();// 放大到尺寸为(ref_w,ref_h),例如100
        auto w = size.width() * ref_w; // 那么结果就是(20,30,25,35),如果左上角参考点还需要移动就变成 (30,50,25,35)
        auto h = size.height() * ref_h;

        return QRectF(x,y,w,h);
    }

    QRectF ViewPattern::mapFromSize(const QRectF &source,const QPointF&ref_point,int ref_w,int ref_h)
    { //source非标准,将其标准化到0-1
        auto topleft = source.topLeft();
        auto size = source.size();

        auto x = (topleft.x() - ref_point.x()) / ref_w;// 相对窗口左上角的区域(100,0,50,50),参考区域是(50,0,100,100)
        auto y = (topleft.y() - ref_point.y()) / ref_h;// [(100-50)/100,(0-0)/100,50/100,50/100]
        auto w = size.width() / ref_w; // 那么结果就是(0.5,0,0.5,0.5)
        auto h = size.height() / ref_h;
        //LOG<<QRectF(x,y,w,h);

        return QRectF(x,y,w,h);
    }

    void ViewPattern::viewRectsMapToViewMask()
    { // 把mViewRects[idx]的信息映射到Mask,依据mSize
        auto viewRects = mViewRects[holeID()];

        for(int r = 0; r < mSize; ++r) {
            for(int c = 0; c < mSize; ++c) {
                for(auto viewRect: viewRects) {
                    auto flag = viewRect.flag;
                    auto rect = mapToSize(viewRect.rect,QPoint(0,0),mSize,mSize); // 等比例放大尺寸到mSize
                    if (rect.intersects(QRectF(c,r,1.0,1.0))) {
                        mViewMask[r][c] = flag; //掩码对应位置根据flag标记是保存还是删除的区域
                    }
                } // 对于位置[r][c]for结束后,就知道这个位置是否被选中
            }
        }

    }

    ViewInfo ViewPattern::viewInfo() const
    {
        return mViewInfo;
    }

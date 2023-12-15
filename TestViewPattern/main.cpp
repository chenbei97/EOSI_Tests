#include "viewpattern.h"

#include <QApplication>

static QString  getStr(const QString& s)
{
    int idx = s.indexOf(".");
    int count = s.mid(idx+1).count();
    QString res = s;
    if (count>6) {
        res = s.left(idx+1+6);
    } else if (count < 6) {
        auto bit = 6-count;
        while (bit--) {
            res.append("0");
        }
    }
    return res;
}

static QString  getStr(double n)
{
    return getStr(QString::number(n));
}

static QString  getStr(int n)
{
    return getStr(QString::number(n)+".");
}

static QPointF convertToPointF(const QString& text)
{ // (0.835,0.33),(0,1)这样的字符串
    Q_ASSERT(text.count(",") == 1);
    Q_ASSERT(text.count("(") == 1);
    Q_ASSERT(text.count(")") == 1);

    auto tmp = text;
    tmp.remove(0,1);
    tmp.chop(1);

    auto x = tmp.section(",",0,0,QString::SectionSkipEmpty).toDouble();
    auto y = tmp.section(",",1,1,QString::SectionSkipEmpty).toDouble();

    return {x,y};
}

static QRectF convertToRectF(const QString& text)
{ // (0.71,0.205,0.1725,0.35)
    Q_ASSERT(text.count(",") == 3);
    Q_ASSERT(text.count("(") == 1);
    Q_ASSERT(text.count(")") == 1);

    auto tmp = text;
    tmp.remove(0,1);
    tmp.chop(1);

    auto values = tmp.split(",",QString::SkipEmptyParts);
    Q_ASSERT(values.count() == 4);

    return {values[0].toDouble(),values[1].toDouble(),
            values[2].toDouble(),values[3].toDouble()};
}

static QSet<QString> convertToSet(const QString& text)
{ // a,b,c
    QSet<QString> set;
    auto tmp = text;

    auto values = tmp.split(",",QString::SkipEmptyParts);
    for(auto val: values)
        set.insert(val);
    return set;
}

static QPointFVector convertToPointFVector(const QString& text)
{ // "(0.3075,0.4075),(0.27675,0.59175),(0.50175,0.36675),(0.50175,0.59175)"
    Q_ASSERT(text.count(",") % 2 == 1); //一定是奇数个
    QPointFVector points;

    int count = 0;
    for(int i = 0; i < text.count(); ++i) {
        if(text[i] == ",") {
            count++;
            if (count % 2 == 1) { // 奇数位置的","是2个数字之间的
                int s1 = i,s2 = i;
                while (text[s1] != "(") {
                    s1--;
                } //匹配时的s1就是"("的索引
                while (text[s2] != ")") {
                    s2++;
                }//匹配时的s2就是")"的索引
                auto x = text.mid(s1+1,i-s1-1).toDouble();
                auto y = text.mid(i+1,s2-i-1).toDouble();
                points.append(QPointF(x,y));
            }
        }
    }

    return points;
}

static QPointF2DVector convertTo2DPointFVector(const QString& text)
{ // "(0,2),(1,2)|(0,0),(0,1),(1,0),(1,1)"
    Q_ASSERT(text.contains("|"));
    QPointF2DVector points;

    auto section = text.split("|",QString::SkipEmptyParts);
    for(auto sec: section)
        points.append(convertToPointFVector(sec));

    return points;
}

static QPointVector convertToPointVector(const QString& text)
{ // "(1,2),(4,5),(7,8),(3,9)"
    Q_ASSERT(text.count(",") % 2 == 1); //一定是奇数个
    QPointVector points;

    int count = 0;
    for(int i = 0; i < text.count(); ++i) {
        if(text[i] == ",") {
            count++;
            if (count % 2 == 1) { // 奇数位置的","是2个数字之间的
                int s1 = i,s2 = i;
                while (text[s1] != "(") {
                    s1--;
                } //匹配时的s1就是"("的索引
                while (text[s2] != ")") {
                    s2++;
                }//匹配时的s2就是")"的索引
                auto x = text.mid(s1+1,i-s1-1).toInt();
                auto y = text.mid(i+1,s2-i-1).toInt();
                points.append(QPoint(x,y));
            }
        }
    }

    return points;
}

static QPoint2DVector convertTo2DPointVector(const QString& text)
{ // "(0,2),(1,2)|(0,0),(0,1),(1,0),(1,1)"
    Q_ASSERT(text.contains("|"));
    QPoint2DVector points;

    auto section = text.split("|",QString::SkipEmptyParts);
    for(auto sec: section)
        points.append(convertToPointVector(sec));

    return points;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString  text = "(1.347782,334.557896)";
    LOG<<convertToPointF(text)<<convertToPointF("(1.5,2.0)")
//      <<convertToRectF("(0.71,0.205,0.1725,0.35)")
//     << convertToSet("a,b,c")
//     <<convertToPointFVector("(0.3072225,0.4075),(0.27675,0.59175),(0.50175,0.36675),(0.50175,0.59175)")
//    <<convertToPointFVector("(0,0),(0,1)")
//    <<convertToPointVector("(1,2),(4,5),(7,8),(3,9)")
//    <<convertToPointFVector("(0.835,0.33),(0.7515,0.522)")
    <<convertTo2DPointVector("(0,2),(1,2)|(0,0),(0,1),(1,0),(1,1)");

    ViewPattern w;
    const int size = 100;
    QVariantMap m;
    m[HoleViewSizeField] = size;
    m[HoleGroupNameField] = "A组";
    m[HoleGroupColorField] = QColor(Qt::cyan);
    m[HoleCoordinateField] =QPoint(0,0);
    if (size > view_well_6_4x*10)
        w.resize(400*3,400*3);
    else if (size < view_well_6_4x) w.resize(400,400);
    else w.resize(800,800);
    w.setViewInfo(m);
    w.show();

    auto inter1 = 2.5 / 1200.0;
    auto inter2 = 1.5 / 1200.0;
    auto inter3 = 315.978/ 1287.0;

    auto s1 =QString::number(inter1);
    auto s2 = QString::number(inter2);
    auto s3 = QString::number(inter3);
    LOG<<inter1<<inter2<<inter3;
    LOG<<s1<<s2<<s3;
    LOG<<getStr(inter1)<<getStr(inter2)<<getStr(inter3)<<getStr(5);

//    LOG<<QRect(0,0,100,100).marginsRemoved(QMargins(10,20,30,40)); // QRect(10,20 60x40)
    //LOG<<QRect(0,0,100,100).moveBottom(QPoint(10,10));
    return a.exec();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

class C; // A的友元类,提前声明

// <1> 声明B的成员函数是A的友元函数
class A; // 必须事先声明，因为B用到了A*w
class B{ // 必须要在A的声明之前声明，因为A用到了B::increase_age
public:
//    void increase_age(A&w){
//        w.mAge ++; // 因为A还没有定义,所以这里不能直接提供实现
//    };
    void increase_age(A*w); // 只能声明个函数，实现要在A的后边
};

class A : public QMainWindow
{
    Q_OBJECT
private:
    int mAge;
public:
    void setAge(int age) {mAge = age;}
    int age() const {return mAge;}

    friend void increase_age(A&w);
    friend void B::increase_age(A*w);
    friend class C;

};

// <1> 声明B的成员函数是A的友元函数 ,如果在头文件要用inline,否则重复定义
// B类的整个声明要在A前边,因为A用到了B，如果B的声明在A后边会提示不完整类型
// 又因为B也用到了A，所以B声明的前边要声明A
// 或者放在cpp定义
//inline void B::increase_age(A*w)
//{
//    w->mAge ++;
//}

// <2>全局函数是A的友元函数可以访问A的成员,要声明static不会重复定义
static void increase_age(A&w)
{
    w.mAge ++;
}

// <3> 类C是A的友元类,C的所有成员函数均可以访问 class C要在A的前边声明
class C {
public:
    void increase(A*a) {
        a->mAge += 2;
    };
    void decrease(A*a) {
        a->mAge -= 3;
    };
};


#endif // MAINWINDOW_H

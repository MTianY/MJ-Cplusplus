//
//  main.cpp
//  Part2Demo
//
//  Created by 马天野 on 2018/10/11.
//  Copyright © 2018 Maty. All rights reserved.
//


#include <iostream>
using namespace std;

#pragma mark 内联函数
//inline int sum(int a, int b) {
//    return a + b;
//}

//int sum (int a, int b) {
//    return a + b;
//}

//inline int sum(int a, int b);

#pragma mark 递归
//inline int sum1 (int a, int b) {
//    return sum1(a, b);
//}

#pragma mark
inline int sum2(int a) {
    return a + a;
}

#define sum3(a) ((a)+(a))

#pragma mark 引用
enum Season {
    ChunTian,
    XiaTian,
    QiuTian,
    DongTian
};

struct Student {
    int age;
};

int &func() {
    int a = 10;
    return a;
}

#pragma mark 交换两个数的值
// 指针写法
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 引用写法
void swap1(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    
}

int func11() {
    return 10;
}

int sum4(const int &a, const int &b) {
    return a + b;
}

//int sum5(const int a, const int b) {
//    return a + b;
//}

int main() {
    
    int v1 = 10;
    int v2 = 20;
    
//    sum4(v1, v2);
    cout << "sum4(v1, v2) = " << sum4(v1, v2) << endl;
    
//    const int v3 = 10;
//    const int v4 = 20;
    int v3 = 50;
    int v4 = 20;
//    sum4(v3, v4);
    cout << "sum4(v3, v4) = " << sum4(v3, v4) << endl;

    
//    int a = 20;
//    int b = 30;
//
//    int age = 10;
////    int &rAge = func11();
//
//   const double &ref = age;
    
//    int age = 10;
//    int const &rAge = 30;
    
//    // 常引用
//    int age = 10;
//    int const &rAge = age;
//    rAge = 30;
    
    // const
    
//    int age = 10;
//    const int *p0 = &age;
//    int const *p1 = &age;
//    int * const p2 = &age;
//    const int * const p3 = &age;
//    int const * const p4 = &age;
    
    
//    int v1 = 10;
//    int v2 = 20;
////    swap(v1, v2);
//    swap1(v1, v2);
//
//    cout << "v1 = " << v1 << endl;
//    cout << "v2 = " << v2 << endl;
    
    
//    func() = 30;
    
//    cout << "sum(int a, int b) = " << sum(10, 20) << endl;
//    sum(10, 20);
    
//    sum1(20, 20);
    
//    int d = 10;
//    sum2(d++);
//    cout << "sum2(d++) = " << sum2(d++) << endl;
//    cout << "sum3(d++) = " << sum3(d++) << endl;
    
    // 指针
//    int age = 20;
//    int *pAge = &age;
//    cout << *pAge << endl;
//
//    *pAge = 30;
//    cout << "*pAge = " << *pAge << endl;
    
    // 引用
//    int age = 30;
//    int &rAge = age;
//
//    rAge = 40;
//    cout << rAge << endl;
    
//    Season season;
//    Season &rSeason = season;
//
//    rSeason = DongTian;
//    cout << rSeason << endl;
    
//    Student Stu;
//    Student &rStu = Stu;
//    rStu.age = 20;
//    cout << rStu.age << endl;

//    int a = 10;
//    int b = 20;
//    int *p = &a;        // 指针 p 指向 a 的地址
//    int *&rP = p;       // rp 引用指针 p, 就是指针 p 的别名
//
//    rP = &b;            // 将 b 的地址赋值给 rp, 就是赋值给指针 p, 此时指针 p 指向 b
//    *p = 30;            // 修改 b 为30
//
//    cout << a << endl;
//    cout << b << endl;
    
//    int array[] = {10, 20, 30};
//    int (&rArray)[3] = array;
    
//    int age = 10;
//    int &rAge = age;
//    int *p = &rAge;
//    int array[] = {rAge, age};
    
//    int &array[];
    
    return 0;
}


//inline int sum (int a, int b) {
//    return a + b;
//}

//
//  main.cpp
//  C++FirstDemo
//
//  Created by 马天野 on 2018/10/10.
//  Copyright © 2018 Maty. All rights reserved.
//

#include <iostream>
#include "test_c.h"
using namespace std;

#pragma mark 函数重载
// int sum(double a, int b) {
//    return a + b;
//}
//
// int sum(int b, double a) {
//    return a + b;
//}

//extern "C" {
//     int sum(double a, int b) {
//        return a + b;
//    }
//
//     int sum(int b, double a) {
//        return a + b;
//    }
//}

#pragma mark 二义性
void display(double a) {
    cout << "display(double a)" << a << endl;
}

void display(long a) {
    cout << "display(long a)" << a << endl;
}

// 再加一个 int 类型的就可以
void display(int a) {
    cout << "display(int a)" << a << endl;
}

void display() {
    cout << "display()" << endl;
}

extern "C" void test1();

#pragma mark 带默认参数的函数
void func (int a = 20) {
    cout << "func(int a)" << a << endl;
}

// 错误写法
//void func (int a = 20, int b) {
//
//}

#pragma mark
void test111 (int a, int b) {
    cout << "test111(int int)" << endl;
}

void display111(int a, void(*func)(int,int) = test111){
    cout << "a is " << a << endl;
    cout << "func is " << func << endl;
}

#pragma mark
void test2(int a, int b = 20) {
    cout << "a is" << a << endl;
}

void test2(int a) {
    cout << "a is" << a << endl;
}

#pragma mark main 函数
int main () {
    
//    test2(100);
    
    // 打印 hello World!
    cout << "Hello World!" << endl;
    
    // 输入 age 并打印 age
//    int age;
//    cin >> age;
//    cout << "age is = " << age << endl;
    
//    cout << "sum = " << sum(1.1, 10) << endl;
//    cout << "sum = " << sum(10, 3.3) << endl;
    
    display();
    display(10);
    display(10l);
    display(10.1);
    
    test1();
    
    cout << "getSum(int a, int b) = " << getSum(10, 30) << endl;
    
    func();
    func(10);
    
    // 指向函数的指针
    void(*funcPtr)(int, int) = test111;
    funcPtr(10, 30);
    
    display111(100, funcPtr);
    
    
    return 0;
}

void test1() {
    cout << "test1 = " << endl;
}

//
//  main.cpp
//  Part4Demo
//
//  Created by 马天野 on 2018/10/15.
//  Copyright © 2018 Maty. All rights reserved.
//

#include <iostream>
using namespace std;

// struct 类
struct TYPerson {
  
    // 成员变量
    int age;
    
    // 成员函数
    void run() {
        cout << "run()-age is = " << age << endl;
    }
    
};

// class 类
class TYStudent {
public:
    // 成员变量
    int no;
    // 成员函数
    void study() {
        cout << "study()" << endl;
    }
    
};

int main () {
    
    // 创建 person 对象
    TYPerson person;
    // 访问成员变量
    cout << "person.age = " << person.age << endl;
    // 访问成员函数
    person.run();
    
    // 创建student 对象
    TYStudent student;
    // 访问成员变量
    student.no;
    student.study();
    
    return 0;
}

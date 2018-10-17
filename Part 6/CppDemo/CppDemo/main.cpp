//
//  main.cpp
//  CppDemo
//
//  Created by Maty on 2018/10/17.
//  Copyright © 2018 kangarootec. All rights reserved.
//

#include <iostream>
#include "Test.hpp"
using namespace std;

struct TYCar {
    TYCar() {
        cout << "构造函数 TYCar()" << endl;
    }
    
    ~ TYCar() {
        cout << "析构函数 ~TYCar() " << endl;
    }
};

struct TYPerson {
    int m_age;
    TYCar *m_car;
    TYPerson() {
        cout << "构造函数: TYPerson()" << endl;
        this->m_age = 0;
        this->m_car = new TYCar();
        delete this->m_car;
        
    }
    ~ TYPerson() {
        cout << "析构函数: ~ TYPerson()" << endl;
    }
};

struct TYStudent : TYPerson {
    
    TYStudent() {
        cout << "构造: TYStudent()" << endl;
    }
    
    ~ TYStudent() {
        cout << "析构: ~TYStudent()" << endl;
    }
    
    
};

namespace TY {
    int g_age;
    
    class Person {
    private:
        int m_height;
    public:
        Person() {
            cout << "构造函数 TY:: Person()" << endl;
        }
        
        ~ Person() {
            cout << "析构函数 TY:: ~Person()" << endl;
        }
        
    };
    
    void test() {
        
    }
    
}

void test1() {
    cout << "--" << endl;
}

namespace TYFirst {
    
    namespace TYSecond {
        
        int g_age1;
        
        class Person1 {
            
        public:
            Person1(){
                
            }
            
            ~ Person1() {
                
            }
            
        };
        
        void test3() {
            
        }
        
    }
    
}

struct TYFF {
    
    int m_a;
    int m_b;
    int m_c;
    int m_d;
    
    TYFF(){
        this->m_a = 0;
        this->m_b = 0;
    }
    
    TYFF(int a, int b) {
        this->m_a = a;
        this->m_b = b;
    }
    
    
    TYFF(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {
        
    }
    
    TYFF(int a, int b, int c, int d) : m_a(1), m_b(1), m_c(1), m_d(1) {
        
    }

};


int main() {
    
    TYStudent *stu = new TYStudent();
    stu->m_age = 20;
    delete stu;
    
//    TYFirst::TYSecond::g_age1 = 20;
//
//    TYFirst::TYSecond:: Person1 *p = new TYFirst::TYSecond:: Person1();
//    delete p;
    
//    using namespace TY;
//
//    Person *per = new Person();
//    delete per;
//    test();
    
    
    
//    TY:: Person *per = new TY:: Person();
//    delete per;
//
//    TY:: test();
//
//    :: test1();
    
//    // 栈空间
//    TYPerson person;
//    cout << "person.m_age = " << person.m_age << endl;
    
    
    // 堆空间
//    TYPerson *person2 = new TYPerson();
//    cout << "person2->m_age = " << person2->m_age << endl;
//
//    cout << "Start ====> 即将执行delete person2" << endl;
////    delete person2;
//    cout << "End ====> 执行完 delete person2" << endl;
    
    
    // 因为上面的 TYCar *m_car; 是指针,不是对象. new TYCar 在堆空间
//    TYPerson *p = new TYPerson();
    
    // 不建议释放TYCar 写在这里.正确做法应该是写在 TYPerson 里.
//    delete p->m_car;
//    delete p;
    
    
//    TYRR *r = new TYRR();
//    delete r;
    
    return 0;
}

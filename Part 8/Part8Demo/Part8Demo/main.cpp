//
//  main.cpp
//  Part8Demo
//
//  Created by 马天野 on 2018/10/22.
//  Copyright © 2018 Maty. All rights reserved.
//

#include <iostream>
using namespace std;

class Animal {
  
public:
    int m_age;
    
    virtual void speak() {
        cout << "Animal: speak()" << endl;
    }
    
    virtual void run() {
        cout << "Animal: run()" << endl;
    }
    
};

class Cat : public Animal {
    
public:
    int m_life;
    
    Cat() : m_life(0) {}
    
    void speak() {
        
        // 先执行父类的成员函数
        Animal::speak();
        
        cout << "Cat: speak()" << endl;
    }
    
    void run() {
        cout << "Cat: run()" << endl;
    }
    
};

class Person {
public:
    virtual void run() {
        cout << "Person: run()" << endl;
    }
    Person() {
        cout << "构造 Person()" << endl;
    }
    virtual ~Person() {
        cout << "析构 ~ Person()" << endl;
    }
    
};

class Student : public Person {
public:
    void run() {
        cout << "Student: run()" << endl;
    }
    ~ Student() {
        cout << "析构: ~Student()" << endl;
    }
};

int main() {
    
//    Animal *animal = new Cat();
//    animal->speak();
//    animal->run();
    
    Person *stu = new Student();
    stu->run();
    delete stu;
    
    return 0;
}

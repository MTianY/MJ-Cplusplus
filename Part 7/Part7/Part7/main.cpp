//
//  main.cpp
//  Part7
//
//  Created by Maty on 2018/10/18.
//  Copyright © 2018 kangarootec. All rights reserved.
//

#include <iostream>

using namespace std;

class Person {
    int m_age;
public:
    Person() {
        cout << "构造函数: Person()" << endl;
        this->m_age = 0;
    }
    
    Person(int age) {
        cout << "构造函数: Person(int age)" << endl;
        this->m_age = age;
    }
    
    ~ Person() {
        cout << "析构函数: ~Person()" << endl;
    }
};

class Student : public Person {
    int m_height;
public:
//    Student() {
//        cout << "构造函数: Student()" << endl;
//        this->m_height = 0;
//    }
    
    Student() : Person(10) {
        cout << "构造函数: Student()" << endl;
    }
    
    ~ Student() {
        cout << "析构函数: ~Student()" << endl;
    }
};

class Animal {
  
public:
    int m_age;
    
    Animal() {
        cout << "构造函数: Animal()" << endl;
    }
    ~ Animal() {
        cout << "析构函数: ~Animal()" << endl;
    }
    
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
    
    Cat() {
        cout << "构造函数: Cat()" << endl;
    }
    ~ Cat() {
        cout << "析构函数: ~Cat()" << endl;
    }
    
    void speak() {
        cout << "Cat: speak()" << endl;
    }
    
    void run() {
        cout << "Cat: run()" << endl;
    }
};

class Dog : public Animal {
public:
    int m_bone;
    
    Dog() {
        cout << "构造函数: Dog()" << endl;
    }
    ~ Dog() {
        cout << "析构函数: ~Dog()" << endl;
    }
    
    void speak() {
        cout << "Dog: speak()" << endl;
    }
    
    void run() {
        cout << "Dog: run()" << endl;
    }
};

class Pig : public Animal {
public:
    int m_rice;
    
    Pig() {
        cout << "构造函数: Pig()" << endl;
    }
    ~ Pig() {
        cout << "析构函数: ~Pig()" << endl;
    }
    
    void speak() {
        cout << "Pig: speak()" << endl;
    }
    
    void run() {
        cout << "Pig: run()" << endl;
    }
};

//void walk(Dog *dog) {
//    dog->run();
//}
//
//void walk(Cat *cat) {
//    cat->run();
//}

void walk(Animal *animal) {
    animal->run();
}

int main() {
    
//    Person person;
//    Student student;
    
    // 默认情况下,编译器只会根据指针类型调用对应的函数,不存在多态
//    Dog *dog = new Dog();
//    dog->run();
    
//    Cat *cat = new Cat();
//    cat->run();
    
    // 父类指针可以指向子类对象
//    Animal *ani = new Dog();
//    ani->run();
    
//    walk(new Dog());
//    walk(new Cat());
//    walk(new Animal());
//    walk(new Pig());
    
    Animal *cat = new Cat();
    cat->m_age = 20;
    cat->speak();
    cat->run();
    
    delete cat;
    
    return 0;
    
}

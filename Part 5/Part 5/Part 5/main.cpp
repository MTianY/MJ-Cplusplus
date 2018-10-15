//
//  main.cpp
//  Part 5
//
//  Created by 马天野 on 2018/10/15.
//  Copyright © 2018 Maty. All rights reserved.

#include <iostream>
using namespace std;

struct TYPerson {
private:
    int m_age;
public:
    void setAge(int age) {
        if(age<0) return;
        this->m_age = age;
    }
    
    int getAge() {
        return this->m_age;
    }
    
};

void test() {
    int *p = new int;
    delete p;
}

void test1() {
    int *p = new int[10];
    delete[] p;
}

int main () {
    
    int *p = (int *)malloc(4);
    *p = 10;
    free(p);
    
    
    
    
    return 0;
}

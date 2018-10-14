//
//  main.cpp
//  Part 3Demo
//
//  Created by 马天野 on 2018/10/15.
//  Copyright © 2018 Maty. All rights reserved.
//

#include <iostream>
using namespace std;

int main () {
    
    int age = 10;
//    const int &rAge = age;
    const long &rAge = age;
    age = 30;
    
    cout << "age is = " << age << endl;
    cout << "rAge is = " << rAge << endl;
    
    return 0;
    
}

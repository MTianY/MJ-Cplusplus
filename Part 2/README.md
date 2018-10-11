## 1. 内联函数 (inline function)

#### 使用 `inline` 修饰函数的声明或者实现, 就可以使其变成内联函数.

```c++
inline int sum(int a, int b) {
    return a + b;
}
```

另一种写法:`建议在声明和实现上都增加 inline 修饰`.

```c++
inline int sum(int a, int b);

int main() {
    
    cout << "sum(int a, int b) = " << sum(10, 20) << endl;
    
    return 0;
}


inline int sum (int a, int b) {
    return a + b;
}
```

#### 内联函数的3个特点:

- 编译器会将函数调用直接展开为函数体代码.
    - 如上面的`sum`函数.当为内联函数后,其本质就是

    ```c++
    cout << "sum(int a, int b) = " << 10+20 << endl;
    ```
    
    - 正常的函数调用,说下会为其开辟一个栈空间,然后当函数执行完成之后,将函数内的局部变量释放掉. 而内联函数, 编译器识别出它是内联函数后,就会将这个函数里的东西(函数体)直接拿过来用.

    将代码编译成汇编后,会发现.当不使用内联函数的时候,会为`sum`开辟内存空间. 使用内联函数之后,不会为其开辟内存空间.
    
- 可以减少函数调用的开销
    - 这样就不会存在调用函数,开辟栈空间和释放变量的开销 
- 会增大代码的体积
    - 所以当一个函数代码太多的话,就不适合使用内联函数. 

#### 注意

- 递归函数,即使在前面写上`inline`,它也不是内联函数.
- `inline`其实只是建议编译器将函数变成内联函数.

#### 内联函数什么情况下使用?

- 函数的代码量不是很多,最好10行以内的
- 函数的调用频率比较高的.
    - 这样就会防止频繁的内存开辟和回收.

#### 内联函数和宏的区别

首先, 内联函数和宏,都可以`减少`函数调用的`开销`.

但是对比宏, 内联函数多了`语法检测`和`函数特性`.

语法检测很好理解,就是编译报错什么的.

函数特性举例如下:

如果是内联函数:

- 执行`sum2(d++)`. 就是 `sum2(d++)`, `d++` 是当做参数传进来的

```c++
inline int sum2(int a) {
    return a + a;
}

int main() {

    int d = 10;
    cout << "sum2(d++) = " << sum2(d++) << endl;
    
    return 0;
}

// 打印结果: sum2(d++) = 22
```

如果是宏:

- `sum3(d++)`.其实就是 `((d++) + (d++))`

```c++
#define sum3(a) ((a)+(a))

int d = 10;
sum3(d++);
```

## 2. #pragma once

之前为了防止头文件被重复导入,经常是如下的写法:

```c++
// 表示没有被定义过,执行条件
#ifndef test_hpp
#define test_hpp

#include <stdio.h>

#endif /* test_hpp */
```

而`#pragma once`可以简化上面的写法.

#### `#pragma once` 可以防止整个文件的内容被重复包含.

#### 二者区别

- `#ifndef` 、 `#define` 、 `#endif` 因为受 `C\C++` 标准的支持, 不受编译器的任何限制.而且它可以针对一个文件中的某部分代码来条件编译.但是`#pragma once`是针对整个文件的.
- 但是`#pragma once` 有些编译器不支持.

## 3. 引用

#### C 语言中,使用指针 (Pointer) 可以访问和修改某个变量的值.

```c

int main() {
    int age = 20;
    int *pAge = &age;
    
    // 通过指针访问某个变量,取值
    cout << *pAge << endl;
    
    // 修改变量的值
    *pAge = 30;
    cout << "*pAge = " << *pAge << endl;
    
    return 0;
}

```

#### C++ 中,使用引用 (Reference) 可以起到跟指针类似的功能.

引用,使用的符号是 `&`. 

```c++
// 引用, 相当于是变量的别名.
int age = 30;
int &rAge = age;
```

给引用赋值,直接拿名字使用, 不用像`C`指针似的,还得加`*`.

```c++
// 引用
int age = 30;
int &rAge = age;
    
rAge = 40;
cout << rAge << endl;

// 打印结果: 40
```

##### 枚举类型加引用

```c++
enum Season {
    ChunTian,
    XiaTian,
    QiuTian,
    DongTian
};

int main() {
    
    Season season;
    Season &rSeason = season;
    
    rSeason = DongTian;
    cout << rSeason << endl;
    return 0;

}

// 打印结果 : 3
```

##### 结构体类型加引用

```c++
struct Student {
    int age;
};

int main() {
    Student stu;
    Student &rStu = stu;
    rStu.age = 20;
    cout << rStu.age << endl;
}   

// 打印结果: 20
```

##### 指针变量加引用.

```c++
int a = 10;
int b = 20;
int *p = &a;        // 指针 p 指向 a 的地址
int *&rP = p;       // rp 引用指针 p, 就是指针 p 的别名
    
rP = &b;            // 将 b 的地址赋值给 rp, 就是赋值给指针 p, 此时指针 p 指向 b
*p = 30;            // 修改 b 为30
    
cout << a << endl;
cout << b << endl;

// 打印结果: a = 10; b = 30;
```

##### 数组加引用

还能像上面那样直接加 `&` 符号吗? 不能了.

- 必须用括号括起来.
- 必须指定原先数组有多少个成员.

```c++
int array[] = {10, 20, 30};
int (&rArray)[3] = array;
```

#### 引用注意点:

- 对引用做计算, 就是对引用所指向的变量做计算.
- 在定义的时候就必须初始化, 一旦指向了某个变量, 就不能变了.

```c++
// 不初始化不行
// ✘ 错误写法
int age = 10;
int &rAge;
```

- 可以利用引用初始化另一个引用, 相当于某个变量多个别名.

```c++
// 下面的 rAge1 和 rAge2 其实都是对 age 的引用.
int age = 10;
int &rAge1 = age;
int &rAge2 = rAge1;
```

- 不存在引用的引用

```c++
// ✘ 错误写法
int age = 20;
int &rAge = age;
// 不能引用再引用这么写.
int &&rAge2 = rAge;
```

- 不存在指向引用的指针

```c++
// ✘ 错误写法
int age = 10;
int &rAge = age;
int & *p = &rAge;
```

- 不存在引用数组

```c++
int age = 20;
int &rAge = age;
int *p = &rAge;
// ✘ 错误写法
int &array[];
// √ 正确写法
int array[] = {rAge, age};
```

- 引用比指针安全些,不会像指针会乱指.
- 函数的返回值可以被赋值

```c++
// 这个函数意义不大,因为函数调用完 a 已经被释放了,此时在赋值30 没什么用.
int &func() {
    int a = 10;
    return a;
}

int age = 10;

// 当有全局变量这种,会有些意义.
int &func() {
    // 做一些处理 age 的操作..
    // 将处理好的 age 返回
    return age;
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

int main () {
 
    func() = 30;
    
    int v1 = 10;
    int v2 = 20;
//    swap(v1, v2);
    swap1(v1, v2);
    
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    
}

```

## 4. const

- `const` 表示`常量`, 被它修饰的变量`不能修改`.且定义的时候一定要初始化.

```c++
// ✘ 错误写法, 必须初始化
const int age;

// √ 正确写法
const int age = 10;
```

- 如果修饰的是 `类`、 `结构体(的指针)`,其成员也不能被修改.

- 如下5个指针分别是什么意思?

**被`const`修饰,有个记忆方法: `const 只修饰它右边的东西.`**



```c++
int age = 10;

// *p0是常量,不能修改. p0不是常量,可以修改
const int *p0 = &age;       // const 修饰的是 *p0

// *p1是常量, p1不是常量
int const *p1 = &age;       // const 修饰 *p1

// p2是常量, *p2 不是常量
int * const p2 = &age;  // const 修饰 p2

// p3是常量, *p3不是常量
const int * const p3 = &age;    // const 修饰 p3

// *p4 和 p4 都是常量
int const * const p4 = &age; // 第一个 const 修饰 *p4 . 第二个 const 修饰 p4;
```

`const` 修饰 `*p` 这种表示不能通过指针修改它指向的内存了. 

## 5. 常引用 (Const Reference)

引用通过`const` 修饰,这样就无法修改数据了,称为`常引用`.

- `const`必须写在 `&` 符号的左边.才算常引用.




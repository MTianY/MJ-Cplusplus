# C++ 语法 Part 1

> 函数重载
> extern
> 内联函数

### Hello World

```c++
#include <iostream>
using namespace std;

int main () {
    cout << "Hello World!" << endl;
    return 0;
}
```

##### 关键字 : `cout` : 

- 输出
- 后面跟 `<<`

##### 关键字 : `cin`

- 输入
- 后面跟 `>>`

##### 关键字 : `endl`

- 换行

```c++
#include <iostream>
using namespace std;

int main () {
    cout << "Hello World!" << endl;
    
    int age;
    cin >> age;
    cout << "age is = " << age << endl;
    return 0;
}
```

### 函数重载

1. C 语言`不支持`函数重载.
2. 函数重载定义:

- `函数名`相同, 但是参数的`个数`或参数的`顺序`或参数的`类型`不同.
- 注意与`返回值类型`无关.
- 注意`二义性`的也不被允许.

√ 正确写法

```c++
#include <iostream>
using namespace std;

int sum(double a, int b) {
    return a + b;
}

int sum(int b, double a) {
    return a + b;
}

int main () {
    
    // 打印 hello World!
    cout << "Hello World!" << endl;
    
    // 输入 age 并打印 age
//    int age;
//    cin >> age;
//    cout << "age is = " << age << endl;
    
    cout << "sum = " << sum(1.1, 10) << endl;
    cout << "sum = " << sum(10, 3.3) << endl;
    
    return 0;
}
```

✘ 错误写法: 返回值类型不同.

```c++
int sum(int b, double a) {
    return a + b;
}

void sum(int b, double a) {
    
}
```

- 上面这种只有返回值不同的,不能算作函数重载,而且还会报错.

✘ 错误写法: 二义性的也不被允许

```c++
void display(double a) {
    cout << "display(double a)" << a << endl;
}

void display(long a) {
    cout << "display(long a)" << a << endl;
}
```

- 上面的写法,当调用 `display(10)` 这个函数时,实参会发生隐式类型的转换,所以不确定调用哪一个函数,因为都可以.
- 编译器此时也会报错.`Call to 'display' is ambiguous`

##### 函数重载的本质

- 本质就是采用了 `name mangling (或 name decoration)` 技术.
- `c++` 编译器默认会对符号名 (变量名、函数名等)进行改编、修饰, 也有叫做"命名倾轧" 的.
- 函数重载时会生成多个不同的函数名,不同编译器由不同的生成规则

上面的`二义性`代码如果加上另两个方法,再调用函数时,就不会发生`二义性`.

```c++
void display(int a) {
    cout << "display(int a)" << a << endl;
}

void display() {
    cout << "display()" << endl;
}
```

调用函数如下:

```c++
display();
display(10);
display(10l);
display(10.1);  
```

打印信息:

```c++
display()
display(int a)10
display(long a)10
display(double a)10.1
```

通过查看`main.cpp`的汇编代码实现,搜索`display`, 发现有3个,有可能是重载后生成的函数名.

```s
"_Z7displayl"
"_Z7displayi"
"_Z7displayv" 
```

### extern "C" 

**被 `extern "C"` 修饰的代码会按照 `C 语言` 的方式去编译.**

如将上面函数重载的代码,添加 `extern "C"` 之后,会报错,因为 C 语言中不支持函数重载.

```c++
extern "C" int sum(double a, int b) {
    return a + b;
}

extern "C" int sum(int b, double a) {
    return a + b;
}
```

上面可以简写为:

```c++
extern "C" {

    int sum(double a, int b) {
       return a + b;
    }
    
    int sum(int b, double a) {
       return a + b;
    }
    
}
```

当一个函数的声明和实现,分开写的时候,`extern "C"` 要写在`函数声明`那里.

✘ 错误写法:

```c++
// 写在函数实现这里会报错
extern "C" void test1() {
    cout << "test1 = " << endl;
}
```

√ 正确写法:

```c++
extern "C" void test1();
```

如果`C语言`文件单独创建,函数声明及实现写在`C语言`文件了,在`c++`中该如何调用`C 语言`中的函数.

下面是在`C语言`头文件中正确写法:

```c
// 防止重复导入
#ifndef test_c_h
#define test_c_h

#include <stdio.h>

#ifdef __cplusplus
// 因为 C 语言中不支持 extern "C" 这个语法,所以这里做判断,当时 C++ 环境时才是用
extern "C" {
#endif
    int getSum(int a, int b);
#ifdef __cplusplus
}
#endif

#endif /* test_c_h */
```

### C++ 函数的默认参数

`C++`允许函数设置默认参数, 在调用时可以根据情况省略实参.规则如下:

- 默认参数只能按照从`右->左`的顺序.(因为从左到右开始赋值)
- 如果函数同时有`声明`、`实现`、默认参数只能放在`函数声明`中.
- 默认参数的值可以是`常量`、`全局符号`(全局变量、函数名).

```c++
void func (int a = 20) {
    cout << "func(int a)" << a << endl;
}
```

执行下面函数:

```c++
func();
func(10);
```

打印结果:

```c
func(int a)20
func(int a)10
```

✘错误写法:

```c++
void func (int a = 20, int b) {
    
}
```

√ 正确写法

```c++
void func (int a, int b = 20) {
    
}
```

因为函数调用,从左边开始传参.

指向函数的指针:

```c++
void test111 (int a, int b) {
    cout << "test111(int int)" << endl;
}

 // 指向函数的指针
void(*funcPtr)(int, int) = test111;
funcPtr(10, 30);
```

当函数重载、默认参数产生冲突、二义性时,建议优先选择使用默认参数

```c++
void test2(int a, int b = 20) {
    cout << "a is" << a << endl;
}

void test2(int a) {
    cout << "a is" << a << endl;
}
```

当调用`test2(100)`时就会报错,有二义性,所以此时建议保留带默认参数的函数,删除另一个.


# Part 6


## 析构函数

在对象销毁的时候,自动调用,一般用来完成对象的清理工作.

#### 特点

- 函数名同类名.
- 以`~`开头.
- 无返回值(void 都不能写)
- 无参数
- 不能重载
- 有且只有一个析构函数

```c++
struct TYPerson {
    int m_age;
    TYPerson() {
        cout << "构造函数: TYPerson()" << endl;
        this->m_age = 0;
    }
    ~ TYPerson() {
        cout << "析构函数: ~ TYPerson()" << endl;
    }
};
```

下面分别是在栈空间和堆空间调用 TYPerson 对象

```c++
int main() {

    // 栈空间
    TYPerson person;
    cout << "person.m_age = " << person.m_age << endl;
    
    // 堆空间
    TYPerson *person2 = new TYPerson();
    cout << "person2->m_age = " << person2->m_age << endl;
    // 堆空间要手动释放
    delete person2;
    
    return 0;
}
```

打印结果:

```c
构造函数: TYPerson()
person.m_age = 0
构造函数: TYPerson()
person2->m_age = 0
析构函数: ~ TYPerson()
析构函数: ~ TYPerson()
```

#### 析构函数到底释放的什么?

- 使用 `new TYPerson()` 时,要手动执行 `delete person2`.这里是回收 `m_age` 所占的4个字节.
- `delete`释放该对象时,会`先`调用该对象的析构函数.
- 析构函数的作用不是删除对象,而是在撤销对象占用的内存之前完成一些清理工作,使这部分内存可以被程序分配给新对象使用.

#### 看下面给出的代码,会有什么问题?

- 下面这段代码会发生内存泄漏, `TYCar` 对象得不到释放.

```c++
struct TYCar {
    TYCar() {
        cout << "构造函数: TYCar()" << endl;
    }
    
    ~ TYCar() {
        cout << "析构函数: ~TYCar()" << endl;
    }
    
};

struct TYPerson {
    
    int m_age;
    TYCar *m_car;
    
    TYPerson() {
        cout << "构造函数: TYPerson()" << endl;
        this->m_car = new TYCar();
    }
    
    ~ TYPerson() {
        cout << "析构函数: ~TYPerson()" << endl;
    }
    
};

```

执行如下代码:

```c++
int main() {
    TYPerson *p = new TYPerson();
    delete p;
    return 0;
}
```

上面代码的内存布局如下图:

![](https://lh3.googleusercontent.com/-lOvEMOMA53s/W8ardyPyPTI/AAAAAAAAAO8/Ndd-_NzC6wIjRDQXJTskzxU5C_2QVizVQCHMYCw/I/15397466706339.jpg)

- `TYPerson *p = new TYPerson()`
    - 指针 `p` 在栈空间. `main`函数执行完毕自动释放.
    - `TYPerson`对象因为执行了`delete`操作,也会得到释放.
    - 最后来到下面这个图:

    ![](https://lh3.googleusercontent.com/-beeVqzXczRY/W8ascgP8HHI/AAAAAAAAAPM/Be5Ytrcw7UEhdRD2ccjBs34YbrBJiX7aACHMYCw/I/15397469269077.jpg)

- 就会发现此时`堆空间`中还有`TYCar`没有得到释放.所以会造成内存泄漏.

所以上面还需要对`TYCar`进行释放.

正确写法:

```c++
struct TYPerson {
    
    int m_age;
    TYCar *m_car;
    
    TYPerson() {
        cout << "构造函数: TYPerson()" << endl;
        
        // 这里用 new 是想在堆空间申请内存,为 TYCar 对象保命
        this->m_car = new TYCar();
        
        // 释放 TYCar;
        delete this->m_car;
    }
    
    ~ TYPerson() {
        cout << "析构函数: ~TYPerson()" << endl;
    }
    
};
```


## 域运算符 ::

如声明如下类

```C++
struct TYPerson {
private:
    int m_age;
public:
    TYPerson();
    ~TYPerson();
}
```

在实现文件中实现时,要加个域运算符,指定这些是谁的东西.

```C++
TYPerson :: TYPerson() {

}

TYPerson :: ~TYPerson() {

}
```

## 命名空间

命名空间可以避免命名冲突

```c++

void test1() {

}

namespace TY {

    // 是全局变量
    int g_age;
    
    class Person {
    
    private:
        int m_age;
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
```

使用时:

```c++
int main() {

    TY::Person *p = new TY::Person();
    delete p;
    
    // 调用 TY 命名空间内部的函数时:
    TY::test();
    
    // 调用最外层的函数时
    // 其本质意义就是 ::test1();
    // :: 是层级最高的
    test1();
    // :: test1();
    
    return 0;
}
```

- 命名空间的大括号和函数的大括号意义不同,这里的`g_age`仍旧是个`全局变量`;

也可以这么用:

```C++
int main() {
    // 这么写之后,就不用每个都写 TY 了
    using namespace TY;
  
    Person *per = new Person();
    delete per;
    test();
 
}
```

- 命名空间不影响内存布局.
- 不能有二义性.
- 命名空间可以嵌套,最外层就是 `::`, 它是`默认的命名空间`, 我们写的所有命名空间都被嵌套在它里面.

```c++
namespace TYFirst {
    
    namespace TYSecond {
        
        int g_age1;
        
        class Person1 {
            
            Person1(){
                
            }
            
            ~ Person1() {
                
            }
            
        };
        
        void test3() {
            
        }
        
    }
    
}
```

使用

```c++
int main() {

    TYFirst::TYSecond::g_age1 = 20;
    TYFirst::TYSecond:: Person1 *p = new TYFirst::TYSecond:: Person1();
    delete p;
    
    return 0;
}
```


## 继承

```C++
struct TYPerson {
    int m_age;
    
    TYPerson() {
        cout << "构造函数: TYPerson()" << endl;
    }
    
    ~ TYPerson() {
        cout << "析构函数: ~TYPerson()" << endl;
    }
    
};

struct TYStudent : TYPerson {
    
    TYStudent() {
       cout << "构造函数: TYStudent()" << endl; 
    }
    
    ~ TYStudent() {
        cout << "析构函数: ~TYStudent()" << endl;
    }
    
};
```

- `C++` 中的继承不像`OC`那样,每个对象最终都会继承自`NSObject`. 这里的 `TYPerson` 就是最后一个父类了,上面没有父类了.

### 成员的访问权限

- private
    - 私有,只有`当前类`内部可以访问

- public
    - 公共的,都可以访问
     
- protected
    - `子类`内部, `当前类`内部可以访问.

    
## 初始化列表

- 便捷的初始化方式

```c++
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
    
    
    // 初始化列表
    // 将传进来的 a 赋值给 m_a
    // 将传进来的 b 赋值给 m_b
    // 将传进来的 c 赋值给 m_c
    TYFF(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {
        
    }
    
    // 这种写法,不管外接传进来什么,都不会用.都是1.
    TYFF(int a, int b, int c, int d) : m_a(1), m_b(1), m_c(1), m_d(1) {
        
    }
    
    // 记住这个本质就是下面:
    // 所以说也可以直接初始化传来一个函数
    TYFF(int a, int b, int c, int d) : m_a(1), m_b(1), m_c(1), m_d(1) {
        this->m_a = 1;
        this->m_b = 1;
        this->m_c = 1;
        this->m_d = 1;
    }

};

```

- 初始化的顺序只和 `成员的声明顺序` 有关

## 构造函数的互相调用

- 构造函数调用构造函数只能在初始化列表里做.

下面这种写法是错误的

```c++
struct Person {
    int m_age;
    int m_height;
    
    Person() {
        // ✘ 这种调用方法错误的!
        Person(0,0);
    }
    
    Person(int age, int height) {
        this->m_age = age;
        this->m_height = height;
    }
};
```

正确写法:

```C++
struct Person {
    int m_age;
    int m_height;
    Person() : Person(10,10) {
        cout << "Person()" << endl;
    }
    Person(int age, int height) {
        this->m_age = age;
        this->m_height = height;
    }
    
    void display() {
    
    }
    
};
```

```C++
int main() {
    
    Person person;
    person.display();
    
    return 0;
}
```

- `Person person` 首先调用的是`无参`的构造函数.
- 构造函数是对象创建完毕,内存分配成功之后再调用的.
- `person.display()` 是将 `person`对象的地址值,传给 `display`这个函数的`this`指针.
- 构造函数也一样.也是将地址值传给构造函数的`this`指针.
    
    





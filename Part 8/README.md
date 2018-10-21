Part 8

## 虚表补充

子类继承父类, 父类中的函数如果都是`虚函数`,子类有如果没有`重写`这个函数,调用的话,那么虚表中存的就是父类虚函数的地址.

如下代码,子类`Cat`没有重写父类`Animal`的`speak()`函数.那么虚表中存的是`父类虚函数 speak()地址 和 子类 Cat 的 run() 函数地址`.

```C++
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
    
    void run() {
        cout << "Cat: run()" << endl;
    }
    
};

int main() {
    
    Animal *animal = new Cat();
    animal->speak();
    animal->run();
    
    return 0;
}
```

## 子类执行父类的成员函数

- 在子类成员函数中,先执行父类的成员函数.

```C++
// 写法(类似 super) 
Animal::speak();
```

```C++
class Cat: public Animal {
public:
    int m_life;
    
    Cat() : m_life(0) {}
    
    void speak() {
        // 先执行父类的成员函数
        Animal::speak();
        // 再执行自己的
        cout << "Cat: speak()" << endl;
    }
    void run() {
        cout << "Cat: run()" << endl;
    }
};
```

- 所以,如果想直接用父类的函数,那么就`不需要重写父类的虚函数.`
- 如果想自己做些东西,那么就重写,但是不要调用父类函数.
- 如果想在父类函数的基础上,加一些自己的操作,那么就在子类重写的那个函数内部,先调用父类的虚函数,加上`Animal::speak()`这种操作.

## 虚析构函数

含有虚函数的类,如果将析构函数声明为虚函数,就是虚析构函数.

其特点是:

- `delete` 父类指针时, 才会调用子类的析构函数,保证析构的完整性.

首先看下如下代码, 当 `delete` 之后,是否释放干净?

```C++
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
    Person *stu = new Student();
    stu->run();
    
    // 释放 stu 指向的堆空间
    delete stu;
    
    return 0;
}

// 打印结果:
构造 Person()
Student: run()
析构 ~ Person()
```

上面并没有释放 `Student` 这个类.如果要想释放它,那么需要将父类的析构函数变为`虚析构函数`.

```C++
class Person {
public:
    virtual void run() {
        cout << "Person: run()" << endl;
    }
    Person() {
        cout << "构造 Person()" << endl;
    }
    // 虚析构函数
    virtual ~Person() {
        cout << "析构 ~ Person()" << endl;
    }
    
};
```

## 纯虚函数

有些时候,我们的父类有一些函数确实不知道该怎么实现,或者实现这个函数没有什么意义.具体的要由子类去实现的这种,我们就需要把他们定位成纯虚函数.

纯虚函数:

- 没有函数体且初始化为0的虚函数,用来定义接口规范.

```C++
class Animal {
public:
    virtual void speak() = 0;
    virtual void run() = 0;
};
```

注意,下面是错误写法:

```C++
// ✘错误写法:
// 这种写法叫声明函数! 不是纯虚函数!
virtual void speak();
```

## 抽象类

- 含有纯虚函数的类.
- 不能实例化,不能创建对象的类.
- 可以包含非纯虚函数.

```C++
class Animal() {
public:
    virtual void speak() = 0;
    virtual void run()= 0;
};
```

- 抽象类的使命就是用来被别人继承的,因为它不能用来创建对象,只能来定义接口规范.


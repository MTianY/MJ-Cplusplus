# Part 7

## 初始化列表补充

如果函数声明和实现时分类的.

- 初始化列表只能写在函数的实现中.
- 默认参数只能写在函数的声明中

```c++
class Person {
    
private:
    int m_age;
    int m_height;
public:
    Person() {
        cout << "构造函数: Person()" << endl;
    }
    
    ~ Person() {
        cout << "析构函数: ~Person()" << endl;
    }
    
    Person(int age, int height) : m_age(age), m_height(height) {
    
    }
    
};
```

下面这种在声明中,直接写初始化列表的是错误的

```c++
class Student {
	private:
		int m_a;
		int m_b;
	public:	
		Student();
		~Student();
		
		// ✘ 错误写法.
		Student(int a, int b) : m_a(a), m_b(b);
};
```


## 子类与父类的构造函数

- 创建子类对象时,会自动调用父类的`无参`构造函数.

```C++
class Person {
    int m_age;
public:
    Person() {
        cout << "构造函数: Person()" << endl;
        this->m_age = 0;
    }
    
    ~ Person() {
        cout << "析构函数: ~Person()" << endl;
    }
};

class Student : public Person {
    int m_height;
public:
    Student() {
        cout << "构造函数: Student()" << endl;
        this->m_height = 0;
    }
    ~ Student() {
        cout << "析构函数: ~Student()" << endl;
    }
};
```

创建`Student`对象时,默认会调用其父类`Person`的构造函数.

```C++
int main() {
    Student stu;
}

// 打印结果:
构造函数: Person()
构造函数: Student()
析构函数: ~Student()
析构函数: ~Person()

```

- 如果子类的构造函数显示的调用了父类的`有参`构造函数,就`不会`再去默认调用父类的`无参`构造函数.

```C++
class Person {
private:
    int m_age;
public:
    Person() {
        cout << "构造函数: Person()" << endl;
    }
    Person(int age) {
        this->m_age = age;
        cout << "构造函数: ~Person()" << endl;
    }
    ~Person() {
        cout << "析构函数: ~Person()" << endl;
    }
};

class Student : public Person {
    
private:
    int m_height;
    
public:

    Student() : Person(10) {
        cout << "构造函数: Student()" << endl;
    }
    
    ~Student() {
        cout << "析构函数: ~Student()" << endl;
    }
    
}
```

执行如下:

```C++
int main() {
    
    Student stu;
    
    return 0;
}

// 打印如下:
构造函数: Person(int age)
构造函数: Student()
析构函数: ~Student()
析构函数: ~Person()

```

- 如果父类缺少无参构造函数,子类的构造函数必须显示调用父类的有参构造函数.

## 父类指针,子类指针.

- 父类指针可以指向子类对象,是安全的,继承方式必须是`public`.
- 子类指针指向父类对象是不安全的.

## 多态

- 默认情况下,编译器只会根据指针类型调用对应的函数,不存在多态
- 多态是面向对象非常重要的一个特性
    - 同一操作作用于不同的对象,可以有不同的解释,产生不同的执行结果.
    - 在运行时,可以识别出真正的对象类型,调用对应子类中的函数.

- 多态的要素
    - 子类重写父类的成员函数(`override`)
    - 父类指针指向子类对象
    - 利用父类指针调用重写的成员函数.    

- `重写`与`重载`的区别
    - `重写`是子类重写父类的函数,名字和父类的一毛一样.参数都一样.
    - `重载`是函数名一致,参数不同等等.    


下面这个代码暂时还没有实现多态的功能

```C++
class Animal {
public:
    void run() {
        cout << "Animal: run()" << endl;
    }
};

class Cat : public Animal {
public:
    void run() {
        cout << "Cat: run()" << endl;
    }
};

class Dog : public Animal {
public:
    void run() {
        cout << "Dog: run()" << endl;
    }
};

class Pig : public Animal {
public:
    void run() {
        cout << "Pig: run()" << endl;
    }
};
```

上面可以看到.父类`Animal`. 子类`Cat, Dog, Pig`.且子类`重写`父类的`run`方法.

因为三个子类有一个共同的父类.`父类指针可以指向子类.`所以有个函数:

```C++
void walk(Animal *animal) {
    animal->run();
}
```

在`main`函数中调用 `walk` 函数.

```C++
int main() {
    
    walk(new Dog());
    walk(new Cat());
    walk(new Pig());
    walk(new Animal());
    
    return 0;
}

打印结果:
Animal: run()
Animal: run()
Animal: run()
Animal: run()
```

- 上面这个例子很好的证明了: `默认情况下,编译器只会根据指针类型调用对应的函数,不存在多态`.
- `walk`函数是根据`Animal`的指针去调用其函数的.

那么多态该如何实现?

## 虚函数

在C++中, 多态是通过`虚函数 virtual`来实现的.

虚函数:

- 被 `virtual` 修饰的`成员函数`.
- 如果父类是`虚函数`了,被`virtural`修饰,那么当子类重写这个函数的时候,可以不用再写`virtural`这个关键字了.

如将上面代码的父类函数前面加上`virtural`,再运行程序看一下.

```C++
class Animal {
  
public:
    virtual void run() {
        cout << "Animal: run()" << endl;
    }
    
};
```

再次运行程序,执行如下代码:

```C++
int main() {
    
    walk(new Dog());
    walk(new Cat());
    walk(new Animal());
    walk(new Pig());
    
    return 0;
}

打印结果:
Dog: run()
Cat: run()
Animal: run()
Pig: run()
```

这就是多态的特性了.


## 虚表 (虚函数表)

虚函数的实现原理是什么? ---> `虚表`.

虚表里面存储着最终需要调用的`虚函数地址`.这个虚表也叫`虚函数表`.

如下面代码:

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
    
    void speak() {
        cout << "Pig: speak()" << endl;
    }
    
    void run() {
        cout << "Pig: run()" << endl;
    }
};
```

在`main`函数中,执行如下

```C++
int main() {
    Animal *cat = new Cat();
    cat->speak();
    cat->run;
}

// 打印结果:
Cat: speak()
Cat: run()
```



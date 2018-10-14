# 类

### C++ 中可以使用 `struct` 和 `class` 来定义一个类.

在 C 语言中,`struct`是个结构体,但是在`C++`中,它是一个类.

#### struct 类

```c++
// struct 类
struct TYPerson {
  
    // 成员变量
    int m_age;
    
    // 成员函数
    void run() {
        cout << "run()-m_age is = " << m_age << endl;
    }
    
};
```

访问这个类

```c++
int main () {
    
    // 创建 person 对象
    TYPerson person;
    // 访问成员变量
    cout << "person.m_age = " << person.m_age << endl;
    // 访问成员函数
    person.run();
    
    return 0;
}
```

- `TYPerson person`. 就已经创建好对象了.就是已经分配好内存给 person 对象了.
- person 对象,在内存中的`main`函数这个栈空间中.不是在堆空间中.`main`函数执行完会自动回收.

#### class 类

```c++
// class 类
class TYStudent {
    // 成员变量
    int m_no;
    // 成员函数
    void study() {
        cout << "study()" << endl;
    }  
};
```

访问其成员变量,如果还像 struct 那种写法,会报错的.

```c++
int main () {
    TYStudent student;
    // 发现报错了,不能访问 no.
    student.m_no;
}
```

#### `struct类` 和 `class 类` 的最大区别就是`权限`.

- `struct` 类的默认成员权限是 `public`.
- `class` 类的默认成员权限是 `private`.

### struct 类在内存中的占用情况

- 上面的 `struct TYPerson` 类在内存中占 `4个字节`. 
- 因为它只有一个成员`int m_age`.
- 其中的`void run` 不占用对象`TYPerson`的内存空间.
    - 这个函数是公用的,不是和对象放在一个空间.
    - 再创建几个对象,也同样是用这个方法.

#### 通过指针访问成员

```c++
TYPerson person;
TYPerson *pPerson = &person;
pPerson ->m_age = 30;
pPerson ->run();
```

- 与通过对象访问的区别是,通过指针用`->`. 通过对象访问直接用`.`.

### 窥探类在内存中的布局

如下代码,看其在内存中的布局情况;

```c++
int main() {
    
    TYPerson person;
    person.m_age = 20;
    person.run();
    
    TYPerson *pPerson = &person;
    pPerson->m_age = 30;
    pPerson->run();
    
    return 0;
}
```
    
     


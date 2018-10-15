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
struct TYPerson {

    int m_id;
    int m_age;
    int m_height;
    
    void display() {
        cout << "m_id is = " << m_id << endl;
        cout << "m_age is = " << m_age << endl;
        cout << "m_height is = " << m_height << endl;
    }

};
int main() {
    
    TYPerson person;
    person.m_id = 1;
    person.m_age = 2;
    person.m_height = 3;
    
    cout << "&person 对象内存地址: " << &person << endl;
    
    cout << "&person.m_id 地址: " << &person.m_id << endl;
    
    cout << "&person.m_age 地址: " << &person.m_age << endl;
    
    cout << "&person.m_height 地址: " << &person.m_height << endl;
        
    return 0;
}
```

打印上面的对象内存地址,可以看出, `m_id`和`m_age`和`m_height`这三个成员在内存中是连续的.

内存图:

![](https://lh3.googleusercontent.com/-B6SF-MpjxnQ/W8RebAt8rUI/AAAAAAAAAOc/SaNnIWRc2Is5xZ_JOmZxyrq5WqIj7geawCHMYCw/I/15395958775971.jpg)

## this

- this 是指向`当前对象`的指针.
- 对象在调用成员函数的时候,`会自动传入当前对象的内存地址`.

上面的 TYPerson 类的成员函数其实就是下面的

```c++
struct TYPerson {
    
    int m_id;
    int m_age;
    int m_height;
    
    void display() {
        cout << "m_id is " << this->m_id << endl;
        cout << "m_age is " << this->m_age << endl;
        cout << "m_height is " << this->m_height << endl;
    }
    
};
```

函数的代码在内存中只有一份!存在代码区.每个函数都有内存地址,用的时候直接`call 内存地址`.

执行 display 函数要去代码区找代码,而`m_id`等存在栈空间,就是代码区的代码要访问栈空间的东西,所以,将 person 对象的地址值传给 display 这个函数就好了.

##### 汇编分析 this

用 `person` 对象调用 `display` 函数.

- `this`就是指向 `TYPerson`对象的指针
- `this`里面存储的就是`person`对象的地址值.

```c++
TYPerson person;
person.display();
```

```c
// ecx 存 person 对象的地址值
lea ecx, [ebp-14h]
// call display 函数,然后进入这个 call 00F0145B 看一下
call 00F0145B
```

进入`call 00F0145B`观察:

```c
TYPerson::display:
...
```

```c
// this->m_id = 5;
mov eax,dword ptr [this]
mov dword ptr [eax],5

// this->m_age = 6;
mov eax,dword ptr [this]
mov dword ptr [eax+4], 6

// this->m_height = 7;
mov eax, dword ptr [this]
mov dword ptr [eax+8],7
```

#### 一个应用在内存中的分区:

- 栈空间
    - 每调用一个函数就会给它分配一段连续的栈空间,等函数调用完毕后会自动回收这段栈空间.
    - 自动分配和回收. 
- 堆空间
    - 需要主动去申请和释放. 
- 代码区
    - 用来存放代码 
- 全局区(数据段)
    - 用来存放全局变量等. 


    
     


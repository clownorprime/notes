### 指针和引用的概念
指针和引用都能够实现间接的访问某个对象
指针是一个对象，其本身存储的是所指对象的虚拟内存地址，而引用是一个变量的别名.

### 指针和内存的关系
指针所处的地址上存放的值是其指向元素的地址。

### 底层const和顶层const
底层const指的是指针所指的对象是一个const,我们无法修改指针所指向对象的值，但是我们可以修改指针本身的值，即我们可以使指针指向其他对象。
顶层const指的是指针本身是一个const,我们无法修改指针，使其指向其他对象，但是我们可以修改指针所指向的对象的值

观察一个指针+const的组合是顶层const还是底层const, 可以从右向左观察，比如：
const int\*p = &a; 这是一个底层const, const针对int
int \* const p = &a; 这是一个顶层const, const限制的是int\*

### 程序编译过程
gcc -E source.c 预处理阶段，替换宏定义等
gcc -S source.c -o source.asm 编译阶段，将源代码编译成为汇编代码
gcc -c source.asm -o source.o 汇编阶段，将汇编代码翻译为目标文件
ld source.o \*.o 链接阶段，将一大堆的目标文件链接成为可执行文件。

### c和c++区别
c和c++都是编译性、静态类型语言
编译性与解释性相对应，解释性语言通过解释器来翻译成为机器语言来进行执行。例如对于shell、python等解释性语言，如果我们想要某个程序执行多次，那么每一次都需要解释器将其翻译成为对应的机器语言。而对于编译性语言，我们只需要使用编译器一次执行相应的可执行文件，从而执行多次。
编译型语言的优点，不需要提供相应的环境，可以直接运行，如java等解释性语言必须安装jvm虚拟机等。

c++有多种编程范式
既可以象c语言一样面向过程，也就是面向函数编程
也可以像java一样，面向对象编程
为了实现代码的复用，也可以使用泛型编程
还可以采用元编程的编程范式

### 内存模型
c++的内存模型
包括代码段、数据段
为什么要分为代码段和数据段
1. 在链接时，我们需要将多个目标文件的代码段链接在一起成为可执行文件的代码段，我们可以设置代码段为只读，从而防止进程修改程序的指令。
2. 将代码段和数据段分开有助于提高缓存的命中率，现代CPU的缓存一般都被设计成为数据缓存和指令缓存分离
3. 将代码段和数据段分开，那么假设有多个可执行文件都需要printf.o的目标文件，那么这个时候，我们就可以在内存中仅保存一份printf.o的副本，采用动态链接的方法，将printf.o所在的位置填写在可执行文件中，那么可以节省大量的内存。
### 内存中的堆和栈分配
注意到
vector的元数据（记录vector的信息，如size, addr)等保存在栈区，而vector的实际数据保存在堆区。

### 面向对象理解
面向对象的核心思想是数据抽象，继承和动态绑定
数据抽象,也就是封装, 将类的实现和接口分离，通过封装，可以控制对数据的访问，提高代码的可维护性和安全性
继承:允许从现有的类中派生出其他的类，新的类继承了父类的属性和行为，并可以在其基础上进行修改，继承有助于提高代码的可重用性。
多态：多态指的是对象的多种表现形态。通过多态，可以在不同的对象上调用相同的方法，实际执行的操作会依据对象的具体类型而又所不同。多态提高了代码的可维护性和拓展性。
抽象：将对象的共同特征抽象出来，成为类或者接口的过程。

### 析构函数

### 什么是抽象类
抽象类指的是一个类中包含了至少一个纯虚函数，纯虚函数指的是只提供了函数的声明，而没有函数具体的实现的虚函数。
抽象类无法实例化，无法产生具体的对象，其子类必须要实现该虚函数。
# STL标准模板库
## STL的六大组成部分
1. 容器，即各种数据结构
2. 算法，各种常用算法
3. 迭代器，扮演算法和容器之间的融合剂
4. 仿函数
5. 配接器
6. 配置器，主要负责内存的配置与管理
container通过allocator取得数据存储空间，算法通过迭代器取得容器之间的内容，functor可以协助算法完成不同的策略变化，adaptor可以修饰或套接Functor.

仿函数，如果你针对某个class进行了operator()重载，那么这个class的对象使用的operator()就可以称为仿函数。

## 关于空间配置器
### 空间配置器的作用
空间配置器就是利用new和delete来提供了一系列标准的接口，来供容器进行使用。

new和delete都包含两阶段操作：
对于new来说，1.使用operator new来配置内存，2.使用构造函数来构造对象内容。
对于delete来说，1.使用operator delete来释放内存。2.使用析构函数来将对象析构.

空间配置器stl allocator将这两阶段操作区分开来，内存配置工作由alloc:allocate()来负责，内存释放工作由alloc::deallocate来负责；而对象构造由alloc::construct()来负责，对象析构由alloc::destory()来负责.

### 空间配置器的组成
空间配置器包括一级配置器和二级配置器
由于分配小型区块可能会造成内存破碎等问题，SGI设计了双层级配置器，第一级配置器直接使用malloc和free，而第二级配置器则试情况而定。
当要分配的动态内存大小超过128bytes之后，直接使用第一级配置器，否则使用第二级配置器.
第二级配置器采用了内存池(memory pool)，它每次会配置一大块内存，并维护了16个free-lists,各自管理大小为8,16,...128bytes的小额区块，当要分配的动态内存大小小于128bytes时，我们直接从这16个free-lists中选取合适的区块，直接进行分配.

free-lists的链表的长度最大为20。
假设一开始，我们要求分配一块32bytes的内存，如果这时候free-lists[2]的长度为0，意味着free-lists不能提供相应的内存，这时候，我们分配32\*40bytes大小的内存，第一个直接返回给应用程序，19个分配给free\_list[2]，剩余的20\*32bytes用作内存池。这时候，我们要求分配一块64bytes的内存，free\_lists[3]中没有任何元素，那么这时候我们可以将内存池中的20\*32bytes的内容赋给free\_lists[3]，那么这时候free\_lists中有10个区块，分配一个给应用程序，剩余9个...


## 关于迭代器的理解
### 迭代器的作用
迭代器就是提供一种方法，可以不暴露容器的内部组成，又可以按顺序访问该容器中的内容。
STL的中心思想是：将容器和算法分开，彼此之间独立设计，再用迭代器将二者粘合在一起。
迭代器最重要的内容是对operator\*和operator->进行重载。
### 迭代器的类型推导
迭代器所指对象的类型，称为该迭代器的value type.
我们可以根据c++的偏特化以及内嵌类型来推导出迭代器的value type.这可以用于我们接受一个迭代器为参数，需要返回该迭代器所指对象的类型。
template <class I>
typename iterator\_traits\<I\>::value\_type
func(I ite)
{ return \*ite; }

template <class T>
struct iterator\_traits<T\*> {
    typedef T value\_type;
    }

常见的迭代器的相应类型有五种：value\_type, difference type, pointer, reference, iterator catagoly, 如果你希望开发的容器能够完美契合与STL，那么就必须要给容器的迭代器定义这五种相应的类型。

iterator catogory又可以分为五种：
Input iterator: 只读
Output iterator: 只写
forward iterator: 可读写, 只可向前，不可向后
bidirectional iterator: 可以双向移动
random access iterator: 支持p+n, p1-p2等指针操作

## 仿函数
仿函数就是通过重载函数调用操作符的一个类, 仿函数本质上是一个类
仿函数和函数指针都是可以将整组操作用作算法的参数，但仿函数相对于函数指针有其独特的优势：
1. 灵活性：仿函数是通过类的对象来实现的，所以能够保存状态和数据，可以在调用期间保持状态，因而仿函数可以用于更加复杂的场合
2. 泛型编程：仿函数可以作为函数模板传递给泛型算法，因而更加适合STL抽象性的需求，而函数指针实现泛型编程较为麻烦。

## 适配器
### 适配器的作用
适配器就是通过提供一个中间层，将原来不兼容的接口变得兼容。它可以通过继承，组合等方法，如poe.com上的chatgpt提供的例子, 提高代码的灵活性和可维护性。



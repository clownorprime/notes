#include <iostream>
#include <memory>
#include <vector>
#include <cstring>

using namespace std;

class Example 
{
    public:
        Example() {
            cout << "example constructor" << endl;
        }
        void print() { cout << "hello" << endl; }
        ~Example() {
            cout << "example destructor" << endl;
        }
};

int main() {
    auto_ptr<Example> e0(new Example());
    auto_ptr<Example> e1(new Example());
    cout << e0.get() << endl;
    cout << e1.get() << endl;
    cout << "hello" << endl;
    cout << "world" << endl;
    cout << e1.get() << endl;
    
    /*
     * 缺点
     * 1. 赋值操作会导致资源所有权的转换
     * 比如：e0 = e1, 那么这时首先e0指向的对象将会调用析构函数，释放掉其内存空间；其次，e0指向e1所指的对象，然后e1指向null;整个过程就好用移动拷贝函数中的浅拷贝.
     * 2. 不能在容器中存放智能指针
     * 容器，如vector要求，其中的元素必须是可赋值和可复制的，而智能指针的复制涉及到资源所有权的转换，不符合这里的条件
     */
    auto_ptr<string> ptr1(new string("hello"));
    auto_ptr<string> ptr2(new string("world"));
    cout << *(ptr1) << endl;
    vector<auto_ptr<string>> vec;
    vec.push_back(ptr1);
    vec.push_back(ptr2);
    //vec[0] = vec[1];
    //cout << *vec[0] << endl;
    //cout << *vec[1] << endl;
    /*
     * 3. 不能auto\_Ptr指向一个数组.
     */
}

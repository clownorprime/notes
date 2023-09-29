#include <iostream>
#include <memory>

using namespace std;

class Example 
{
    public:
        Example() {
            cout << "example constructor" << endl;
        }
        ~Example() {
            cout << "example destructor" << endl;
        }
};

int main() {
    shared_ptr<Example> sp0;
    shared_ptr<Example> sp1(new Example());
    // use_count函数用来返回当前指向该对象的指针个数
    cout << sp0.use_count() << endl;
    shared_ptr<Example> sp2(new Example());
    sp2.reset(new Example());
    cout << sp2.get() << endl;
    cout << sp2.use_count() << endl;
}

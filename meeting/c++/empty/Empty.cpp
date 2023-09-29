#include <iostream>
#include <memory>

using namespace std;

class Empty {
    public:
    virtual void func1();
    virtual void func2();
    virtual void func3();
    int a = 3;
    auto_ptr<int> ptr;
    unique_ptr<int> uniquePtr;
};

int main() 
{
    cout << sizeof(Empty) << endl;
}

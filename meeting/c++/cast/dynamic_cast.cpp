#include <iostream>

using namespace std;

class Base {
    public:
        virtual void func() {
            cout << "hello, base" << endl;
        }
};

class Derived : public Base {
    public:
        void func() {
            cout << "hello, derived" << endl;
        }
};

int main() 
{
    Base *base = new Base;
    Derived* dirived = dynamic_cast<Derived*>(base);
    cout << dirived << endl;
    return 0;
}

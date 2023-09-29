#include <iostream>

using namespace std;
class GrandParent 
{
    public:
        GrandParent() { 
            cout << "GrandParent constructor" << endl;
            data = 1;
        }
    int data;
};

class Father : public GrandParent 
{
    public:
        Father() {
            cout << "father constructor" << endl;
        }
};

class Mother : public GrandParent 
{
    public:
        Mother() {
            cout << "mother constructor" << endl;
        }
};

class Child : public Father, public Mother 
{
    public:
        Child() {
            cout << "child constructor" << endl;
        }
};

int main() 
{
    Child c;
    cout << c.Mother::data << endl;
}

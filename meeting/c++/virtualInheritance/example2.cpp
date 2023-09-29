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

class Father : virtual public GrandParent 
{
    public:
        Father() {
            cout << "father constructor" << endl;
        }
};

class Mother : virtual public GrandParent 
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
    cout << c.data << endl;
}

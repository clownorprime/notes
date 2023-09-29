#include <iostream>
#include <memory>
#include <vector>

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
    unique_ptr<Example> e0(new Example());
    unique_ptr<Example> e1(new Example());
    auto_ptr<Example> autoPtr(new Example());
    e1.release();
}

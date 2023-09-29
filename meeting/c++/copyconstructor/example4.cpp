#include <iostream>

using namespace std;
class Example {
    public:
        Example() {
            data = 0;
            this->p = new int(2);
        }
        Example(int data) {
            this->data = data;
            this->p = new int(3);
        }
        Example(Example &e) {
            //类内的对象能够直接访问其私有成员
            //这并不违背面向对象的封装特性
            this->data = e.data;
            this->p = new int(0);
            *p = *(e.p);
        }
        ~Example() {
            delete p;
        }
    private:
        int *p;
        int data;
};

int main() 
{
    Example e(2);
    Example e2(e);
    cout << e2.getVal() << endl;
}
        

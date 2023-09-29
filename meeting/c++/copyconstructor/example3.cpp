#include <iostream>

class Example {
    public:
        Example() {
            data = 0;
            this->p = new int(2);
        }
        Example(int data) {
            this->data = data;
            this->p = new int(2);
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
}
        

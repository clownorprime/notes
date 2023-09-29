#include <iostream>

using namespace std;
class Base 
{
    public:
        virtual void speak() {
            cout << "base" << endl;
        }
};

class Dog : public Base 
{
    public:
        void speak() override {
            cout << "Dog" << endl;
        }
};

class Cat : public Base 
{
    public:
        void speak() override {
            cout << "Cat" << endl;
        }
};
int main() 
{
    Dog* dog = new Dog;
    Base* base = dog;
    Cat* cat = new Cat;
    base->speak();
    dog->speak();
    cat->speak();
}

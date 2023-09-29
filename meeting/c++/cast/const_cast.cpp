#include <iostream>

using namespace std;

int main() 
{
    int val = 2;
    const int *a = &val;
//    *a = 3;
    int *b = const_cast<int*>(a);
    *b = 3;
    cout << *b << endl;
    cout << *a << endl;
}

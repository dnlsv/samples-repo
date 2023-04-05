#include <iostream>
#include <funcs.h>

using namespace std;

int main()
{
    int a = 7, b = 10;

    cout << "a + b = " << a << " + " << b << " = " << add(a, b) << endl;

    cout << "a - b = " << a << " - " << b << " = " << diff(a, b) << endl;

    cout << "a * b = " << a << " * " << b << " = " << mult(a, b) << endl;

    cout << "a / b = " << a << " / " << b << " = " << dev(a, b) << endl;

    return 0;
}
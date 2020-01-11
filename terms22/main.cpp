#include <iostream>
#include "terms22.h"
using namespace std;

int main()
{
    Rational a(10);
    Rational b(11);
    Rational c = a + b;
    cout << c;
    return 0;
}

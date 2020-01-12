#include <iostream>
#include "terms25.h"
using namespace std;

int main()
{
    vector<Type> types{Type::Text, Type::Grap, Type::Grap, Type::Text};
    NewsLetter lhs(types);
    NewsLetter rhs(lhs);
    cout << rhs;
    return 0;
}

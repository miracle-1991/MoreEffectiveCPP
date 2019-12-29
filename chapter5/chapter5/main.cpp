#include <iostream>
#include <string>
#include <vector>
using namespace std;

//本条款主要提供了一个建议：
//不要重构任何隐式类型转换操作符或者不加explicit的单子变量constructors
//原因就是这些函数会在你意想不到的地方执行默认的转换，导致调试困难或者出现意想不到的结果
class Rational
{
public:
    Rational(string size) : m_size(stod(size)) {
        cout << __FUNCTION__ << endl;
    }

    operator double() const {
        cout << __FUNCTION__ << endl;
        return m_size;
    }

    friend bool operator == (const Rational& lhs, const Rational& rhs);
private:
    int m_size{0};
};

bool operator == (const Rational& lhs, const Rational& rhs) {
    return  lhs.m_size == rhs.m_size;
}

int main()
{
    Rational r("10");
    cout << r << endl; //编译器为了让程序执行成功，虽然没有operator <<，但是编译器硬是找到了可以隐式转换为double的方法，然后调用该方法

    string s("11");
    if (r == s) {
        cout << "相等" << endl;
    }else {
        cout << "不想等" << endl;
    }
    return 0;
}

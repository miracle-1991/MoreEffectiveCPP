#include <iostream>

using namespace std;

/*条款20：返回值优化
 * 主要讲述了必须返回一个对象时，可以使用的一个特殊写法，而该写法会被编译器优化，减少由于临时对象而产生的构造函数和析钩函数调用
*/

class Rational
{
public:
    Rational(int numerator = 0, int denominator = 1) : m_numerator(numerator), m_denominator(denominator) {
        cout << __FUNCTION__ << endl;
    }
    int numerator() const { return  m_numerator; }
    int denominator() const { return  m_denominator; }
    void print() const {
        cout << (double)m_numerator/m_denominator << endl;
    }
private:
    int m_numerator;
    int m_denominator;
};

inline const Rational operator * (const Rational& lhs, const Rational& rhs) {
    //返回构造函数的参数，让编译器自己优化掉临时变量
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

int main()
{
    Rational a = 10;
    Rational b(1, 2);
    Rational c = a * b;
    c.print();
    return 0;
}

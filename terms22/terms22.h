#ifndef TERMS22_H
#define TERMS22_H
#include <iostream>
/*条款22：考虑以操作符符合形式(op=)代替其独身形式(op)
 *主要思想：operator += 的效率比operator + 性能更好，并且能设计出通用的operator + 模板
*/

class Rational
{
public:
    Rational(int v) : val(v) {}
    Rational(const Rational& rhs) : val(rhs.val) {
        std::cout << __FUNCTION__ << std::endl;
    }

    Rational& operator += (const Rational& rhs) {
        std::cout << __FUNCTION__ << std::endl;
        val += rhs.val;
        return *this;
    }

    Rational& operator -= (const Rational& rhs) {
        val -= rhs.val;
        return *this;
    }

    friend std::ostream& operator << (std::ostream& out, const Rational& rhs);
private:
    int val;
};

std::ostream& operator << (std::ostream& out, const Rational& rhs) {
    out << rhs.val << std::endl;
    return out;
}

template <typename T>
const T operator + (const T& lhs, const T& rhs) {
    return T(lhs) += rhs; //使用匿名对象，方便编译器进行优化
}

template <typename T>
const T operator - (const T& lhs, const T& rhs) {
    return T(lhs) -= rhs;
}

#endif // TERMS22_H

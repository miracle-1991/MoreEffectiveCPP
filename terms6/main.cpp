#include <iostream>

using namespace std;

/*条款7：区分前置++和后置++
* 前置：++在前，所以是先+1，再取出;
*      ++在后，所以是先取出，再+1
* 在c++11中进行重写时，为了区分二者，后置比前置多了一个入参
*/

class UPInt
{
public:
    UPInt() : num(0) {}
    UPInt& operator++() {
        *this += 1;
        return *this;
    }
    const UPInt operator++(int) {
        UPInt oldValue = *this;
        ++(*this);
        return oldValue;
    }

    UPInt& operator+=(int n) {
        num += n;
        return *this;
    }

    friend ostream& operator << (ostream& out, UPInt& rhs);
private:
    int num;
};

ostream& operator << (ostream& out, UPInt& rhs) {
    out << rhs.num;
    return out;
}

int main()
{
    UPInt un;
    cout << un << endl;

    un++;
    cout << un << endl;

    ++un;
    cout << un << endl;
    return 0;
}

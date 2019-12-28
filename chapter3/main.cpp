#include <iostream>
#include <string>
#include <vector>
using namespace std;

//本章主要讲述了数组对象总是涉及指针的算数运算，所以不能和多态混用

class Father
{
public:
    Father() {}
    virtual ~Father() { cout << __FUNCTION__ << endl; }
    virtual string name() const { return m_name; }
    friend ostream& operator << (ostream& out, const Father& rhs);
private:
    string m_name{"Father!"};
};

ostream& operator << (ostream& out, const Father& rhs) {
    out << rhs.name() << endl;
}


class Son : public Father
{
public:
    Son() {}
    virtual ~Son() { cout << __FUNCTION__ << endl; }
    string name() const override { cnt++; return m_name; }
    friend ostream& operator << (ostream& out, const Son& rhs);
private:
    string m_name{"Son!"};
    mutable int cnt{0};
};

ostream& operator << (ostream& out, const Son& rhs) {
    out << rhs.name() << endl;
}

void Print(ostream& s, const Father arr[], int num) {
    for (int i = 0; i < num; i++) {
        s << arr[i];
    }
}

void deleteArray(Father arr[]) {
    delete [] arr;
}

int main()
{
    //例1, 如果子类比父类拥有更多的成员变量，则sizeof(子类)比sizeof(父类)要大，而数组中的arr[i]其实本质上就是*(arr + i)的缩写，所以在此处的指针偏移计算是错误的。
    Father f_arr[10];
    Print(cout, f_arr, 10);

    Son s_arr[10];
    Print(cout, s_arr, 10); //实测，打印完第一个“Son”就遇到SIGSEGV错误退出了

    //例2
    Son* ps_arr = new Son[10];
    deleteArray(ps_arr);    //同样会遇到SIGSEGV错误

    return 0;
}

#include <iostream>

using namespace std;

//More Eff C++的第二章主要讲述四种类型转化的用法

class Widget
{
public:
    Widget() {}
    virtual ~Widget() {}
    virtual void print() {
        cout << __FUNCTION__ << " Father." << endl;
    }
};

class SpecialWidget : public Widget
{
public:
    SpecialWidget() {}
    virtual ~SpecialWidget() {}
    virtual void print() override {
        cout << __FUNCTION__ << " Son." << endl;
    }
};

void SPrint(SpecialWidget* psw) {
    if (psw != nullptr) {
        psw->print();
    }
    return;
}

int doSomeThing() {
    cout << __FUNCTION__ << endl;
}

void CastTest() {
    //static_cast，基本上就是起到与C旧式转型相同的作用
    int firstNum = 100;
    int secondNum = 200;
    double result = static_cast<double>(firstNum)/secondNum;
    cout << __FUNCTION__ << " result: " << result << endl;

    //const_cast，告诉编译器，去掉表达式中的常量性
    const SpecialWidget* psw = new SpecialWidget();
    SPrint(const_cast<SpecialWidget*>(psw));
    delete psw;

    //dynamic_cast,将指向父类的指针转型为指向子类的指针，如果转型失败，会得到null指针
    //无法用在缺乏虚函数表的类型身上
    Widget* pw = new SpecialWidget();
    SPrint(dynamic_cast<SpecialWidget*>(pw));
    delete pw;

    //reinterpret_cast，最常用的用途是转换函数指针类型
    typedef void (*FuncPtr)();
    FuncPtr funcPtrArr[10] = {nullptr};
    funcPtrArr[0] = reinterpret_cast<FuncPtr>(&doSomeThing);
    for (FuncPtr ptr : funcPtrArr) {
        if (ptr != nullptr) {
            ptr();
        }
    }
    return;
}

int main()
{
    CastTest();
    return 0;
}

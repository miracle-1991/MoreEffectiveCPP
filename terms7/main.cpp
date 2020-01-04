#include <iostream>

using namespace std;
/*
* 条款8：了解各种不同意义的new和delete
* new操作符的本质：1、分配足够容纳对象的内存;2、调用构造函数在这块内存上初始化对象;
* 第一步可以简单理解为operator new函数，也是我们唯一可以重载的new;
* 第二部可以简单理解为placement new函数，用于在指定内存上构造内存
*/

struct MyStruct {
    int a;
    int b;
    double c;
    char d;
};

//千万不要重构全局的operator new，最好在类内重构
class Widget
{
public:
    Widget() {
        cout << "构造函数" << endl;
    }
    ~Widget() {
        cout << "析构函数" << endl;
    }
private:
    MyStruct m_st;
};

void* operator new(size_t size) {
    cout << "分配内存" << endl;
    return malloc(size);
}

void operator delete(void* memory) {
    cout << "释放内存" << endl;
    free(memory);
}

void* mallocShared(size_t size) {
    return  operator new(size);
}

void freeWidget(void* memory) {
    return operator delete(memory);
}

Widget* constructWidget(void* buffer) {
    return new (buffer) Widget();
}

void* deconstructWidget(Widget* pw) {
    pw->~Widget();
    return  pw;
}

int main()
{
    void* mempry = mallocShared(sizeof (Widget));
    Widget* pw = constructWidget(mempry);

    deconstructWidget(pw);
    freeWidget(pw);
    return 0;
}

#ifndef TERMS27_H
#define TERMS27_H
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;
/*
 * 条款27：要求或者禁止对象产生于heap之中
 * 1、要求对象产生于堆之中：将destructor设置为private
 * 2、检查对象是否在堆中，只用abstract base class
 * 3、禁止对象产生于堆中，将operator new设置为private
*/

//1、要求对象产生于堆中，原理：让自动析构不合法就可以了
class UPNumber
{
public:
    UPNumber() : num(0) {}
    UPNumber(int n) : num(n) {}
    UPNumber(const UPNumber& rhs) : num(rhs.num) {}

    //伪析构, const对象也可能需要被销毁
    void destory() const { delete this; }
private:
    ~UPNumber() {
        cout << __FUNCTION__ << endl;
    }
private:
    int num;
};

//2、检查对象是否位于堆中,使用纯虚类提供统一的簙记效果
using RawAddress = const void*;
class HeapTracked
{
public:
    class MissingAddress {};
    virtual ~HeapTracked() = 0;
    static void* operator new(size_t size);
    static void operator delete(void *ptr);
    bool isOnHeap() const;
private:
    static list<RawAddress> addresses;
};

class Asset : public HeapTracked
{
public:
    Asset()  { value = new UPNumber(); }
    ~Asset() { value->destory(); }
private:
    UPNumber* value;
};

//3、禁止对象产生于heap中，原理：不让调用operator new和operator delete即可
class DownNumber
{
public:
    DownNumber() {}
private:
    static void* operator new(size_t size) = delete ;
    static void operator delete(void* ptr) = delete ;
};

#endif // TERMS27_H

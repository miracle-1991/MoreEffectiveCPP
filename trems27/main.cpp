#include <iostream>
#include "terms27.h"
using namespace std;

void Test1() {
//    UPNumber n; //无法通过编译

    UPNumber* p = new UPNumber;
//    delete p; //无法通过编译

    p->destory();
}

void inventoryAssert(const Asset* ap) {
    if (ap->isOnHeap()) {
        cout << "YES IN HEAP" << endl;
    }else {
        cout << "NOT IN HEAP" << endl;
    }
}

void Test2() {
    Asset a;
    inventoryAssert(&a);

    Asset* b = new Asset;
    inventoryAssert(b);
}

void Test3() {
    DownNumber n1;
    static DownNumber n2;
//    DownNumber* p = new DownNumber; //无法通过编译
}

int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}

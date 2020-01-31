#include "terms27.h"

list<RawAddress> HeapTracked::addresses; //义务性定义
HeapTracked::~HeapTracked() {}

void* HeapTracked::operator new(size_t size) {
    void* memptr = ::operator new(size);
    addresses.push_front(memptr);   //最先申请的理论上最先被用到
    return memptr;
}

void HeapTracked::operator delete(void *ptr) {
    auto iter = find(addresses.begin(), addresses.end(), ptr);
    if (iter != addresses.end()) {
        addresses.erase(iter);
        ::operator delete(ptr);
    }else {
        throw MissingAddress();
    }
}

bool HeapTracked::isOnHeap() const {
    const void* rawAddress = dynamic_cast<const void*>(this);
    auto iter = find(addresses.begin(), addresses.end(), rawAddress);
    return iter != addresses.end();
}

#ifndef TERMS25_H
#define TERMS25_H
#include <list>
#include <vector>
#include <iostream>
/*条款25：词条款主要讲了3个技巧，可以根据输入的数据调用不同类型的构造、复制构造和打印函数
 * 1、virtual constructor：虚拟构造，其实不是把构造函数写成virtual(写成virtual编译器也不支持)，而是根据不同的数据产生不同的对象
 * 2、virtual copy constructor：虚拟复制构造，根据不同的数据调用不同类型的复制构造函数
 * 3、virtual no-member function：虚拟非成员函数，根据不同的数据，调用不同的成员函数，比如打印函数
*/

enum class Type {
    Text,
    Grap
};

class NLComponent
{
public:
    NLComponent() {}
    virtual NLComponent* clone() const = 0;
    virtual std::ostream& print(std::ostream& s) const = 0;
};

class TextBlock : public NLComponent
{
public:
    TextBlock() {}
    virtual TextBlock* clone() const override {
        return new TextBlock(*this);
    }
    virtual std::ostream& print(std::ostream& s) const override {
        s << "TextBlock" << "\t";
        return s;
    }
};

class Graphic : public NLComponent
{
public:
    Graphic() {}
    virtual Graphic* clone() const override {
        return new Graphic(*this);
    }
    virtual std::ostream & print(std::ostream &s) const override {
        s << "Graphic" << "\t";
        return s;
    }
};

inline std::ostream& operator << (std::ostream& s, const NLComponent& c) {
    return c.print(s);
}

class NewsLetter
{
public:
    NewsLetter(const std::vector<Type>& types) {
        for (const Type& t : types) {
            components.push_back(readComponents(t));
        }
    }

    //virtual copy constructor
    NewsLetter(const NewsLetter& rhs) {
        for (auto iter = rhs.components.begin(); iter != rhs.components.end(); iter++) {
            components.push_back((*iter)->clone());
        }
    }
    friend std::ostream& operator << (std::ostream& s, const NewsLetter& n);
private:
    //virtual constructor
    static NLComponent* readComponents(const Type& t) {
        NLComponent* ret = nullptr;
        switch (t) {
        case Type::Text:
            ret = new TextBlock();
            break;
        case Type::Grap:
            ret = new Graphic();
            break;
        default:
            break;
        }
        return ret;
    }
private:
    std::list<NLComponent*> components;
};

inline std::ostream& operator << (std::ostream& s, const NewsLetter& n) {
    for (auto& item : n.components) {
        s << *item;
    }
    return s;
}

#endif // TERMS25_H

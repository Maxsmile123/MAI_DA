#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>

class TItem{
    friend class TRBT;
    friend class BST;
private:
    std::string key;
    unsigned long long value;

public:
    TItem(): key(""), value(0) {}
    std::string& GetKey()  {
        return key;
    }
    unsigned long long GetValue() const{
        return value;
    }

    friend std::istream& operator>>(std::istream& is, TItem& object){
        is >> object.key >> object.value;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const TItem& object){
        os << object.key << '\t' << object.value << "\n";
        return os;
    }
};

#endif //ITEM_H

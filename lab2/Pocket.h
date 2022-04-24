#ifndef POCKET_H
#define POCKET_H

#include <string>
#include <iostream>
#include "RBT.h"

class TPocket{
    friend class TRBT;
private:
    char color;
    unsigned long long value;
    std::string key;

    TPocket(): color('#'), value(0), key("g") {};
    TPocket(char color_, unsigned long long value_, std::string& key_):
    color(color_), value(value_), key(key_) {};
    friend std::istream& operator>>(std::istream& is,  TPocket& object){
        is >> object.color >> object.value >> object.key;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const TPocket& object){
        os << object.color << object.value << object.key << " ";
        return os;
    }
};

#endif //POCKET_H

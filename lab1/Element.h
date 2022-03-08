#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>

class TElement{
public:
    double key;
    unsigned long long value;


    friend std::istream &operator>>(std::istream &is, TElement &object){
        is >> object.key >> object.value;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, TElement &object){
        os << object.key << '\t' << object.value << "\n";

        return os;
    }

};

#endif //ELEMENT_H

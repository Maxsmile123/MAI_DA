#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include "suffix_tree.h"
#include <vector>
#include <string>
#include <utility>
#include <iostream>


class TSuffix_array
{
    std::vector<size_t> array;
    std::string text;
    bool is_first = true;
public:
    TSuffix_array(std::string s);
    void BuildSiffixArray(const std::shared_ptr<TNode> &node);
    void Find(const std::string &text, unsigned int count);
    ~TSuffix_array() = default;
};


#endif //SUFFIX_ARRAY_H

#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include "suffix_tree.h"
#include <vector>
#include <string>

class TSuffix_array
{
    std::vector<size_t> array;
    std::string text;
public:
    TSuffix_array(std::string s);
    void BuildSiffixArray(const std::shared_ptr<TNode> &node);
    void Find(const std::string &text);
    ~TSuffix_array() = default;
};


#endif //SUFFIX_ARRAY_H

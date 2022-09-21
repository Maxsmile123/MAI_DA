#include "suffix_array.h"

#include <utility>


void TSuffix_array::Find(const std::string &pattern)
{

}

void TSuffix_array::BuildSiffixArray(const std::shared_ptr<TNode> &node)
{
    if (!node) {
        return;
    }
    for (const auto &it: node->children) {
        BuildSiffixArray(it.second);
    }
    if (node->suffix_index != -1) {
        array.push_back(node->suffix_index + 1);
    }

}
TSuffix_array::TSuffix_array(std::string s)
    : text(std::move(s))
{}


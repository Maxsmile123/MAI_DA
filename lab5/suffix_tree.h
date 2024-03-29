#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include "suffix_node.h"
#include "suffix_array.h"

#include <string>
#include <vector>
#include <iostream>


class TSuffix_tree
{
public:
    TSuffix_tree(std::string &text);
    void BuildSuffixTree();
    std::shared_ptr<TNode> get_root()
    {
        return this->root;
    }


private:
    void ExtendSuffixTree(int pos);
    static int EdgeLength(const std::shared_ptr<TNode> &node);

    std::shared_ptr<TNode> root = std::make_shared<TNode>(nullptr, -1, new int(-1));
    std::shared_ptr<TNode> lastCreatedInternalNode = nullptr;
    std::string text;
    std::shared_ptr<TNode> activeNode = nullptr;
    int activeEdge = -1;
    int activeLength = 0;
    int remainingSuffixCount = 0;
    int leafEnd = -1;
};


#endif //SUFFIX_TREE_H

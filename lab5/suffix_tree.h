#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include "suffix_node.h"
#include <string_view>
#include <vector>


class TSuffix_tree
{
public:
    TSuffix_tree(std::string_view &text); // Не забудь в main при чтении добавить сентинел в конец строки!
    void BuildSuffixTree();

private:
    void ExtendSuffixTree(int pos);
    void CountIndex(const std::shared_ptr<TNode> &node, std::vector<int> &vec);
    static int EdgeLength(const std::shared_ptr<TNode> &node);

    std::shared_ptr<TNode> root = std::make_shared<TNode>(nullptr, -1, new int(-1));
    std::shared_ptr<TNode> lastCreatedInternalNode = nullptr;
    std::string_view text;
    std::shared_ptr<TNode> activeNode = nullptr;
    int activeEdge = -1;
    int activeLength = 0;
    int remainingSuffixCount = 0;
    int leafEnd = -1;
};


#endif //SUFFIX_TREE_H